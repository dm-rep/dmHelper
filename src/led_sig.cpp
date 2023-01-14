
#include <stdint.h>
#include <vector>
#include "led_sig.hpp"

// extern unsigned long millis();
// extern void pinMode(uint8_t pin, uint8_t mode);
// extern void digitalWrite(uint8_t pin, uint8_t val);

namespace dmHelper
{

	LedSig::LedSig(uint8_t pin, uint8_t on)
	{
		m_pin = pin;
		m_level = on;
		pinMode(m_pin, 1);
		off();
		instances.push_back(this);
	}
	// turns on the LED for the specified time [ms] (0 = forever)
	void LedSig::on(uint16_t ms)
	{
		m_on = true;
		m_tOn = 0;
		m_tOff = 0;
		digitalWrite(m_pin, m_level);
		if (!ms)
			m_t = 0;
		else
			m_t = millis() + ms;
	}
	// turns off the LED
	void LedSig::off()
	{
		m_on = false;
		digitalWrite(m_pin, m_level ^ 1);
		m_t = 0;
		m_tOn = 0;
		m_tOff = 0;
	}
	// starts blinking
	void LedSig::blink(uint16_t msOn, uint16_t msOff)
	{
		on(msOn);
		m_tOn = msOn;
		m_tOff = msOff;
	}
	// togles led
	void LedSig::togle()
	{
		m_on = !m_on;
		digitalWrite(m_pin, m_on ? m_level : m_level ^ 1);
	}

	void LedSig::update()
	{
		if (m_t && m_t < millis())
		{
			togle();
			m_t = m_on ? m_tOn : m_tOff;
			if (m_t)
				m_t += millis();
		}
	}
	std::vector<LedSig*> LedSig::instances;
};
