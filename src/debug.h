#include <advancedSerial.h>


#define DEBUG_SERIAL Serial

#define DEBUG_WIFISETUP_MSG aSerial.l(Level::v).p(__PRETTY_FUNCTION__).p(":").p(__LINE__).p(":").p(millis()).p("ms").p(":").p
