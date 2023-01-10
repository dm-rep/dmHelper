dmHelper
==============================
There are several useful classes that can be used in different solutions

**EepromConfig**
> Ensures all operations for working with the configuration.
> - save/load/restore from/to eeprom
> - easy detection of changes in the current configuration compared to the saved one

**FixedQueue**
> Queue with specified maximum length - older records are dropped

**LedSig**
> Simple non-blinking control of LED signaling. Automatic update of all existing instances.

**Vval**
> Class to store a value along with information about its validity
> - tracks value change
> - monitors timeout

*More will be added* :-)