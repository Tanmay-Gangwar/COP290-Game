#ifndef MAZE_HPP
#define MAZE_HPP

#include<iostream>
#include<SDL2/SDL.h>
#include<vector>
#include"client.hpp"
#include"data.hpp"
using namespace std;

class Maze{
    public:

    SDL_Surface *road, *grass, *gate;
    vector<vector<char>> maze;
    SDL_Rect* rect;
    vector<pair<int, int>> gateCoord;
    Maze(){
        auto X = freopen("Images/IITDMaze.txt", "r", stdin);
        // if (X == NULL) cout << "Fucked up\n";
        maze = vector<vector<char>>(45, vector<char>(100));
        rect = new SDL_Rect();
        rect->w = MAZE_WIDTH;
        rect->h = MAZE_HEIGHT;
        for (int i = 0; i < 45; i++){
            for (int j = 0; j < 100; j++){
                cin >> maze[i][j];
                if (maze[i][j] == 'G') gateCoord.push_back({i, j});
            }
        }
        fclose(stdin);
        loadMedia();
    }

    void draw(SDL_Surface* screenSurface, int x, int y){
        // cerr << "Yes drawing it\n";
        SDL_Surface* image;
        for (int i = 0; i < 45; i++){
            for (int j = 0; j < 100; j++){
                rect->w = MAZE_WIDTH;
                rect->h = MAZE_HEIGHT;
                rect->x = j * rect->w + MAZE_WIDTH / 2 - (x + PLAYER_WIDTH / 2) + SCREEN_WIDTH / 2;
                rect->y = i * rect->h + MAZE_HEIGHT / 2 - (y + PLAYER_HEIGHT / 2) + SCREEN_HEIGHT / 2;
                if (maze[i][j] == 'X') image = grass;
                else if (maze[i][j] == 'R') image = road;
                else image = gate;
                SDL_BlitScaled(image, NULL, screenSurface, rect);
            }
        }
        // for (int i = row - 4; i < row + 5; i++){
        //     for (int j = col - 8; j < col + 8; j++){
        //         rect->x = (j - col + 8) * rect->w;
        //         rect->y = (i - row + 4) * rect->h;
        //         if (i < 0 || i >= 45 || j < 0 || j >= 100) image = grass;
        //         else if (maze[i][j] == 'X') image = grass;
        //         else if (maze[i][j] == 'R') image = road;
        //         else image = gate;
        //         SDL_BlitScaled(image, NULL, screenSurface, rect);
        //     }
        // }
    }

    void loadMedia(){
        road = SDL_LoadBMP("Images/road.bmp");
        grass = SDL_LoadBMP("Images/grass.bmp");
        gate = SDL_LoadBMP("Images/gate.bmp");
        // if (road == NULL || grass == NULL || gate == NULL) cerr << "Nah man\n";
    }
};



#endif // MAZE_HPP