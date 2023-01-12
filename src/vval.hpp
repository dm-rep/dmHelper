#ifndef _vval_h
#define _vval_h

extern unsigned long millis();

template <typename T>
class Vval
{
public:
	Vval(uint16_t expirationSec = 120) { m_expirationSec = expirationSec; m_valid = false; m_dirty = true; };
	
	// setting current valid value
	void setValue(T value)
	{
		m_dirty = (value != m_value) | !isValid();
		m_valid = true;	
		m_value = value;
		m_updated = millis() / 1000;
		m_timeouted = false;
	};

	// change validity to false
	void setInvalid() { m_valid = false; m_dirty = true; };

	// returns true when the value is older than time in constructor argument
	bool isTimeout() {return (millis() / 1000 - m_updated) > m_expirationSec; };

	// returns validity its depends on expiration too 
	bool isValid() { return m_valid && !isTimeout(); };

	// verifies if a change has occurred and clears or keeps dirty flag
	bool isDirty(bool keep = false)
	{
		if (isTimeout() && !m_timeouted)
		{
			// set timeout and dirty
			m_timeouted = true;
			m_dirty = true;
		}
		bool r = m_dirty;
		if (m_dirty && !keep) m_dirty = false;
		return r;
	};

	// sets dirty flag directly
	void setDirty(bool dirty = true) { m_dirty = dirty;  }	

	// returns value as string or specified invalid variant
	const String toString(const String invalid = "") { return isValid() ? String(m_value) : invalid; };

	// returns value as string in decimal (value is tenfold) or specified invalid variant
	const String toString10(const String invalid = "") { return isValid() ? String(((float)m_value/10),1) : invalid; };

	// returns rounded value as string (value is tenfold) or specified invalid variant
	const String toStringRounded(const String invalid = "") { return isValid() ? String((int)((m_value + 5)/10)) : invalid; };	

	// returns last value, it should be calls before isValid()
	const T getValue() { return m_value; }

protected:
	T m_value;
	bool m_valid = false;
	bool m_dirty = true;
	uint16_t m_expirationSec;
	uint32_t m_updated = 0;
	bool m_timeouted = false;
};

#endif