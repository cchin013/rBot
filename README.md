# rBot

**About this project**
<p>
This is a Twitch chat bot written in C++ that interacts with the Twitch API for whatever reason you may have. Currently I just use it to respond to simple commands like !hello, !motd, etc but it can be extended to do basically anything you want it to. Thanks to Tyler Allen for the initial inspiration and the initial, unpolished iteration of the program that I later optimized.
</p>

**Installation**
<p>
1. <code>git clone https://github.com/cchin013/rBot.git</code>
<p>
2. Change the information in <code>rBot.cpp</code> on line 9. Replace YOURAUTHTOKEN with the token generated from the link in the comment above, making sure to include the "oauth" part. The two other strings are self-explanatory. Change the information in rBot.h on lines 98 and 199 to the name of the channel you want the bot to join.
<p>
3. <code>g++ rBot.cpp</code>
<p>
4. <code>./a.out</code>
<p>
Simple as that!

**Uses of rBot**
<p>
You can use this bot to interact with the Twitch API in whatever manner you want(adhering to their terms of service, of course!). You can use it to handle things like !rank, !weather, !runes, !masteries, etc. You just have to change the <code>find</code> function on line 195 to incorporate what you want out of the bot. 
For example, if you wanted the bot to respond with a link to your twitter account when a user types !twitter, you would just add this line:

`if (find(buf, "!twitter"))`
  `{`
  
  `sendData("PRIVMSG #YOURCHANNELNAME :My twitter is located at https://twitter.com/MyTwitterAccountHandle\r\n");`
  
  `}`
  
  **Known bugs**
  * Bot sometimes disconnects after the second PONG 
  * Bot response is sometimes delayed or simply unresponsive to chat commands. Trying multiple times for a command usually works.
 
 
  **TO-DO LIST**
  * Let the bot reconnect if it loses connection (probably just make a larger loop somewhere?)
  * Allow the bot to use moderator status to moderate the chat per the broadcaster's rules
  * Allow the bot to access the weather for a certain zipcode or state via a weather API
  * Maybe allow the bot to join another person's channel without having to restart the bot / change the parameters?
 
  
