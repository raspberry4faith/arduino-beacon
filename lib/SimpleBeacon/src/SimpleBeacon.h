#ifndef _SIMPLE_BEACON_H_
#define _SIMPLE_BEACON_H_


#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "bt.h"

#include "Arduino.h"

struct ble_gap_adv_params_s;

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
