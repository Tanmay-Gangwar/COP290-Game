#ifndef TEXT_HPP
#define TEXT_HPP

#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<vector>
#include"client.hpp"
#include"data.hpp"
using namespace std;

class Text{
    public:
    SDL_Rect* text_rect;
    TTF_Font* largeFont;
    TTF_Font* smallFont;
    TTF_Font* mediumFont;
    
    Text(){
        if (TTF_Init() < 0){
            cerr << "Failed to initialize fonts\n";
            return;
        }
        smallFont = TTF_OpenFont("Font/ZakwanOebit.ttf", 20);
        largeFont = TTF_OpenFont("Font/font.ttf", 80);
        mediumFont = TTF_OpenFont("Font/timesnewroman.ttf", 40);
    }

    void displaySmall(SDL_Surface* screenSurface, string message_text, SDL_Color &color, int x, int y){
        SDL_Surface* text_surface = TTF_RenderText_Solid(smallFont, message_text.c_str(), color);
        SDL_Rect* rect = new SDL_Rect();
        rect->w = text_surface->w;
        rect->h = text_surface->h;
        if (x == -1) rect->x = screenSurface->w / 2 - text_surface->w / 2;
        else rect->x = x;
        rect->y = y;  
        SDL_BlitScaled(text_surface, NULL, screenSurface, rect);
    }

    void displayLarge(SDL_Surface* screenSurface, string message_text, SDL_Color &color, int x, int y){
        SDL_Surface* text_surface = TTF_RenderText_Solid(largeFont, message_text.c_str(), color);
        SDL_Rect* rect = new SDL_Rect();
        rect->w = text_surface->w;
        rect->h = text_surface->h;
        if (x == -1) rect->x = screenSurface->w / 2 - text_surface->w / 2;
        else rect->x = x;
        rect->y = y;  
        SDL_BlitScaled(text_surface, NULL, screenSurface, rect);
    }

    void displayMedium(SDL_Surface* screenSurface, string message_text, SDL_Color &color, int x, int y){
        SDL_Surface* text_surface = TTF_RenderText_Solid(mediumFont, message_text.c_str(), color);
        SDL_Rect* rect = new SDL_Rect();
        rect->w = text_surface->w;
        rect->h = text_surface->h;
        if (x == -1) rect->x = screenSurface->w / 2 - text_surface->w / 2;
        else rect->x = x;
        rect->y = y;  
        SDL_BlitScaled(text_surface, NULL, screenSurface, rect);
    }

    // static SDL_Surface *loadFont(string &font_path, int font_size, string &message_text, SDL_Color &color){
    //     TTF_Font *font = TTF_OpenFont(font_path.c_str(), font_size);
    //     if (!font){
    //         std::cerr << "failed to load font\n";
    //     }
    //     SDL_Surface *text_surface = TTF_RenderText_Solid(font, message_text.c_str(), color);
    //     if (!text_surface){
    //         cerr << "failed to create text surface\n";
    //     }
    //     return text_surface;
    // }
};

#endif // TEXT_HPP