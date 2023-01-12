#ifndef temp_h
#define temp_h

#include <stdint.h>
#include <WString.h>
#include "vval.hpp"

#define UNDEF16T10 9999

namespace dmHelper
{
	// Specialization from vVal class for temperature storage, designed for 16T10 format handling
	class Temp : public Vval<int16_t>
	{
	public:
		// creates instance
		Temp() : Vval(120) { m_msbLast = 0xff; m_lsbLast = 0xff; }
		// updates from msb/lsb source
		void update(uint8_t msb, uint8_t lsb);
		// returns string of temp without decimal places
		String withoutDecimal();
		// returns string of temp without only decimal places
		String onlyDecimal();
		// returns rounded temp 
		int8_t getT() { return (m_value + 5) / 10; }
		// returns temp in dT
		int16_t getT10() { return m_value; }
		// returns minimal handled value
		int16_t getMinT10() { return m_minT10; }
		// returns maximal handled value
		int16_t getMaxT10() { return m_maxT10; }
		// reset min and max
		void resetMinMax() { m_minT10 = UNDEF16T10; m_maxT10 = UNDEF16T10; }

	private:
		bool m_minus = false;
		uint8_t m_t10;
		uint8_t m_t1;
		uint8_t m_t01;
		uint8_t m_msbLast;
		uint8_t m_lsbLast;
		uint32_t m_age = 0;
		int16_t m_minT10 = UNDEF16T10;
		int16_t m_maxT10 = UNDEF16T10;
	};
}
#endif