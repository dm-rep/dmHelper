#ifndef _led_sig_h
#define _led_sig_h

#include <stdint.h>
#include <vector>

extern unsigned long millis();
extern void pinMode(uint8_t pin, uint8_t mode);
extern void digitalWrite(uint8_t pin, uint8_t val);

namespace dmHelper
{
    // Simple non-blinking control of LED signaling
	class LedSig
	{
	public:
		// creates instance of LedSig
		LedSig(uint8_t pin, uint8_t on = 1);
		// turns on the LED for the specified time [ms] (0 = forever)
		void on(uint16_t ms = 0);
		// turns off the LED
		void off();
		// starts blinking
		void blink(uint16_t msOn = 500, uint16_t msOff = 500);
		// togles led
		void togle();
		// updates all existing instances (called from execution loop)
		static void updateInstances()
		{
			for (auto &i : instances) i->update();
		}

	private:
		uint8_t m_pin, m_level;
		uint16_t m_tOn, m_tOff;
		uint32_t m_t = 0;
		bool m_on = false;

		void update();
    	static std::vector<LedSig *> instances;
	};
	std::vector<LedSig *> LedSig::instances;
}

#endif