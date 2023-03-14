#include "led.h"
#include "config.h"
#include "amekeyb.h"

void led_init_ports(void)
{
	#ifdef LED_NUM_LOCK_PIN
		setPinDigital(LED_NUM_LOCK_PIN);
		setPinOutput(LED_NUM_LOCK_PIN);
		setPinPower(LED_NUM_LOCK_PIN);
	#endif
	
	#ifdef LED_CAPS_LOCK_PIN
		setPinDigital(LED_CAPS_LOCK_PIN);
		setPinOutput(LED_CAPS_LOCK_PIN);
		setPinPower(LED_CAPS_LOCK_PIN);	
	#endif
	
	#ifdef LED_SCROLL_LOCK_PIN
	
	#endif
}
