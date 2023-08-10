/* ********************************************************************************************** */
/*                                                                                                */
/*   Soft  Tracker  Project                                            :::::::::        :::       */
/*   check_incomming_messages.h                                       :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/06/28 14:49:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/06/29 18:48:41                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   These functions are for checking on new Telegram messages, reading them and reacting to      */
/*   them accordingly.                                                                            */
/*                                                                                                */
/* ********************************************************************************************** */

short  ft_answer_engine(String chat_id, String text)
{
    short   cycles;
    String  message;

    ESP.wdtFeed();
    #ifdef PRIVATE
    if (chat_id != CHAT_ID)
    {
        cycles = 0;
        bot.sendMessage(chat_id, "UNAUTHORIZED. ACCESS DENIED.\nThe device is unaccessable from this chat.\n\nhttps://www.youtube.com/watch?v=XV25MrouozE", "");
        return (cycles);
    }
    #endif 
    if (text == "/status")
    {
        ESP.wdtFeed();
        cycles = 0;
        message = "Устройство подключено к " + String(WiFi.SSID());   
        message += ", RSSI " + String(WiFi.RSSI());
        message += " dBm, заряд аккумулятора " + String(ft_battery_check()) + "%";
        bot.sendMessage(chat_id, message, "Markdown");
        message.clear();
        return (cycles);
    }
    else if (text == "/location")
    {
        cycles = 0;
        rtcMng.last_wifi = 0;
        ft_send_location();
        return (cycles);
    }
    else if (text == "/ota")
    {
        cycles = 0;
        bot.sendMessage(chat_id, "Режим перепрошивки OTA нужен для замены программного обеспечения устройства и доступен только разработчикам. Чтобы продолжить, введите свой пароль разработчика", "");
        return (cycles);
    }
    else if (text == "/2461" || text == "/ota 2461")
    {
        cycles = -32767;                                                              // keep the device working as long as possible while OTA
        bot.sendMessage(chat_id, "Пароль принят", "");
        ft_ota_mode(chat_id);
        return (cycles);
    }
    else if (text == "/reboot")
    {
        bot.sendMessage(chat_id, "Перезагружаюсь!", "");
        g_for_this_long = 10;
        cycles = WAIT_FOR_MESSAGES_LIMIT;
        return (cycles);
    }
    else if (text == "/off")
    {
        bot.sendMessage(chat_id, "Выключаюсь!", "");
        cycles = WAIT_FOR_MESSAGES_LIMIT;
        return (cycles);
    }
    else
    {
        cycles = 0;
        bot.sendMessage(chat_id, "Простите, я не понимаю.", "");
        return (cycles);
    }
    return (cycles);
}

short ft_new_messages(short numNewMessages)                                       // function to handle what happens when you receive new messages
{
    short   cycles;
    String  chat_id;
    String  text;
    String  from_name;

    ESP.wdtFeed();
    DEBUG_PRINTF("\nHandling new messages\n", "");
    DEBUG_PRINTF("Number of messages to handle: %d\n", numNewMessages);
    for (short i = 0; i < numNewMessages; i++) 
    {
        DEBUG_PRINTF("Handling loop iterations: i = %d\n", i);
        chat_id = String(bot.messages[i].chat_id);
        text = bot.messages[i].text;
        from_name = bot.messages[i].from_name;
        DEBUG_PRINTF("%s says: ", from_name.c_str());
        DEBUG_PRINTF("%s\n\n", text.c_str());
        cycles = ft_answer_engine(chat_id, text);
    }
    ESP.wdtFeed();
    return (cycles);
}

void  ft_check_incomming_messages(short cycles)
{
    short numNewMessages;

    while (cycles <= WAIT_FOR_MESSAGES_LIMIT)                                       // waiting for new messages
    {
        ESP.wdtFeed();
        DEBUG_PRINTF("Waiting for incomming commands from Telegram chat\n", "");       
        numNewMessages = bot.getUpdates(bot.last_message_received + 1);             // check how many new messages in queue
        while (numNewMessages)
        {
            DEBUG_PRINTF("Inside of the while (numNewMessages) loop, numNewMessages == %d\n", numNewMessages);
            cycles = ft_new_messages(numNewMessages);
            numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        }
        DEBUG_PRINTF("Waiting loop cycles: %d\n", cycles);
        if ((cycles + 25) == WAIT_FOR_MESSAGES_LIMIT)
            bot.sendMessage(CHAT_ID, "Переход в режим сна через 1 минуту. Чтобы отменить, напишите мне любое сообщение", "");
        cycles++;
    }
}
 
