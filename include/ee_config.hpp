#ifndef _ee_config_h
#define _ee_config_h

#include <stdint.h>
#include <functional>
#include <EEPROM.h>

namespace dmHelper
{
	// Class providing save/load/restore configuration from/to eeprom
	template<typename T> class EepromConfig
	{
		public:
			// data member
			T data;	
			// calls before using (from setup), returns false when the default was restored
			// version number reflects the T structure (change it on change T)
			bool init(uint16_t version);
			// loads from eeprom (FALSE when the default was restored - version disagreement)
			bool load();
			// restores to default
			void loadDefault();
			// save to eeprom
			bool save();
			// check validity
			bool isValidStructure();
			// if the saved content is different from the current (need to be saved)
			bool isDirty();
			// read from address (for debuging)
			uint8_t readByte(uint16_t add);
			// method to get the default
			std::function<void()> fnObtainDefault;
		private:
			uint16_t m_ver;
			uint32_t m_hash;
			uint32_t calcHash();
	};
}

#endif
