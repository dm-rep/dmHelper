#ifndef _vval_h
#define _vval_h

#include "WString.h"

namespace dmHelper
{
	// Class to store a value along with information about its validity
	template <typename T>
	class Vval
	{
	public:
		Vval(uint16_t expirationSec = 120)
		{
			m_expirationSec = expirationSec;
			m_valid = false;
			m_dirty = true;
		};

		// setting valid value
		void setValue(T value);
		// cancels validity
		void setInvalid();
		// returns TRUE if value was expired
		bool isTimeout();
		// returns validity (depends on expiration or validity setting)
		bool isValid();
		// verifies if a change value has occurred (the flag can be kept)
		bool isDirty(bool keep = false);
		// setting dirty flag force
		void setDirty(bool dirty = true) { m_dirty = dirty; }
		// returns value as string or specified invalid variant
		const String toString(const String invalid = "");
		// returns value as string in decimal (value is tenfold) or specified invalid variant
		const String toString10(const String invalid = "");
		// returns rounded value as string (value is tenfold) or specified invalid variant
		const String toStringRounded(const String invalid = "");
		// returns last value
		const T getValue() { return m_value; }

	protected:
		T m_value;
		bool m_valid = false;
		bool m_dirty = true;
		uint16_t m_expirationSec;
		uint32_t m_updated = 0;
		bool m_timeouted = false;
	};
}
#endif