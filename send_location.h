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
/*   This function checks what Wi-Fi network the device is being connected to and sends an        */
/*   according message into a Telegram chat.                                                      */
/*                                                                                                */
/* ********************************************************************************************** */

void  ft_send_location(void)
{
    String  ssid;

    ESP.wdtFeed();
    ssid = WiFi.SSID();
    DEBUG_PRINTF("WiFi connected to %s\n", ssid.c_str());
//    DEBUG_PRINTF("Signal strength is %i dBm\n\n", WiFi.RSSI());
    if ((ssid == "brok.jmnet.cz") && (rtcMng.last_wifi != 1)) 
    {
        rtcMng.last_wifi = 1;
        bot.sendMessage(CHAT_ID, "Дома в Прага, Uhříněvěs", "");
    }
    if ((ssid == "brmlab.cz") && (rtcMng.last_wifi != 2)) 
    {
        rtcMng.last_wifi = 2;
        bot.sendMessage(CHAT_ID, "В BrmLab Hackerspace Prague в Прага, Žižkov", "");
    }
    if ((ssid == "Roman_iPhone_8") && (rtcMng.last_wifi != 3)) 
    {
        rtcMng.last_wifi = 3;
        bot.sendMessage(CHAT_ID, "Админ раздал для меня Wi-Fi со своего мобильника. Должно быть он где-то путешествует", "");
    }
    if ((ssid == "Stas118_2.4") && (rtcMng.last_wifi != 4)) 
    {
        rtcMng.last_wifi = 4;
        bot.sendMessage(CHAT_ID, "В гостях у друзей в Прага, Žižkov", "");
    }
    if ((ssid == "stas") && (rtcMng.last_wifi != 5)) 
    {
        rtcMng.last_wifi = 5;
        bot.sendMessage(CHAT_ID, "В гостях у друзей в Прага, Žižkov", "");
    }
    if ((ssid == "O2-Internet-304") && (rtcMng.last_wifi != 6)) 
    {
        rtcMng.last_wifi = 6;
        bot.sendMessage(CHAT_ID, "В гостях у родителей девушки в Градец Кралове", "");
    }
    if ((ssid == "Parlor") && (rtcMng.last_wifi != 7)) 
    {
        rtcMng.last_wifi = 7;
        bot.sendMessage(CHAT_ID, "В кафэ Parlor в Прага, Karlín", "");
    }
    if ((ssid == "camppraha") && (rtcMng.last_wifi != 8)) 
    {
        rtcMng.last_wifi = 8;
        bot.sendMessage(CHAT_ID, "В архитектурном центре C.A.M.P. в Праге", "");
    }
    if ((ssid == "pavaon.cz") && (rtcMng.last_wifi != 9)) 
    {
        rtcMng.last_wifi = 9;
        bot.sendMessage(CHAT_ID, "В пиццерии Pavaon в Прага, Nové Město", "");
    }
    if ((ssid == "BERNARD") && (rtcMng.last_wifi != 10)) 
    {
        rtcMng.last_wifi = 10;
        bot.sendMessage(CHAT_ID, "В баре Bernard Pub в Прага, Žižkov", "");
    }
    if ((ssid == "42p_guest") && (rtcMng.last_wifi != 11)) 
    {
        rtcMng.last_wifi = 11;
        bot.sendMessage(CHAT_ID, "В IT школе 42 Prague в Прага, Vysočany", "");
    }
    ssid.clear();
    ESP.wdtFeed();
}
 
