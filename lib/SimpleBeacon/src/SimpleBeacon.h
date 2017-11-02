#ifndef _SIMPLE_BEACON_H_
#define _SIMPLE_BEACON_H_

#include "Arduino.h"

class SimpleBeacon {
    public:

        SimpleBeacon(void);
        ~SimpleBeacon(void);

        /**
         * Start BLE Advertising
         *
         * @return true on success
         *
         */
        bool begin();

        /**
         * Stop BLE Advertising
         *
         * @return none
         */
        void end(void);

    private:

};

#endif
