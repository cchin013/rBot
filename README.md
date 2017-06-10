# rBot

-----------------
<h1>About this project
-----------------
This is a Twitch chat bot written in C++ that interacts with the Twitch API for whatever reason you may have. Currently I just use it to respond to simple commands like !hello, !motd, etc but it can be extended to do basically anything you want it to. Thanks to Tyler Allen for the initial inspiration and the initial, unpolished iteration of the program that I later optimized.

-----------------
<h2> Installation
-----------------
1. <code>git clone https://github.com/cchin013/rBot.git</code>
2. Change the information in <code>rBot.cpp</code> on line 9. Replace YOURAUTHTOKEN with the token generated from the link in the comment above, making sure to include the "oauth" part. The two other strings are self-explanatory.
3. <code>g++ rBot.cpp</code>
4. <code>./a.out</code>
Simple as that!

-----------------
<h2> Uses of rBot
-----------------
You can use this bot to interact with the Twitch API in whatever manner you want(adhering to their terms of service, of course!). You can use it to handle things like !rank, !weather, !runes, !masteries, etc. You just have to change the <code>find</code> function on line 195 to incorporate what you want out of the bot. 
For example, if you wanted the bot to respond with a link to your twitter account when a user types !twitter, you would just add this line:
<code>
if (find(buf, "!twitter"))
{
  sendData("PRIVMSG #noticemeskyoriwilldie :My twitter is located at https://twitter.com/MyTwitterAccountHandle\r\n");
}
</code>
