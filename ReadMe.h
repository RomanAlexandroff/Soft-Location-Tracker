/* ********************************************************************************************** */
/*                                                                                                */
/*   Soft  Tracker  Project                                            :::::::::        :::       */
/*   ReadMe.h                                                         :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/06/28 14:49:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/09/15 08:14:26                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   This file contains only notes.                                                               */
/*                                                                                                */
/* ************************************************************************************************
  
          ABOUT THE PROJECT
  
      This firmware allows Users to track an approximate location of ESP8285-based devices via
      Telegram chat notifications.
      
      How it works:
      
      ESP8285 connects to already known Wi-Fi networks and informs a pre-set Telegram chat of
      that fact. For it to work Users must manually input the credentials of the Wi-Fi networks
      they wish to be notified about, as well as the Telegram chat ID they wish to be notified
      to. Users also should add a personalized message to every inputed Wi-Fi network to indicate
      the network location. The device will check its connection status at most as frequently as
      once per hour and notify the chat if it manages to connect. The firmware does not have
      access to any other means of location tracking.

      Newly added functionality:  Wi-Fi networks recorder. If ESP8285 wakes up but cannot find
      familiar networks to connect to, it records the names of the networks it can "see" around.
      When ESP8285 eventually connects to a known Wi-Fi network, not only it states its location,
      but also prints out the list of networks the device "saw" since the previous successfull
      connection. Since most of Wi-Fi networks are named after the venues or places they belong to,
      the functionality allows to track locations even when no known Wi-Fi networks are available.
      
      Considering that the Soft Location Tracker cannot track the exact location at the exact time,
      it provides a solid layer of privacy to anything or anyone tracked by such a device, hence the
      name. At the same time it allows Users to reliably backtrack the Tracker's movements.

      Features:

          - multiple Wi-Fi enabled — every program cycle the Tracker tries to connect to all known
            Wi-Fi networks instead of just one of them;
          - antispam — if the Tracker finds himself connected to the same Wi-Fi network it was
            connected to during the previous cycle, it will not send any notifications, preventing
            spamming Users with repetative messages;
          - Wi-Fi networks recorder — even when the Tracker cannot get online it keeps tracking its
            movements by recording all Wi-Fi networks it "sees" on its way;
          - battery status notifications — low battery charge will not go unnoticed by Users, since
            the Tracker can ask them to charge it via Telegram chat;
          - user commands — Users can control some functionality of the Tracker by sending it commands
            via Telegram chat;
          - OTA update — no need to take the Tracker out from wherever you put it to update it! Simply
            open the Telegram chat, command the Tracker to start updating and it will send you a link 
            to open with your web-browser and to drop a binary file with new firmware there.
      
      What applications it can have:
      
          - parents can be sure their children successfully reached school and then         
            came back home after the lessons without invading the children's privacy,
          - companies can track location of their property without compromising the
            privacy of the employees who are being in possesion of the property,
          - senders can be notified of their valuable parcels having reached the intended
            destination without need of a confirmation from the receivers,
          - extravert people who want all their friends to know that they are visiting
            some venue,
          - etc.

      The Soft Location Tracker hardware:
      
      - any ESP8266 or ESP8285 module with accessable RST and GPIO16 pins;
      - LiPol Battery, *230mAh, 3.7V   
      * charge-measuring function in other.h uses capacity-specific constants, hence the 230mAh capacity
        is important. To use batteries with different capacities, the constants need to be recalculated,
        otherwise the readings will not be precise. See the instructions at the bottom of the page.

      Future development:

      - make possible for Users to set the system messages language from Telegram chat;
      - make possible for Users to add new Wi-Fi networks and custom messages for them from Telegram chat
        and save them into EEPROM;
      - add functionality to output the list of saved Wi-Fi networks when requested from Telegram chat;
      - add functionality to delete individual saved Wi-Fi networks from the list from Telegram chat;
      - make possible for Users to assign a name or an ID to individual Trackers from Telegram chat;
      - refactor unused functionality from the UniversalTelegramBot library to empty memory space.
      

      This sketch was firstly written as a toy for my Embedded Development group chat in
      Telegram. It would allow the group chat members to track where I was without discovering
      my precise location.
      
      The project is based on Brian Lough's Universal Telegram Bot Library:
      https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot

      The OTA functionality added using AsyncElegantOTA as well as ESPAsyncWebServer libraries:
      https://github.com/ayushsharma82/AsyncElegantOTA
      https://github.com/me-no-dev/ESPAsyncWebServer


  ***********************************************************************************************


          ISSUES LOG:

      WARNING! Do not call ft_go_to_sleep() function from ft_check_incomming_messages(), 
      ft_new_messages() and ft_ota_mode() functions! It causes the Telegram bot messages queue
      to get stuck on the same last message!

      IMPORTANT! Firmware file shall not to exeed 50% of the microprocessor memory. Otherwise 
      the OTA update functionality may no longer be able to perform the update. For ESP8285
      max firmware file size equals to 522232 bytes.

      UNSOLVED! If I write a command to the bot using reply function, it stops responding 
      to any commands at all. Other than that it continues properly working and continues reporting 
      its location to the chat. So far I was unable to fix the issue even by reflashing the firmware.
      I'm not aware how, but the problem fixes itself within 24 hours. Suddenly the device becomes
      responsive and answers all the comands that had been sent to it within its unavailability. 

      CANCELED. I've tried using bot.setMyCommands to create some kind of a menu for commands to
      the bot. Unfortunately, bot does not understand them in this format. To deactivate the "menu"
      go to the @BotFather bot, enter /mybots command, choose the bot, choose Edit bot, choose Edit
      Commands, enter /empty command. You need to remove bot.setMyCommands from the code first.

      Triggering the OTA mode with an interrupt seems to be very unstable. Possibly, I could
      do that with battery charge level instead. When plugged in, ADC module outputs very 
      distinctive level of charge. I could use that to make the device understand, that it
      is being charged and that it is time to turn on the OTA mode. Experiments required.
      Possibly, I could make the device activate ability to be controlled from the Telegram
      chat when it is above 99% of battery charge. Then, by sending a special command to the
      device I make the device switch to OTA mode.
      Could it be easier to engineer UART into microUSB instead?? 
       
      The device reliably fails to connect to certain Wi-Fi hotspots. I've already tried 
      increasing connectTimeoutMs up to 10000 — no positive effect. I assume, that the problem
      may be in the WiFi.persistent(false) function that forbids the device to save WiFi
      configuration in flash. I have it turned "true" throughout the code now. Need to try it.
  
      I tried implementing SPIFFS file system in order to store all the data managed by the code 
      in a single data.txt file. Unfortunatelly, implementation of this functionality occupied
      so much memory space, that the OTA update was no longer able to work. The functionality
      thus was discarted and RTC memory was used to store the data instead.


      
    
  ***********************************************************************************************    


      EXAMPLE OF THE credentials.h FILE
  
      #define BOTtoken      "xxxxxxxxxx:xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"     // Telegram Bot Token
      #define CHAT_ID       "-xxxxxxxxxxxxx"                                     // Telegram chat ID

      #define OTA_PASSWORD  1234

      #define SSID1         "home_wifi_name"
      #define PASSWORD1     "home_wifi_password"
      #define MESSAGE1      "At home in London"
    
      #define SSID2         "university_wifi_name"
      #define PASSWORD2     "university_wifi_password"
      #define MESSAGE2      "At the university in Oxford"
    
      #define SSID3         "restaurant_wifi_name"
      #define PASSWORD3     "restaurant_wifi_password"
      #define MESSAGE3      "At the "Restaurant_name" restaurant"
     
   
  ***********************************************************************************************


      CALCULATING CONSTANTS FOR BATTERY CHARGE FUNCTION

      You will need to check the following little utility:
      https://github.com/RomanAlexandroff/ESP-Battery-Charge-Utility
      
      It was designed to be a universal solution for battery charge level detection in ESP-based
      projects and has all the instructions inside of it.
    

  *********************************************************************************************** */
