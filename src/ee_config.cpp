
#include <stdint.h>
#include <EEPROM.h>
#include "ee_config.hpp"

namespace dmHelper
{
	template <typename T>
	bool EepromConfig<T>::init(uint16_t version)
	{
		m_ver = version;
		EEPROM.begin(sizeof(T) + 2);
		return load();
	}
	template <typename T>
	bool EepromConfig<T>::load()
	{
		bool r = isValidStructure();

		if (r)
		{
			EEPROM.get<T>(2, data);
		}
		else
		{
			loadDefault();
			save();
		}
		return r;
	}
	template <typename T>
	void EepromConfig<T>::loadDefault()
	{
		fnObtainDefault();
	}
	template <typename T>
	bool EepromConfig<T>::save()
	{
		EEPROM.put(0, &m_ver);
		EEPROM.put<T>(2, data);
		bool r = EEPROM.commit();
		if (r)
			m_hash = calcHash();
		return r;
	}
	template <typename T>
	bool EepromConfig<T>::isValidStructure()
	{
		// return EEPROM.readUShort(0) == m_ver;
		uint16_t x;
		return EEPROM.get(0, x) == m_ver;
	}
	template <typename T>
	bool EepromConfig<T>::isDirty()
	{
		return (m_hash != calcHash());
	}
	template <typename T>
	uint8_t EepromConfig<T>::readByte(uint16_t add)
	{
		return EEPROM.read(add);
	}
	template <typename T>
	uint32_t EepromConfig<T>::calcHash()
	{
		uint16_t len = sizeof(T);
		uint32_t r = len;
		char *buff = (char *)&data;

		for (uint16_t i = 0; i < len; i++)
		{
			r ^= buff[i] + 0x9e3779b9 + (r << 6) + (r >> 2);
		}
		return r;
	}

}
