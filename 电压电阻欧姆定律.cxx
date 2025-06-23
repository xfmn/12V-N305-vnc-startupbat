#include <stdio.h>

int main() {
    double voltage = 5.0;       // 电压 V（单位：伏特）
    double resistance = 2;   // 电阻 R（单位：欧姆，2欧分 = 0.02欧）
    
    double current = voltage / resistance;  // 欧姆定律：I = V / R
    
    printf("电压为 %.2fV，电阻为 %.4fΩ，电流为 %.2fA\n", voltage, resistance, current);
    
    return 0;
}
