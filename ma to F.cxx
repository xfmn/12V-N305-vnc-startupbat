#include <stdio.h>

int main() {
    // 輸入參數
    float mAh = 11.0;     // 鋰電池容量（毫安時）
    float voltage = 2.75;   // 鋰電池電壓（伏特）

    // 換算公式
    float coulombs = mAh * 3.6;           // 1 mAh = 3.6 庫侖
    float farads = coulombs / voltage;   // 法拉 = 庫侖 / 電壓

    // 輸出結果
    printf("等效電容為：約 %.2f F\n", farads);

    return 0;
}
