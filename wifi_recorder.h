/* ********************************************************************************************** */
/*                                                                                                */
/*   Soft  Tracker  Project                                            :::::::::        :::       */
/*   wifi_recorder.h                                                  :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/06/28 14:49:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/06/29 18:48:41                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   In case the device wakes up and cannot find any already known Wi-Fi networks, the code in    */
/*   this file searches for Wi-Fi networks at the location of the device and stores the names     */
/*   of the found networks in the RTC memory. When the device eventually connects to a known      */
/*   Wi-Fi network, not only it states its location, but also prints out the list of networks     */
/*   the device "saw" between the last two successfull connections.                               */
/*                                                                                                */
/*   Wi-Fi networks are often named after the venues that own them. This is why recording         */
/*   networks names can help User to backtrack the path the device made between successfull       */
/*   connections.                                                                                 */
/*                                                                                                */
/*   In the scenario when the device leaves a location with a known Wi-Fi network, travels for    */
/*   days to places without known Wi-Fi networks and then later returns to the initial location   */
/*   with the Wi-Fi network it was previously connected to, the device will not be able to        */
/*   report such movements with a standart send_location function. This is when the list of       */
/*   recorded networks names come helpful - it will reflect such movements.                       */
/*                                                                                                */
/* ********************************************************************************************** */

void  ft_clear_scan_results(void)
{
    int  i;
    int  j;

    i = 0;
    j = 0;
    while (rtcMng.scan_results[i][0] != '\0')
    {
        while (rtcMng.scan_results[i][j] != '\0')
        {
            rtcMng.scan_results[i][j] = '\0';
            j++;
        }
        j = 0;
        i++;
    }
}

String  ft_write_report_message(void)
{
    int     i;
    int     j;
    String  message;

    i = 0;
    j = 0;
    message = "Since the last successful connection I've detected some Wi-Fi networks ";   
    message += "I was unable to connect to. Here's the list:\n";
    while (rtcMng.scan_results[i][0] != '\0')
    {
        message += "\n" + String(i + 1) + ". ";
        while (rtcMng.scan_results[i][j] != '\0')
        {
            message += String(rtcMng.scan_results[i][j]);
            j++;
        }
        message += "\n";
        j = 0;
        i++;      
    }
    return (message);
}

void  ft_scan_report(void)
{
    String  message;

    message = ft_write_report_message();
    bot.sendMessage(CHAT_ID, message, "");
    ft_clear_scan_results();
}

void  ft_wifi_scan(void)
{
    int     i;
    int     j;
    int     quantity;
    String  ssid;

    i = 0;
    j = 0;
    DEBUG_PRINTF("Starting WiFi scan.../n", "");
    quantity = WiFi.scanNetworks(false, true);
    if (quantity == 0)
    {
        DEBUG_PRINTF("No networks found\n", "");
    }
    else if (quantity > 0)
    {
        DEBUG_PRINTF("%d networks found\n", quantity);
        while (rtcMng.scan_results[i][0] != '\0' && i < (MAX_NETWORKS - 2))
            i++;              
        while (j < quantity && i < (MAX_NETWORKS - 1))
        {
            ssid = WiFi.SSID(j);
            ssid.toCharArray(rtcMng.scan_results[i], 20);
            i++;
            j++;
        }
    }
    else
        DEBUG_PRINTF("WiFi scan error %d", quantity);
}
 
