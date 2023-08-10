/* ********************************************************************************************** */
/*                                                                                                */
/*   Soft  Tracker  Project                                            :::::::::        :::       */
/*   other.h                                                          :+:    :+:     :+: :+:      */
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

void  ft_go_to_sleep(void)
{
    ESP.wdtFeed();
    system_rtc_mem_write(64, &rtcMng, 2);
    DEBUG_PRINTF("\nGoing to sleep for %d minute(s)\n", (g_for_this_long / 60000000));
    DEBUG_PRINTF("The device was running for %d second(s) this time\n", (millis() / 1000));
    DEBUG_PRINTF("\nDEVICE STOP\n\n\n", "");
    ESP.deepSleep(g_for_this_long, WAKE_RFCAL);
}

short  ft_battery_check(void)
{
    short  battery;
      
    battery = ceil((ESP.getVcc() - 3040) / 12.22);
    if (battery <= 0)
        battery = 0;
    if (battery >= 100)
        battery = 100;
    return (battery);
}
 
