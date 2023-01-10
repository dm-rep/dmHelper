
#include "vval.hpp"

extern uint32_t millis();

namespace dmHelper
{
	template <typename T>
	void Vval<T>::setValue(T value)
	{
		m_dirty = (value != m_value) | !isValid();
		m_valid = true;	
		m_value = value;
		m_updated = millis() / 1000;
		m_timeouted = false;
	};

	template <typename T>	
	bool Vval<T>::isTimeout() {return (millis() / 1000 - m_updated) > m_expirationSec; };

	template <typename T>
	bool Vval<T>::isValid() { return m_valid && !isTimeout(); };

	template <typename T>
	bool Vval<T>::isDirty(bool keep)
	{
		if (isTimeout() && !m_timeouted)
		{
			m_timeouted = true;
			m_dirty = true;
		}
		bool r = m_dirty;
		if (m_dirty && !keep) m_dirty = false;
		return r;
	};

	
	template <typename T>
	const String Vval<T>::toString(const String invalid) { return isValid() ? String(m_value) : invalid; };

	template <typename T>
	const String Vval<T>::toString10(const String invalid) { return isValid() ? String(((float)m_value/10),1) : invalid; };

	template <typename T>
	const String Vval<T>::toStringRounded(const String invalid) { return isValid() ? String((int)((m_value + 5)/10)) : invalid; };	
}

