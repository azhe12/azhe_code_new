#include <stdio.h>
//#define CP5DTU
#define CP5DWG
#ifdef CP5DTU
#define BRI_SETTING_MIN                 30
#define BRI_SETTING_DEF                 142
#define BRI_SETTING_MAX                 255
#define BRI_SETTING_ONCHG               120

#define AUO_PWM_MIN                     9
#define AUO_PWM_DEFAULT                 60
#define AUO_PWM_MAX                     220
#else
#define BRI_SETTING_MIN                 30
#define BRI_SETTING_DEF                 142
#define BRI_SETTING_MAX                 255
#define BRI_SETTING_ONCHG               120

#define AUO_PWM_MIN                     13
#define AUO_PWM_DEFAULT                 79
#define AUO_PWM_MAX                     255
#endif
int sprd_shrink_pwm(int br)
{
	int shrink_br;

	if (br <= 0) {
		shrink_br = 0;
	} else if (br > 0 && br <= BRI_SETTING_MIN) {
		shrink_br = AUO_PWM_MIN;
	} else if (br > BRI_SETTING_MIN && br <= BRI_SETTING_DEF) {
		shrink_br = (AUO_PWM_MIN + (br - BRI_SETTING_MIN) *
				(AUO_PWM_DEFAULT - AUO_PWM_MIN) /
				(BRI_SETTING_DEF - BRI_SETTING_MIN));
	} else if (br > BRI_SETTING_DEF && br <= BRI_SETTING_MAX) {
		shrink_br = (AUO_PWM_DEFAULT + (br - BRI_SETTING_DEF) *
				(AUO_PWM_MAX - AUO_PWM_DEFAULT) /
				(BRI_SETTING_MAX - BRI_SETTING_DEF));
	} else if (br > BRI_SETTING_MAX)
		shrink_br = AUO_PWM_MAX;

	return shrink_br;
}

int main()
{
	int bri;
	while (scanf("%d", &bri) != EOF) {
		printf("%d\n", sprd_shrink_pwm(bri));
	}
	return 0;
}
