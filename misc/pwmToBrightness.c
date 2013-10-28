#include <stdio.h>

int main(int argc, char** argv)
{
	int bri_min = 30;
	int bri_def = 142;
	int bri_max = 255;
	int auo_pwm_min = 9;
	int auo_pwm_def = 60;
	int auo_pwm_max = 220;
	int pwm;
	float bri;
	while (scanf("%d", &pwm) != EOF) {
		if (pwm <= 0)
			bri = 0;
		else if (pwm > 0 && pwm <= auo_pwm_min) {
			bri = bri_min;
		} else if (pwm > auo_pwm_min && pwm <= auo_pwm_def) {
			bri = 1.0 * (pwm - auo_pwm_min) * (bri_def - bri_min) /  (auo_pwm_def - auo_pwm_min) + bri_min;
		} else if (pwm > auo_pwm_def && pwm <= auo_pwm_max) {
			bri = 1.0 * (pwm - auo_pwm_def) * (bri_max - bri_def) / (auo_pwm_max - auo_pwm_def) + bri_def;
		}
		
		printf("%d\n", (bri - (int)(bri) >= 0.5 ? (int)(bri) + 1 : (int)(bri)));
	}

	return 0;
}
