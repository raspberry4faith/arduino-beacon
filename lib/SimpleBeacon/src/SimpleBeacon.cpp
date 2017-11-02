#include "SimpleBeacon.h"
#include "esp32-hal-log.h"

#include "bt.h"
#include "bta_api.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"

static esp_ble_adv_params_t _adv_params = {
    .adv_int_min = 512,
    .adv_int_max = 1024,
    .adv_type = ADV_TYPE_IND,
    .own_addr_type = BLE_ADDR_TYPE_PUBLIC,
    .peer_addr = {
        0x00,
    },
    .peer_addr_type = BLE_ADDR_TYPE_PUBLIC,
    .channel_map = ADV_CHNL_ALL,
    .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

static void _on_gap(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    if (event == ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT)
    {
        esp_ble_gap_start_advertising(&_adv_params);
    }
}

static bool _init_gap()
{
    uint8_t adv_data[31];
    uint8_t adv_data_len;

    if (!btStarted() && !btStart())
    {
        log_e("btStart failed");
        return false;
    }
    esp_bluedroid_status_t bt_state = esp_bluedroid_get_status();
    if (bt_state == ESP_BLUEDROID_STATUS_UNINITIALIZED)
    {
        if (esp_bluedroid_init())
        {
            log_e("esp_bluedroid_init failed");
            return false;
        }
    }
    if (bt_state != ESP_BLUEDROID_STATUS_ENABLED)
    {
        if (esp_bluedroid_enable())
        {
            log_e("esp_bluedroid_enable failed");
            return false;
        }
    }

    adv_data[0] = 2;     // Len
    adv_data[1] = 0x01;  // Type Flags
    adv_data[2] = 0x04;  // BR_EDR_NOT_SUPPORTED 0x04
    adv_data[3] = 26;    // Len
    adv_data[4] = 0xFF;  // Type
    adv_data[5] = 0x4C;  // Company 2 -> fake Apple 0x004C LSB
    adv_data[6] = 0x00;  // Company 1 MSB
    adv_data[7] = 0x02;  // Type Beacon
    adv_data[8] = 21;    // Length of Beacon Data

    adv_data[9] = 0x00;  // UUID 1
    adv_data[10] = 0x11; // UUID 2
    adv_data[11] = 0x22; // UUID 3
    adv_data[12] = 0x33; // UUID 4
    adv_data[13] = 0x44; // UUID 5
    adv_data[14] = 0x55; // UUID 6
    adv_data[15] = 0x66; // UUID 7
    adv_data[16] = 0x77; // UUID 8
    adv_data[17] = 0x88; // UUID 9
    adv_data[18] = 0x99; // UUID 10
    adv_data[19] = 0xAA; // UUID 11
    adv_data[20] = 0xBB; // UUID 12
    adv_data[21] = 0xCC; // UUID 13
    adv_data[22] = 0xDD; // UUID 14
    adv_data[23] = 0xEE; // UUID 15
    adv_data[24] = 0xFF; // UUID 16

    adv_data[25] = 0x08; // Major 1 Value
    adv_data[26] = 0x15; // Major 2 Value
    adv_data[27] = 0x47; // Minor 1 Value
    adv_data[28] = 0x11; // Minor 2 Value

    adv_data[29] = 0xD0; // Beacons TX power

    adv_data_len = 30;

    if (esp_ble_gap_config_adv_data_raw(adv_data, adv_data_len))
    {
        log_e("esp_ble_gap_config_adv_data_raw failed");
        return false;
    }

    if (esp_ble_gap_register_callback(_on_gap))
    {
        log_e("gap_register_callback failed");
        return false;
    }

    return true;
}

static bool _stop_gap()
{
    if (btStarted())
    {
        esp_bluedroid_disable();
        esp_bluedroid_deinit();
        btStop();
    }
    return true;
}

SimpleBeacon::SimpleBeacon()
{
}

SimpleBeacon::~SimpleBeacon(void)
{
    _stop_gap();
}

bool SimpleBeacon::begin()
{
    return _init_gap();
}

void SimpleBeacon::end()
{
    _stop_gap();
}
