/* ********************************************************************************************** */
/*                                                                                                */
/*   Soft  Tracker  Project                                            :::::::::        :::       */
/*   Telegram_Where_Is_Admin_ESP-01M.ino                              :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/06/28 14:49:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/06/29 18:48:41                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   This is the Main file of the Soft Tracker Project. This firmware allows User to track        */
/*   an approximate location of ESP8285 based devices via Telegram chat notifications.            */
/*   Telegram library details: https://RandomNerdTutorials.com/telegram-group-esp32-esp8266/      */
/*   Important! Firmware file not to exeed 50% of memory. Otherwise OTA unavailable.              */
/*                                                                                                */
/* ********************************************************************************************** */

#include "header.h"

void  setup(void)
{
    short battery_state;
    bool  play_recorded;

    play_recorded = false;
    ESP.wdtEnable(WD_TIMEOUT);                                                // watchdog
    #ifdef DEBUG
        Serial.begin(115200);
    #endif
    DEBUG_PRINTF("\n\n\nDEVICE START\n\n", "");
    system_rtc_mem_read(64, &rtcMng, sizeof(rtcMng));                         // Revive variables from RTC memory after deep sleep
    if (rtcMng.last_wifi == 0)
        play_recorded = true;
    configTime(0, 0, "pool.ntp.org");
    client.setTrustAnchors(&cert);                                            // Add root certificate for api.telegram.org
    WiFi.persistent(true);                                                    // Save WiFi configuration in flash - optional
    WiFi.mode(WIFI_STA);
    WiFi.hostname("SoftTraker");
    ft_wifi_list();
    if (wifiMulti.run(CONNECT_TIMEOUT) == WL_CONNECTED) 
    {
        ft_send_location();
        if (play_recorded && rtcMng.scan_results[0][0])
            ft_scan_report();
        battery_state = ft_battery_check();
        DEBUG_PRINTF("Current battery state is %d%%\n", battery_state);
        if (battery_state <= 15)
        {
            bot.sendMessage(CHAT_ID, "Аккумулятор уже меньше 15%. Срочно нужна подзарядка!", "");
        }
        else if (battery_state >= 99)                                         // unlimited messaging unlocks only when charging
        {
            bot.sendMessage(CHAT_ID, "Аккумулятор полностью заряжен!", "");
            ft_check_incomming_messages(0);                                   // 0 == check new messages for WAIT_FOR_MESSAGES_LIMIT times
        }
        else
            ft_check_incomming_messages(WAIT_FOR_MESSAGES_LIMIT);             // WAIT_FOR_MESSAGES_LIMIT == check new messages only 1 time
    }
    else
    {
        ft_wifi_scan();
        rtcMng.last_wifi = 0;
    }
    ft_go_to_sleep();
}

void  loop(void) { /* NOTHING IS HERE */ }
 
