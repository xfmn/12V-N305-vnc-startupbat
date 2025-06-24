需要声音必须安装虚拟声卡驱动，推流系统音频至网络端口
利用 WebSocket + PCM 音频流服务器 将远程系统音频传至 Android 浏览器播放，同时 VNC 前台显示画面，实现完整远程桌面体验（图+声）。
nodejs websocket 音频流服务。
┌──────────────┐              ┌──────────────┐
│   远程电脑   │              │ Android设备 │
│              │              │              │
│ VNC服务器 ←┐ │              │   VNC客户端  │（前台画面）
│            └─┤              │              │
│ PCM音频抓取 → WebSocket → 浏览器播放器   │（后台声音）
└──────────────┘              └──────────────┘


技术细节构建流程
1. 🖥️ 远程电脑端（Linux 或 Windows）
📌 音频抓取 & PCM 推流
使用工具： ffmpeg、sox、gstreamer、或 Node.js 模块（如 node-lame）

推送方式：

将音频转换为 PCM 或 Opus

经 WebSocket 推送到浏览器


ffmpeg -f pulse -i default -acodec pcm_s16le -f s16le \
  - | websocat -s 8080


// 简化版 nodejs websocket 音频流服务
const WebSocket = require('ws');
const spawn = require('child_process').spawn;

const wss = new WebSocket.Server({ port: 8000 });

wss.on('connection', ws => {
  const ffmpeg = spawn('ffmpeg', ['-f', 'pulse', '-i', 'default', '-acodec', 'pcm_s16le', '-f', 's16le', '-']);
  ffmpeg.stdout.on('data', data => ws.send(data));
});

WebSocket PCM.html
<audio id="player" autoplay></audio>
<script>
const audioContext = new AudioContext();
const socket = new WebSocket("ws://<PC_IP>:8000");

const player = audioContext.createScriptProcessor(4096, 1, 1);
player.connect(audioContext.destination);

let bufferQueue = [];
socket.binaryType = "arraybuffer";

socket.onmessage = function(event) {
  const data = new Int16Array(event.data);
  const float32 = new Float32Array(data.length);
  for (let i = 0; i < data.length; i++) {
    float32[i] = data[i] / 32768;
  }
  bufferQueue.push(float32);
};

player.onaudioprocess = function(e) {
  const output = e.outputBuffer.getChannelData(0);
  output.fill(0);
  if (bufferQueue.length > 0) {
    const buf = bufferQueue.shift();
    output.set(buf.subarray(0, output.length));
  }
};
</script>
