#include "rBot.h"

using namespace std;

int main()
{

//You can get your account's auth token here: http://twitchapps.com/tmi/
rBot bot = rBot("PASS YOURAUTHTOKEN\r\n", "NICK YOURTWITCHUSERNAME\r\n", "USER YOURTWITCHUSERNAME\r\n");
bot.start();

return 0;

}
