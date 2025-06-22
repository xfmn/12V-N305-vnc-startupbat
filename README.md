# bat
@echo off REM 启动 WiFi 热点 netsh wlan set hostednetwork mode=allow ssid=MyHotspot key=12345678 netsh wlan start hostednetwork  REM 启动 TightVNC 服务 net start "TightVNC Server"
