#ifndef MENU_HPP
#define MENU_HPP

#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<vector>
#include"client.hpp"
#include"data.hpp"
#include"text.hpp"
using namespace std;

class Menu{
    public:
    Text text;
    SDL_Surface *background;
    vector<pair<string, char>> hints;
    vector<string> solvedBy;
    vector<int> points;
    vector<SDL_Color> colorCodes;
    SDL_Rect* rect;

    string getLine(){
        string res = "";
        string s;
        cin >> s;
        while (s != "#"){
            res += s;
            res += " ";
            cin >> s;
        }
        return res;
    }

    Menu(){
        freopen("hints.txt", "r", stdin);
        int n;
        cin >> n;
        while (n--){
            string hint = getLine();
            char res;
            cin >> res;
            hints.push_back(make_pair(hint, res));
            solvedBy.push_back("None");
            int point;
            cin >> point;
            points.push_back(point);
        }
        // for (int i = 0; i < hints.size(); i++){
        //     cerr << hints[i].first << "\n" << hints[i].second << "\n" << solvedBy[i] << "\n" << points[i] << "\n";
        // }
        fclose(stdin);
        colorCodes = vector<SDL_Color>(13);
        background = SDL_LoadBMP("Images/MenuBackground.bmp");
        rect = new SDL_Rect();
        rect->x = SCREEN_WIDTH / 2 - 25;
        rect->y = 25;
        rect->w = SCREEN_WIDTH / 2;
        rect->h = SCREEN_HEIGHT - 50;
        getColorCodes();
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

    void draw(SDL_Surface* screenSurface){
        // if (background == NULL) cerr << "Null background\n";
        // else cerr << "Background exist\n";
        SDL_BlitScaled(background, NULL, screenSurface, rect);
        text.displayLarge(screenSurface, "HINTS", colorCodes[12], 3 * SCREEN_WIDTH / 5 + 60, 40);
        for (int i = 0; i < hints.size(); i++){
            SDL_Color color;
            if (solvedBy[i] == "None") color = colorCodes[12];
            else{
                for (int j = 0; j < 12; j++){
                    if (solvedBy[j] == colors[j]) color = colorCodes[j];
                }
            }
            // SDL_Color color = colorCodes[i];
            text.displaySmall(screenSurface, hints[i].first, color, SCREEN_WIDTH / 2 + 10, 31 * i + 177);
        }
    }
};

#endif // MENU_HPP