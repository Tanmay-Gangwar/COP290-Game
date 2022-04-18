#include<iostream>
#include<SDL2/SDL.h>
#include"character.hpp"
#include"client.hpp"
#include"startScreen.hpp"
#include"maze.hpp"
#include"data.hpp"
#include"text.hpp"
#include"menu.hpp"
#include"score.hpp"

using namespace std;

// const int SCREEN_WIDTH = 640;
// const int SCREEN_HEIGHT = 560;

SDL_Window* window;
SDL_Surface* screenSurface;
SDL_Surface* background;

StartScreen startScreen;
Maze maze;
Text text;
Score score;

bool ShowMenu = false;
bool ShowScore = false;
bool ShowMap = false;

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
    // cerr << "Run has initiated\n";
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
    // cerr << "Doneloadting\n";
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
                SDL_Delay(200);
                transmit("Data#Terminate");
                return;
            }
            if (e.type == SDL_KEYDOWN){
                if (e.key.keysym.sym == SDLK_TAB) ShowMenu = true;
                else if (e.key.keysym.sym == SDLK_LSHIFT) ShowScore = true;
                else if (e.key.keysym.sym == SDLK_m) {
                    ShowMap = true;
                    MAZE_WIDTH = SCREEN_WIDTH / 100;
                    MAZE_HEIGHT = SCREEN_HEIGHT / 45;
                }
            }
            if (e.type == SDL_KEYUP){
                if (e.key.keysym.sym == SDLK_TAB) ShowMenu = false;
                else if (e.key.keysym.sym == SDLK_LSHIFT) ShowScore = false;
                else if (e.key.keysym.sym == SDLK_m) {
                    ShowMap = false;
                    MAZE_WIDTH = SCREEN_WIDTH / 16;
                    MAZE_HEIGHT = SCREEN_HEIGHT / 9;
                }
            }
            // player.move(e);
            if (!ShowMap){
                players[-1].move(e, maze.maze, menu.hints, menu.solvedBy, menu.points);
                std::string toSend = players[-1].getDataToSend(menu.solvedBy);
                // string toSend = to_string(players[-1].rect->x) + " " + to_string(players[-1].rect->y);
                transmit(toSend.c_str());
            }
        }
        // SDL_BlitScaled(maze.grass, NULL, screenSurface, backgroundRect);
        SDL_BlitScaled(background, NULL, screenSurface, backgroundRect);
        if (ShowMap) maze.draw(screenSurface, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        else maze.draw(screenSurface, players[-1].x, players[-1].y);
        if (ShowMenu) menu.draw(screenSurface);
        // player.draw(screenSurface);
        for (auto z: players){
            // cerr << z.first << "\n";
            if (!ShowMap) z.second.draw(screenSurface, players[-1].x, players[-1].y);
        }
        if (ShowScore) score.draw(screenSurface, players);
        // players[-1].draw(screenSurface);
        // if (players.find(5) != players.end()){
            // cerr << "Found\n";
            // players[5].draw(screenSurface);
        // }
        SDL_UpdateWindowSurface(window);
        // cerr << players.size() << "\n";
    }
}