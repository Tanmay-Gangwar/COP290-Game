#ifndef SCORE_HPP
#define SCORE_HPP

#include<iostream>
#include<algorithm>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<vector>
#include"client.hpp"
#include"data.hpp"
#include"text.hpp"
using namespace std;


class Score{
    public:
    Text text;
    SDL_Surface *image[12];
    SDL_Rect *rect;
    vector<SDL_Color> colorCodes;

    Score(){
        for (int i = 0; i < 12; i++) {
            string Player = "Images/" + colors[i] + "Down0.bmp";
            image[i] = SDL_LoadBMP(Player.c_str());
        }
        rect = new SDL_Rect();
        colorCodes = vector<SDL_Color>(13);
        getColorCodes();
    }

    static bool cmp(Character a, Character b){
        return a.score > b.score;
    }

    void draw(SDL_Surface* screenSurface, map<int, Character> Players){
        vector<Character> players;
        for (auto &x: Players) players.push_back(x.second);
        sort(players.begin(), players.end(), cmp);
        int cnt = 0;
        for (auto &x: players){
            rect->x = 40;
            rect->y = cnt * 60 + 100;
            rect->w = PLAYER_WIDTH;
            rect->h = PLAYER_HEIGHT;
            for (int i = 0; i < 12; i++){
                if (x.color == colors[i]){
                    SDL_BlitScaled(image[i], NULL, screenSurface, rect);
                    text.displayMedium(screenSurface, to_string(x.score), colorCodes[i], rect->x + PLAYER_WIDTH + 10, rect->y);
                }
            }
            cnt++;
        }
    }


    void getColorCodes(){
        colorCodes[ 0].r = 255, colorCodes[ 0].g =   0, colorCodes[ 0].b =   0, colorCodes[ 0].a = 255;
        colorCodes[ 1].r = 255, colorCodes[ 1].g = 255, colorCodes[ 1].b =   0, colorCodes[ 1].a = 255;
        colorCodes[ 2].r =   0, colorCodes[ 2].g =   0, colorCodes[ 2].b = 255, colorCodes[ 2].a = 255;
        colorCodes[ 3].r =   0, colorCodes[ 3].g = 255, colorCodes[ 3].b = 255, colorCodes[ 3].a = 255;
        colorCodes[ 4].r =   0, colorCodes[ 4].g = 255, colorCodes[ 4].b =   0, colorCodes[ 4].a = 255;
        colorCodes[ 5].r =   0, colorCodes[ 5].g = 100, colorCodes[ 5].b =   0, colorCodes[ 5].a = 255;
        colorCodes[ 6].r = 255, colorCodes[ 6].g = 105, colorCodes[ 6].b = 180, colorCodes[ 6].a = 255;
        colorCodes[ 7].r = 255, colorCodes[ 7].g = 165, colorCodes[ 7].b =   0, colorCodes[ 7].a = 255;
        colorCodes[ 8].r = 255, colorCodes[ 8].g = 255, colorCodes[ 8].b = 255, colorCodes[ 8].a = 255;
        colorCodes[ 9].r =  75, colorCodes[ 9].g =   0, colorCodes[ 9].b = 130, colorCodes[ 9].a = 255;
        colorCodes[10].r = 128, colorCodes[10].g =   0, colorCodes[10].b = 128, colorCodes[10].a = 255;
        colorCodes[11].r = 150, colorCodes[11].g =  75, colorCodes[11].b =   0, colorCodes[11].a = 255;
        colorCodes[12].r =   1, colorCodes[12].g =   1, colorCodes[12].b =   1, colorCodes[12].a = 255;
    }

};


#endif // SCORE_HPP