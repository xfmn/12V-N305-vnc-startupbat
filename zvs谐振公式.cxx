#include <stdio.h>
#include <math.h>

// 谐振频率计算函数
double calc_zvs_freq(double L_henry, double C_farad) {
    return 1.0 / (2.0 * M_PI * sqrt(L_henry * C_farad));
}

int main() {
    double L_microhenry, C_microfarad;
    
    printf("ZVS 谐振频率计算器\n");
    printf("---------------------\n");
    
    // 用户输入电感、电容（以 μH 与 μF 为单位）
    printf("请输入电感值 L (单位: 微亨 μH): ");
    scanf("%lf", &L_microhenry);
    
    printf("请输入电容总值 C (单位: 微法 μF): ");
    scanf("%lf", &C_microfarad);
    
    // 单位转换为标准单位
    double L = L_microhenry * 1e-6;     // μH → H
    double C = C_microfarad * 1e-6;     // μF → F

    // 计算频率
    double freq = calc_zvs_freq(L, C);

    // 输出结果
    printf("\n计算结果：\n");
    printf("谐振频率 f = %.2f Hz\n", freq);
    printf("约为 %.2f kHz\n", freq / 1000.0);

    return 0;
}
