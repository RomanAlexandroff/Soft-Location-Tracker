/* ********************************************************************************************** */
/*                                                                                                */
/*   Soft  Tracker  Project                                            :::::::::        :::       */
/*   send_location.h                                                  :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/06/28 14:49:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/06/29 18:48:41                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   This sketch was written as a toy for my Embedded Development group chat in Telegram          */
/*   This sketch allows the group chat members to track where I am.                               */
/*   Complete project details: https://RandomNerdTutorials.com/telegram-group-esp32-esp8266/      */
/*   Project created using Brian Lough's Universal Telegram Bot Library:                          */
/*   https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot                               */
/*                                                                                                */
/* ********************************************************************************************** */

void  ft_send_location(void)
{
    String  ssid;

    ESP.wdtFeed();
    ssid = WiFi.SSID();
    DEBUG_PRINTF("WiFi connected to %s\n", ssid.c_str());
//    DEBUG_PRINTF("Signal strength is %i dBm\n\n", WiFi.RSSI());
    if ((ssid == "brok.jmnet.cz") && (rtcMng.lastWiFi != 1)) 
    {
        rtcMng.lastWiFi = 1;
        bot.sendMessage(CHAT_ID, "Дома в Прага, Uhříněvěs", "");
    }
    if ((ssid == "brmlab.cz") && (rtcMng.lastWiFi != 2)) 
    {
        rtcMng.lastWiFi = 2;
        bot.sendMessage(CHAT_ID, "В BrmLab Hackerspace Prague в Прага, Žižkov", "");
    }
    if ((ssid == "Roman_iPhone_8") && (rtcMng.lastWiFi != 3)) 
    {
        rtcMng.lastWiFi = 3;
        bot.sendMessage(CHAT_ID, "Админ раздал для меня Wi-Fi со своего мобильника. Должно быть он где-то путешествует", "");
    }
    if ((ssid == "Stas118_2.4") && (rtcMng.lastWiFi != 4)) 
    {
        rtcMng.lastWiFi = 4;
        bot.sendMessage(CHAT_ID, "В гостях у друзей в Прага, Žižkov", "");
    }
    if ((ssid == "stas") && (rtcMng.lastWiFi != 5)) 
    {
        rtcMng.lastWiFi = 5;
        bot.sendMessage(CHAT_ID, "В гостях у друзей в Прага, Žižkov", "");
    }
    if ((ssid == "O2-Internet-304") && (rtcMng.lastWiFi != 6)) 
    {
        rtcMng.lastWiFi = 6;
        bot.sendMessage(CHAT_ID, "В гостях у родителей девушки в Градец Кралове", "");
    }
    if ((ssid == "Parlor") && (rtcMng.lastWiFi != 7)) 
    {
        rtcMng.lastWiFi = 7;
        bot.sendMessage(CHAT_ID, "В кафэ Parlor в Прага, Karlín", "");
    }
    if ((ssid == "camppraha") && (rtcMng.lastWiFi != 8)) 
    {
        rtcMng.lastWiFi = 8;
        bot.sendMessage(CHAT_ID, "В архитектурном центре C.A.M.P. в Праге", "");
    }
    if ((ssid == "pavaon.cz") && (rtcMng.lastWiFi != 9)) 
    {
        rtcMng.lastWiFi = 9;
        bot.sendMessage(CHAT_ID, "В пиццерии Pavaon в Прага, Nové Město", "");
    }
    if ((ssid == "BERNARD") && (rtcMng.lastWiFi != 10)) 
    {
        rtcMng.lastWiFi = 10;
        bot.sendMessage(CHAT_ID, "В баре Bernard Pub в Прага, Žižkov", "");
    }
    if ((ssid == "42p_guest") && (rtcMng.lastWiFi != 11)) 
    {
        rtcMng.lastWiFi = 11;
        bot.sendMessage(CHAT_ID, "В IT школе 42 Prague в Прага, Vysočany", "");
    }
    ssid.clear();
    ESP.wdtFeed();
}
 
