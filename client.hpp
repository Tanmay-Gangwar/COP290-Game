#ifndef CLIENT_HPP
#define CLIENT_HPP

// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include"data.hpp"
#include "character.hpp"
#include <vector>
#include<map>
#define PORT 8080
using namespace std;

const char* SERVER_IP = "10.184.22.118";


map<int, Character> players;
int sock = 0, valread;
sockaddr_in serv_addr;
string helloStr = "Hello from client";
pthread_t thread;
bool Terminate = false;
vector<pair<int, int>> gateCoord;

void handle(string s){
    // cerr << "Test1\n";
    cerr << s << "\n";
    int cnt = 0;
    string player = "";
    string x = "";
    string y = "";
    string imgCounter = "";
    string direction = "";
    string color = "";
    string onBicycle = "";
    string score = "";
    for (char c: s){
        if (c == ' ') cnt++;
        else if (cnt == 5){
            if (('A' > c || 'Z' < c) && ('a' > c || 'z' < c)) return;
        } 
        else if ('0' > c || '9' < c) return;
    }
    // cerr << "test2 " << cnt << "\n";
    if (cnt != 7) return;
    // cerr << "Test2\n";
    cnt = 0;
    // cerr << s << "\n";
    for (char c: s){
        if (c == ' ') cnt++;
        else if (cnt == 0) player += c;
        else if (cnt == 1) x += c;
        else if (cnt == 2) y += c;
        else if (cnt == 3) imgCounter += c;
        else if (cnt == 4) direction += c;
        else if (cnt == 5) color += c;
        else if (cnt == 6) onBicycle += c;
        else score += c;
    }
    cerr << color << "\n";
    // cerr << "OMP\n";
    // cerr << player << "\n" << x << "\n" << y << "\n\n\n";
    int Player = atoi(player.c_str());
    int X = atoi(x.c_str());
    int Y = atoi(y.c_str());
    if (color == "Terminate"){
        cerr << "Trying to erase\n";
        auto it = players.find(Player);
        if (it != players.end()) players.erase(it);
        return;
    }
    // cerr << Player << "\n" << X << "\n" << Y << "\n\n";
    if (players.find(Player) == players.end()) players[Player] = Character(color, gateCoord);
    players[Player].x = X;
    players[Player].y = Y;
    players[Player].imgCounter = atoi(imgCounter.c_str());
    players[Player].direction = atoi(direction.c_str());
    players[Player].onBicycle = (onBicycle == "1");
    players[Player].lastUpdated = time(0);
    players[Player].score = atoi(score.c_str());
}   

void *getMessages(void *args){
    char buffer[1024];
    while(!Terminate){
        valread = read(sock, buffer, 1024);
        string s(buffer);
        // cout << s << "\n";
        handle(s);
        if (s == "Terminate") {
            // cerr << "Uf not expected this\n";
            Terminate = true;
        }
        for (int i = 0; i < 1024; i++) buffer[i] = 0;
    }
    return NULL;
}

void transmit(const char* dir){
    send(sock, dir, 1024, 0);
    // send(sock, dir, strlen(dir), 0);
    // printf("Message sent");
}

 
int start(string characterColor, vector<pair<int, int>> &gates)
{
    // cerr << "1\n";
    gateCoord = gates;
    // const char* hello = helloStr.c_str();
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
 
    // cerr << "2\n";
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }
 
    if (connect(sock, (struct sockaddr*)&serv_addr,
                sizeof(serv_addr))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    Terminate = false;
    // cerr << "3\n";
    players[-1] = Character(characterColor, gates);
    // cerr << "4\n";
    pthread_create(&thread, NULL, getMessages, NULL);
    // while (!Terminate){
    //     string s = "HI";
    //     // cin >> s;
    //     if (s == "Terminate") Terminate = true;
    //     const char* hello = s.c_str();
    //     send(sock, hello, strlen(hello), 0);
    //     printf("Hello message sent\n");
    //     // valread = read(sock, buffer, 1024);
    //     // printf("%s\n", buffer);
    // }
    return 0;
}

#endif // CLIENT_HPP