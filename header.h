/* ********************************************************************************************** */
/*                                                                                                */
/*   Soft  Tracker  Project                                            :::::::::        :::       */
/*   header.h                                                         :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/06/28 14:49:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/06/29 18:48:41                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   This firmware allows User to track an approximate location of ESP8285 based devices via      */
/*   Telegram chat notifications.                                                                 */
/*   Telegram library details: https://RandomNerdTutorials.com/telegram-group-esp32-esp8266/      */
/*   Project created using Brian Lough's Universal Telegram Bot Library:                          */
/*   https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot                               */
/*   Important! Firmware file not to exeed 50% of memory. Otherwise OTA unavailable.              */
/*                                                                                                */
/* ********************************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <Arduino.h>                                                  // OTA
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WiFiMulti.h>
#include <stdio.h>
#include <ESPAsyncTCP.h>                                              // OTA
#include <ESPAsyncWebServer.h>                                        // OTA
#include <AsyncElegantOTA.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>                                              // Telegram
extern "C" {
  #include "user_interface.h"                                         // RTC memory read/write functions
}
ADC_MODE(ADC_VCC);

#define PRIVATE                                                       // comment out this line to allow bot answer in any Telegram chat
#define DEBUG                                                         // comment out this line to turn off Serial output
#ifdef DEBUG
  #define DEBUG_PRINTF(x, y) Serial.printf(x, y)
  #define DEBUG_PRINTS(q, w, e, r, t) Serial.printf(q, w, e, r, t)
#else
  #define DEBUG_PRINTF(x, y)
  #define DEBUG_PRINTS(q, w, e, r, t)
#endif
#define WD_TIMEOUT 5000                                               // watchdog, in milliseconds (5000 == 5 seconds; 8500 — system max val)
#define WAIT_FOR_OTA_LIMIT 30000                                      // in milliseconds (30000 == 30 seconds)
#define WAIT_FOR_MESSAGES_LIMIT 80                                    // in seconds, 1 == 2 seconds (80 == 160 seconds == 2,5 minutes)
#define SLEEP_DURATION 3600000000                                     // in microseconds (60000000 == 1 minute; 3600000000 == 1 hour)
#define BOTtoken "6190828349:AAE7EGTvHINrN6Msql22NUK2QK4VNvRATV8"     // WhereIsAdmin_bot Bot Token — DO NOT CHANGE!
//#define CHAT_ID "-1001789922877"                                    // Embedded Development Club chat ID - FOR RELEASE ONLY
#define CHAT_ID "-1001928425767"                                      // Test Group For Telegram Gadgets chat ID - FOR DEVELOPMENT ONLY

typedef struct {
unsigned short    last_wifi;
} rtcMemoryStruct;
rtcMemoryStruct rtcMng; 

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
ESP8266WiFiMulti wifiMulti;
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
AsyncWebServer server(80);

const uint32_t    g_connect_timeout = 5000;                // WiFi connect timeout per each AP. In milliseconds. Increase if cannot connect.
unsigned long     g_millis1 = 0;
unsigned int      g_for_this_long = SLEEP_DURATION;        // How long the ESP will sleep for

#include "other.h"
#include "ota_mode.h"
#include "send_location.h"
#include "check_incomming_messages.h"
#include "wifi_list.h"

void   ft_wifi_list(void);
void   ft_send_location(void);
void   ft_check_incomming_messages(short cycles);
short  ft_new_messages(int numNewMessages);
short  ft_answer_engine(String chat_id, String text);
void   ft_ota_mode(String chat_id);
short  ft_battery_check(void);
void   ft_go_to_sleep(void);

#endif
 
