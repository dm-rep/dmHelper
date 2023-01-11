#ifndef _ee_config_h
#define _ee_config_h

#include <stdint.h>
#include <EEPROM.h>

template<typename T> class EepromConfig
{
    public:
		// configuration data (type T)
		T data;
		
		// init (calls from setup) return false when the default was restored
		// version: identifier of the data structure (change on change!)
		bool init(uint16_t version)
		{
			m_ver = version;
			EEPROM.begin(sizeof(T) + 2);
			return load();
		}

		// reads config (returns false when default had to be loaded)
		bool load()
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

		// restore default
		void loadDefault()
		{
			fnObtainDefault();
		}	

		// saves current, returns true on success
		bool save()
		{
			//EEPROM.writeUShort(0, m_ver);
			EEPROM.put(0, m_ver);
			EEPROM.put<T>(2, data);	
			bool r = EEPROM.commit();
			if (r) m_hash = _calcHash();
			return r;
		}

		// checks validity
		bool isValidStructure()
		{
			uint16_t x;
			return EEPROM.get(0, x) == m_ver;
		}

		// if the saved is different from the current
		bool isDirty()
		{
			return (m_hash != _calcHash());
		}

		// read from address (debug)
		uint8_t readByte(uint16_t add)
		{
			return EEPROM.read(add);
		}
    
		std::function<void()> fnObtainDefault;

    private:
        uint16_t m_ver;
        uint32_t m_hash;

		// calculates simple hash
		uint32_t _calcHash()
		{
			uint16_t len = sizeof(T);
			uint32_t r = len;
			char *buff = (char*)&data;

			for (uint16_t i = 0; i < len; i++)
			{
				r ^= buff[i] + 0x9e3779b9 + (r << 6) + (r >> 2);
			}
			return r;    
		}
};





#endif
