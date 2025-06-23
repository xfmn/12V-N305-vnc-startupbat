#include <stdio.h>

typedef struct {
    const char* metal;
    // 波長（nm）
    // 對應的反射率範圍（最小, 最大，浮點數0~1）
    float refl_365_min, refl_365_max;
    float refl_400_min, refl_400_max;
    float refl_450_min, refl_450_max;
    float refl_520_min, refl_520_max;
    float refl_620_min, refl_620_max;
} MetalOpticalProperties;

MetalOpticalProperties metals[] = {
    {"Silver", 0.70f, 0.80f, 0.85f, 0.90f, 0.90f, 0.95f, 0.95f, 0.97f, 0.95f, 0.98f},
    {"Gold",   0.20f, 0.40f, 0.30f, 0.50f, 0.50f, 0.70f, 0.60f, 0.70f, 0.85f, 0.95f},
    {"Copper", 0.30f, 0.50f, 0.40f, 0.60f, 0.50f, 0.70f, 0.55f, 0.65f, 0.80f, 0.90f},
    {"Aluminum",0.80f,0.85f, 0.85f, 0.90f, 0.85f, 0.90f, 0.85f, 0.90f, 0.85f, 0.90f},
    {"Iron",   0.20f, 0.40f, 0.30f, 0.50f, 0.40f, 0.50f, 0.40f, 0.50f, 0.60f, 0.70f},
};

int metal_count = sizeof(metals) / sizeof(metals[0]);

float get_reflectance(MetalOpticalProperties m, int wavelength_nm) {
    // 返回該波長反射率範圍中間值
    switch(wavelength_nm) {
        case 365: return (m.refl_365_min + m.refl_365_max) / 2.0f;
        case 400: return (m.refl_400_min + m.refl_400_max) / 2.0f;
        case 450: return (m.refl_450_min + m.refl_450_max) / 2.0f;
        case 520: return (m.refl_520_min + m.refl_520_max) / 2.0f;
        case 620: return (m.refl_620_min + m.refl_620_max) / 2.0f;
        default: return -1.0f; // 不支持的波長
    }
}

int main() {
    int wavelength;
    char metal_name[20];

    printf("請輸入金屬名稱 (Silver, Gold, Copper, Aluminum, Iron): ");
    scanf("%19s", metal_name);

    printf("請輸入波長 (nm), 支援365,400,450,520,620: ");
    scanf("%d", &wavelength);

    for(int i=0; i<metal_count; i++) {
        if (strcmp(metals[i].metal, metal_name) == 0) {
            float refl = get_reflectance(metals[i], wavelength);
            if (refl < 0) {
                printf("不支持的波長 %d nm\n", wavelength);
            } else {
                printf("%s 在 %d nm 波長的反射率約為 %.2f%%\n", metal_name, wavelength, refl*100);
                printf("吸收率約為 %.2f%%\n", (1.0f - refl)*100);
            }
            return 0;
        }
    }
    printf("找不到金屬 %s\n", metal_name);
    return 0;
}
