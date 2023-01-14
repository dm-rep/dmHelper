
#include <stdint.h>
#include <WString.h>
#include "vval.hpp"
#include "temp.hpp"

#define UNDEF16T10 9999

namespace dmHelper
{
	void Temp::update(uint8_t msb, uint8_t lsb)
	{
		m_msbLast = msb;
		m_lsbLast = lsb;

		m_t10 = (msb & 0xf0) >> 4;
		m_t1 = msb & 0x0f;
		m_t01 = (lsb & 0xf0) >> 4;

		bool undef = (m_t10 > 9 || m_t1 > 9 || m_t01 > 9);
		m_minus = (lsb & 1) == 1;

		if (undef)
		{
			setInvalid();
		}
		else
		{
			int16_t t10 = 100 * m_t10 + 10 * m_t1 + m_t01;
			setValue(m_minus ? -1 * t10 : t10);
			if (m_minT10 == UNDEF16T10 || t10 < m_minT10)
				m_minT10 = t10;
			else if (m_maxT10 == UNDEF16T10 || t10 > m_maxT10)
				m_maxT10 = t10;
		}
	}

	String Temp::withoutDecimal()
	{
		if (!isValid())
			return "?";
		if (m_value >= 0 || m_value <= -10)
			return String(m_value / 10);
		return String("-0");
	}

	String Temp::onlyDecimal()
	{
		if (!isValid())
			return "  ";
		uint8_t decimal = m_value < 0 ? (-m_value) % 10 : m_value % 10;
		String r = ". ";
		r[1] = decimal + '0';
		return r;
	}

}
