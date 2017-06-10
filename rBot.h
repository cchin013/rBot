#ifndef RBOT_H
#define RBOT_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

using namespace std;

class rBot {
    public:
    rBot(char const* pass, char const* nick, char const* user);
    ~rBot();
    void start();
    bool find(char const* toLookThru, char const* toFind);
    
    private:
    int s; //socket info
    char const* port; //6667 for IRC bot
    char const* pass; //OAuth password from http://twitchapps.com/tmi/
    char const* nick; //username of the bot
    char const* user;
    bool success; //Don't try to start the bot if the connection fails
    bool sendData(char const* msg); //Helper to commands; sends message or command in response to a command in chat
    void sendPong(char const* buf); //IRC chats send a PING and you need to respond with PONG or the bot disconnects
    void commands(char const* buf); //Deal with the proper response to commands from chat
};

rBot::rBot(char const* pass, char const* nick, char const* user)
{
    this->pass = pass;
    this->nick = nick;
    this->user = user;
}

rBot::~rBot()
{
    close(s);
}

void rBot::start()
{
    int MAXDATASIZE = 100;
    this->success = true;
    this->port = "6667";
    struct addrinfo hints, *servinfo;
    memset(&hints, 0, sizeof hints);
    
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    int errCheck; //Store error messages if failed connection
    if ((errCheck = getaddrinfo("irc.chat.twitch.tv", port, &hints, &servinfo)) != 0)
    {
        this->success = false;
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(errCheck));
    }
    
    //Check if socket setup failed
    if ((s = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol))) 
    {
        perror("client: socket");
    }
    
    //Connect the bot if all else goes well
    if (connect(s,servinfo->ai_addr, servinfo->ai_addrlen) == -1)
    {
        close(s);
        perror("Client successfully connected");
    }
    
    freeaddrinfo(servinfo);
    
    //Setup for receiving data
    int data; //Stores data
    char buf[MAXDATASIZE]; //Let's set the max data size(msg size) to 150
    
    int tick = 0; //amount of times data received
    while (1) //Main bot activity loop
    {
        ++tick;
        switch(tick) {
            case 1:
                sendData(pass);
                sendData(nick);
                sendData(user);
                break;
            case 4:
                sendData("JOIN #noticemeskyoriwilldie\r\n"); //This line determines what channel you want the bot in
                break;
            default:
                break;
        }
    
    //The following will deal with receiving commands from the chat
    data = recv(s,buf,MAXDATASIZE-1,0);
    buf[data] = '\0';
    cout << buf;
    commands(buf);
    
    if (find(buf, "PING"))
    {
        sendPong(buf);
    }
    
    if (data == 0)
    {
        cout << "Connection lost for some reason, figure it out" << endl;
        break;
    }
    }
}

//Modified version of a C++ character searching skeleton found online, honestly not that complicated
bool rBot::find(char const* toLookThru, char const* toFind)
{
    int toLookLen = strlen(toLookThru); //same as toLookThru.size() if it were a string
    int toFindLen = strlen(toFind);     //these are just looping variables
    
    for (unsigned i = 0; i < toLookLen; ++i)
    {
        bool found = true;
        for (unsigned j = 1; j < toFindLen; ++j) //This is very slow [O(n^2)]
        {                                       //TODO: Optimize this I suppose? Can maybe speed it up through markov chains?
            if (toLookThru[j + i] != toFind[j]) //Matching the letters one by one for the words
            {                                   //i.e. if we need to find "BOB" it would compare
                found = false;                  //the first letter of toLookThru to "B" then second letter to "O" etc
            }
        }
        if (found)
        {
            return true;
        }
    }
    return false;
}

bool rBot::sendData(char const* msg)
{
    int len = strlen(msg);
    int bytes = send(s,msg,len,0);
    if (bytes == 0)
    {
        return false;
    }
    return true;
}

void rBot::sendPong(char const* buf)
{
    char const* toLookThru = "PING ";
    
    for (unsigned i = 0; i < strlen(buf); ++i)
    {
        if (buf[i] == toLookThru[0])
        {
            bool found = true;
            for (unsigned j = 1; j < 4; ++j)
            {
                if (buf[i + j] != toLookThru[j])
                {
                    found = false;
                }
            }
            
            if (found)
            {
                int tick = 0;
                for (unsigned j = (i + strlen(toLookThru)); j < strlen(buf); ++j)
                {
                    ++tick;
                }
                
                char const* returnPong = "PONG ";

                if (sendData(returnPong))
                {
                    cout << "PING PONG" << endl;
                }
                return;
            }
        }
    }
}

void rBot::commands(char const* buf)
{
    if (find(buf, "!elias"))
    {
        sendData("PRIVMSG #noticemeskyoriwilldie: hello elias sells\r\n");
    }
}

#endif
