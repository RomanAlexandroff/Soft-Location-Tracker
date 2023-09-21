/* ********************************************************************************************** */
/*                                                                                                */
/*   Soft  Tracker  Project                                            :::::::::        :::       */
/*   send_location.h                                                  :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/06/28 14:49:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/09/16 12:48:41                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   This function checks what Wi-Fi network the device is being connected to and sends an        */
/*   according message into a Telegram chat.                                                      */
/*                                                                                                */
/* ********************************************************************************************** */

void  IRAM_ATTR ft_send_location(void)
{
    String  ssid;

    ESP.wdtFeed();
    ssid = WiFi.SSID();
    DEBUG_PRINTF("WiFi connected to %s\n", ssid.c_str());
//    DEBUG_PRINTF("Signal strength is %i dBm\n\n", WiFi.RSSI());
    if ((ssid == SSID1) && (rtcMng.g_last_wifi != 1)) 
    {
        rtcMng.g_last_wifi = 1;
        bot.sendMessage(CHAT_ID, MESSAGE1, "");
        return;
    }
    if ((ssid == SSID2) && (rtcMng.g_last_wifi != 2)) 
    {
        rtcMng.g_last_wifi = 2;
        bot.sendMessage(CHAT_ID, MESSAGE2, "");
        return;
    }
    if ((ssid == SSID3) && (rtcMng.g_last_wifi != 3)) 
    {
        rtcMng.g_last_wifi = 3;
        bot.sendMessage(CHAT_ID, MESSAGE3, "");
        return;
    }
    if ((ssid == SSID4) && (rtcMng.g_last_wifi != 4)) 
    {
        rtcMng.g_last_wifi = 4;
        bot.sendMessage(CHAT_ID, MESSAGE4, "");
        return;
    }
    if ((ssid == SSID5) && (rtcMng.g_last_wifi != 5)) 
    {
        rtcMng.g_last_wifi = 5;
        bot.sendMessage(CHAT_ID, MESSAGE5, "");
        return;
    }
    if ((ssid == SSID6) && (rtcMng.g_last_wifi != 6)) 
    {
        rtcMng.g_last_wifi = 6;
        bot.sendMessage(CHAT_ID, MESSAGE6, "");
        return;
    }
    if ((ssid == SSID7) && (rtcMng.g_last_wifi != 7)) 
    {
        rtcMng.g_last_wifi = 7;
        bot.sendMessage(CHAT_ID, MESSAGE7, "");
        return;
    }
    if ((ssid == SSID8) && (rtcMng.g_last_wifi != 8)) 
    {
        rtcMng.g_last_wifi = 8;
        bot.sendMessage(CHAT_ID, MESSAGE8, "");
        return;
    }
    if ((ssid == SSID9) && (rtcMng.g_last_wifi != 9)) 
    {
        rtcMng.g_last_wifi = 9;
        bot.sendMessage(CHAT_ID, MESSAGE9, "");
        return;
    }
    if ((ssid == SSID10) && (rtcMng.g_last_wifi != 10)) 
    {
        rtcMng.g_last_wifi = 10;
        bot.sendMessage(CHAT_ID, MESSAGE10, "");
        return;
    }
    if ((ssid == SSID11) && (rtcMng.g_last_wifi != 11)) 
    {
        rtcMng.g_last_wifi = 11;
        bot.sendMessage(CHAT_ID, MESSAGE11, "");
        return;
    }
    if ((ssid == SSID12) && (rtcMng.g_last_wifi != 12)) 
    {
        rtcMng.g_last_wifi = 12;
        bot.sendMessage(CHAT_ID, MESSAGE12, "");
        return;
    }
    if ((ssid == SSID13) && (rtcMng.g_last_wifi != 13)) 
    {
        rtcMng.g_last_wifi = 13;
        bot.sendMessage(CHAT_ID, MESSAGE13, "");
        return;
    }
    ESP.wdtFeed();
}
 
