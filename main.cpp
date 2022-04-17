#include<iostream>
#include<SDL2/SDL.h>
#include"character.hpp"
#include"client.hpp"
#include"startScreen.hpp"
#include"maze.hpp"
#include"data.hpp"
using namespace std;

// const int SCREEN_WIDTH = 640;
// const int SCREEN_HEIGHT = 560;

SDL_Window* window;
SDL_Surface* screenSurface;
SDL_Surface* background;

StartScreen startScreen;
Maze maze;

SDL_Rect* backgroundRect;
// Character player;

void init();
void loadMedia();
void run();
void close();

int main(int argc, const char* argv){
    srand(time(0));
    init();
    // cerr << "Trying\n";
    // for (auto z: maze.maze){
    //     for (char c: z) cerr << c; cerr << "\n";
    // }
    // cerr << "Initialized\n";
    string characterColor = startScreen.runGame(screenSurface, window);
    if (characterColor == "QUIT") return 0;
    // cerr << "game ended\n";
    loadMedia();
    start(characterColor, maze.gateCoord);
    cerr << "Run has initiated\n";
    run();
    close();

    return 0;
}

void init(){
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    screenSurface = SDL_GetWindowSurface(window);

    backgroundRect = new SDL_Rect();
    backgroundRect->x = 0;
    backgroundRect->y = 0;
    backgroundRect->w = SCREEN_WIDTH;
    backgroundRect->h = SCREEN_HEIGHT;
}

void loadMedia(){
    background = SDL_LoadBMP("Images/GameBackground.bmp");
    // player = Character("Blue/Blue", SCREEN_WIDTH, SCREEN_HEIGHT);
    cerr << "Doneloadting\n";
}


void close(){
    // player.erase();
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}


void run(){
    // cerr << "Yes\n";
    SDL_Event e;
    int i = 0;
    // surface = surfaces[i];
    // SDL_Rect* rect = new SDL_Rect();
    // rect->x = 0;
    // rect->y = 0;
    // rect->w = SCREEN_WIDTH;
    // rect->h = SCREEN_HEIGHT;
    while (true){
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT) {
                transmit("Terminate");
                return;
            }
            // player.move(e);
            std::string toSend = players[-1].move(e, maze.maze);
            // string toSend = to_string(players[-1].rect->x) + " " + to_string(players[-1].rect->y);
            transmit(toSend.c_str());
        }
        // SDL_BlitScaled(maze.grass, NULL, screenSurface, backgroundRect);
        // SDL_BlitScaled(background, NULL, screenSurface, backgroundRect);
        maze.draw(screenSurface, players[-1].x, players[-1].y);
        // player.draw(screenSurface);
        for (auto z: players){
            // cerr << z.first << "\n";
            z.second.draw(screenSurface, players[-1].x, players[-1].y);
        }
        // players[-1].draw(screenSurface);
        // if (players.find(5) != players.end()){
            // cerr << "Found\n";
            // players[5].draw(screenSurface);
        // }
        SDL_UpdateWindowSurface(window);
        // cerr << players.size() << "\n";
    }
}