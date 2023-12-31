/* ********************************************************************************************** */
/*                                                                                                */
/*   Soft  Tracker  Project                                            :::::::::        :::       */
/*   ota_mode.h                                                       :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/06/28 14:49:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/06/29 18:48:41                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   This file allowes to update the microntroller wirelessly, simply by sending a compiled       */
/*   binary file into its file system. The microcontroller opens a gate, accessable through       */
/*   any web-browser via a link, that is provided by the microcontroller through both Serial      */
/*   port and Telegram chat.                                                                      */
/*   NOTE! The compiled firmware file should not exeed 50% of the microprocessor memory!          */
/*   Otherwise the OTA update functionality may no longer be able to perform the update.          */
/*   For ESP8285 (ESP-01M) max firmware file size equals to 522232 bytes.                         */
/*                                                                                                */
/* ********************************************************************************************** */

short  ft_ota_mode(String chat_id) 
{
    String      ssid;
    IPAddress   ip;
    String      message;
    short       battery;
    int         i;

    ESP.wdtFeed();
    ssid = WiFi.SSID();
    ip = WiFi.localIP();
    battery = ft_battery_check();
    if (battery <= 15)
    {
        DEBUG_PRINTF("\nThe battery is too low to perform an OTA update safely. Connect a charging cable to proceed.\n", "");
        message = "The battery is too low to perform an OTA update safely. ";
        message += "Connect a charging cable to proceed. I will wait as long as I can.";
        bot.sendMessage(chat_id, message, "");
        while (battery > 5 && battery <= 15 && i)
        {
            battery = ft_battery_check();
            ESP.wdtFeed();
            delay (999);
            i--;
        }
        if (battery <= 15)
            return (WAIT_FOR_MESSAGES_LIMIT);
        message.clear();
    }
    DEBUG_PRINTF("\n\nSOFT TRACKER\nOTA update mode initialized.\n\n", "");
    DEBUG_PRINTF("Wi-Fi network: %s\n", ssid.c_str());
    DEBUG_PRINTS("IP address: %d.%d.%d.%d\n\n", ip[0], ip[1], ip[2], ip[3]);
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { request->send(200, "text/plain", "Soft Tracker OTA update."); });        //Starting the OTA server
    AsyncElegantOTA.begin(&server);
    server.begin();
    DEBUG_PRINTF("HTTP server started.\nConnect to the stated Wi-Fi network and proceed to the link\n\n", "");
    DEBUG_PRINTS("http://%d.%d.%d.%d/update\n\n\n", ip[0], ip[1], ip[2], ip[3]);
    message = "OTA mode activated. \n\nConnected to\n" + String(ssid);
    message += "\nAssigned IP\n" + String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
    message += "\n\nConnect to the stated Wi-Fi network and go to the link\nhttp://";
    message += String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]) + "/update";
    message += "\n\nRemember that in OTA mode I will not go to sleep automatically.";
    message += " To cancel the OTA mode without firmware update use \"off\" or \"reboot\" commands";
    bot.sendMessage(chat_id, message, "");
    ESP.wdtFeed();
    return (-32767);
}
 
