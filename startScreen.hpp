#ifndef START_SCREEN_HPP
#define START_SCREEN_HPP

#include<iostream>
#include<SDL2/SDL.h>
#include"client.hpp"
#include"data.hpp"
using namespace std;


class StartScreen{
    public:
    string Players[12];
    bool Available[12];
    SDL_Surface* background;
    SDL_Surface* players[12];
    SDL_Surface* LeftArrows[2];
    SDL_Surface* RightArrows[2];
    SDL_Surface* StartLogo[2];
    SDL_Rect* backgroundRect;
    SDL_Rect* PlayerRect;
    SDL_Rect* LeftArrowRect;
    SDL_Rect* RightArrowRect;
    SDL_Rect* StartLogoRect;
    int playerCounter = 0;
    int playerWidth = 60;
    int startLogoWidth = 200;
    int startLogoHeight = 150;

    StartScreen(){
        Players[0]  = "Red";
        Players[1]  = "Yellow";
        Players[2]  = "Blue";
        Players[3]  = "Cyan";
        Players[4]  = "LightGreen";
        Players[5]  = "DarkGreen";
        Players[6]  = "Pink";
        Players[7]  = "Orange";
        Players[8]  = "White";
        Players[9]  = "Indigo";
        Players[10] = "Purple";
        Players[11] = "Brown";
        for (int i = 0; i < 12; i++) Available[i] = true;

        backgroundRect = new SDL_Rect();
        backgroundRect->x = 0;
        backgroundRect->y = 0;
        backgroundRect->w = SCREEN_WIDTH;
        backgroundRect->h = SCREEN_HEIGHT;

        PlayerRect = new SDL_Rect();
        PlayerRect->x = SCREEN_WIDTH / 2 - playerWidth / 2;
        PlayerRect->y = SCREEN_HEIGHT / 2 - playerWidth / 2;
        PlayerRect->w = playerWidth;
        PlayerRect->h = playerWidth;

        LeftArrowRect = new SDL_Rect();
        LeftArrowRect->x = SCREEN_WIDTH / 2 - 100;
        LeftArrowRect->y = SCREEN_HEIGHT / 2 - 25;
        LeftArrowRect->w = 50;
        LeftArrowRect->h = 50;

        RightArrowRect = new SDL_Rect();
        RightArrowRect->x = SCREEN_WIDTH / 2 + 50;
        RightArrowRect->y = SCREEN_HEIGHT / 2 - 25;
        RightArrowRect->w = 50;
        RightArrowRect->h = 50;

        StartLogoRect = new SDL_Rect();
        StartLogoRect->x = SCREEN_WIDTH / 2 - startLogoWidth / 2;
        StartLogoRect->y = 3 * SCREEN_HEIGHT / 4;
        StartLogoRect->w = startLogoWidth;
        StartLogoRect->h = startLogoHeight;

        loadMedia();
        cerr << "Media loaded\n";
    }
    

    bool isHovering(SDL_Event &e, SDL_Rect *rect){
        return e.motion.x >= rect->x && e.motion.x <= rect->x + rect->w && e.motion.y >= rect->y && e.motion.y <= rect->y + rect->h;
    }

    string runGame(SDL_Surface* screen, SDL_Window* window){
        SDL_Event e;
        SDL_Surface* leftArrow = LeftArrows[0];
        SDL_Surface* rightArrow = RightArrows[0];
        SDL_Surface* startLogo = StartLogo[0];
        while (true){
            while (SDL_PollEvent(&e) != 0){
                if (e.type == SDL_QUIT){
                    return "QUIT";
                }
                if (e.type == SDL_KEYDOWN){
                    if (e.key.keysym.sym == SDLK_RIGHT) playerCounter = (playerCounter + 1) % 12;
                    else if (e.key.keysym.sym == SDLK_LEFT) playerCounter = (playerCounter + 11) % 12;
                }
                if (e.type == SDL_MOUSEMOTION){
                    // cerr << e.motion.x << " " << e.motion.y << "\n";
                    if (isHovering(e, LeftArrowRect)) leftArrow = LeftArrows[1];
                    else leftArrow = LeftArrows[0];
                    if (isHovering(e, RightArrowRect)) rightArrow = RightArrows[1];
                    else rightArrow = RightArrows[0];
                    if (isHovering(e, StartLogoRect)) startLogo = StartLogo[1];
                    else startLogo = StartLogo[0];
                }
                if (e.type == SDL_MOUSEBUTTONDOWN){
                    if (e.button.button == SDL_BUTTON_LEFT){
                        if (isHovering(e, LeftArrowRect)) playerCounter = (playerCounter + 11) % 12;
                        if (isHovering(e, RightArrowRect)) playerCounter = (playerCounter + 1) % 12;
                        if (isHovering(e, StartLogoRect)) return Players[playerCounter];
                    }
                }
                if (e.type == SDL_KEYDOWN){
                    if (e.key.keysym.sym == SDLK_RETURN) return Players[playerCounter];
                }
            }
            SDL_BlitScaled(background, NULL, screen, backgroundRect);
            // SDL_BlitSurface(players[playerCounter], NULL, screen, PlayerRect);
            SDL_BlitScaled(players[playerCounter], NULL, screen, PlayerRect);
            SDL_BlitScaled(leftArrow, NULL, screen, LeftArrowRect);
            SDL_BlitScaled(rightArrow, NULL, screen, RightArrowRect);
            SDL_BlitScaled(startLogo, NULL, screen, StartLogoRect);
            SDL_UpdateWindowSurface(window);
        }
        return "Red";
    }   

    void loadMedia(){
        background = SDL_LoadBMP("Images/StartScreenBackground.bmp");
        for (int i = 0; i < 12; i++) {
            string Player = "Images/" + Players[i] + "Down0.bmp";
            players[i] = SDL_LoadBMP(Player.c_str());
        }
        if (background == NULL) cerr << "Background null\n";
        for (int i = 0; i < 12; i++){
            if (players[i] == NULL) cerr << Players[i] << " nnull\n";
        }
        LeftArrows[0] = SDL_LoadBMP("Images/LeftNormalArrow.bmp");
        LeftArrows[1] = SDL_LoadBMP("Images/LeftHighlightedArrow.bmp");
        RightArrows[0] = SDL_LoadBMP("Images/RightNormalArrow.bmp");
        RightArrows[1] = SDL_LoadBMP("Images/RightHighlightedArrow.bmp");

        StartLogo[0] = SDL_LoadBMP("Images/StartLogo1.bmp");
        StartLogo[1] = SDL_LoadBMP("Images/StartLogo2.bmp");
    }
};

#endif // START_SCREEN_HPP