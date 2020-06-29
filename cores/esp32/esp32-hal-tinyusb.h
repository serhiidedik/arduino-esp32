// Copyright 2015-2020 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#pragma once

#include "esp32-hal.h"

#if CONFIG_IDF_TARGET_ESP32S2

#ifdef __cplusplus
extern "C" {
#endif

#include "tinyusb.h"

typedef struct {
        uint16_t vid;
        uint16_t pid;
        const char * product_name;
        const char * manufacturer_name;
        const char * serial_number;
        uint16_t fw_version;
        
        uint16_t usb_version;
        uint8_t usb_class;
        uint8_t usb_subclass;
        uint8_t usb_protocol;
        uint8_t usb_attributes;
        uint16_t usb_power_ma;
        
        bool webusb_enabled;
        const char * webusb_url;
} tinyusb_device_config_t;

#define TINYUSB_CONFIG_DEFAULT() {                                      \
        .vid = USB_ESPRESSIF_VID,                                       \
        .pid = 0x0002,                                                  \
        .product_name = CONFIG_USB_DESC_PRODUCT_STRING,                 \
        .manufacturer_name = CONFIG_USB_DESC_MANUFACTURER_STRING,       \
        .serial_number = CONFIG_USB_DESC_SERIAL_STRING,                 \
        .fw_version = CONFIG_USB_DESC_BCDDEVICE,                        \
        .usb_version = 0x0200,                                          \
        .usb_class = TUSB_CLASS_MISC,                                   \
        .usb_subclass = MISC_SUBCLASS_COMMON,                           \
        .usb_protocol = MISC_PROTOCOL_IAD,                              \
        .usb_attributes = TUSB_DESC_CONFIG_ATT_SELF_POWERED,            \
        .usb_power_ma = 500,                                            \
        .webusb_enabled = false,                                        \
        .webusb_url = "espressif.github.io/arduino-esp32/webusb.html"   \
}

esp_err_t tinyusb_init(tinyusb_device_config_t *config);

// The following definitions and functions are to be used only by the drivers
typedef enum {
    USB_INTERFACE_CDC,
    USB_INTERFACE_DFU,
    USB_INTERFACE_HID,
    USB_INTERFACE_VENDOR,
    USB_INTERFACE_MSC,
    USB_INTERFACE_MIDI,
    USB_INTERFACE_CUSTOM,
    USB_INTERFACE_MAX
} tinyusb_interface_t;

esp_err_t tinyusb_enable_interface(tinyusb_interface_t interface);
uint8_t tinyusb_add_string_descriptor(const char * str);
uint8_t tinyusb_get_free_duplex_endpoint(void);
uint8_t tinyusb_get_free_in_endpoint(void);
uint8_t tinyusb_get_free_out_endpoint(void);

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_IDF_TARGET_ESP32S2 */