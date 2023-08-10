/* ********************************************************************************************** */
/*                                                                                                */
/*   Soft  Tracker  Project                                            :::::::::        :::       */
/*   wifi_list.h                                                      :+:    :+:     :+: :+:      */
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

void  ft_wifi_list(void)
{
    wifiMulti.addAP("brok.jmnet.cz", "19S67MBA");
    wifiMulti.addAP("42p_guest", "guest.of.42");
    wifiMulti.addAP("brmlab.cz", "brmlabINSIDE!");
    wifiMulti.addAP("Roman_iPhone_8", "qweasdyxc123");
    wifiMulti.addAP("Stas118_2.4", "180915LK");
    wifiMulti.addAP("stas", "18091809");
    wifiMulti.addAP("O2-Internet-304", "SJd96Qux");
    wifiMulti.addAP("Parlor", "Iloveicecream2");
    wifiMulti.addAP("camppraha", "karelprager");
    wifiMulti.addAP("pavaon.cz", "pavaon11");
    wifiMulti.addAP("BERNARD", "jeseniova93");
    ESP.wdtFeed();
}
 
