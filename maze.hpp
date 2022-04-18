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

    SDL_Surface* roads[11];
    SDL_Surface *road, *grass, *gate;
    SDL_Surface* yulu[4];
    vector<vector<char>> maze;
    SDL_Rect* rect;
    vector<pair<int, int>> gateCoord;
    SDL_Surface *bharti, *tennisCourt, *delhi16;
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
                if (maze[i][j] == 'J') {
                    // cerr << "Running\n";
                    rect->w = 4 * MAZE_WIDTH;
                    rect->h = 2 * MAZE_HEIGHT;
                }
                else if (maze[i][j] == 'H'){
                    rect->w = 6 * MAZE_WIDTH;
                    rect->h = 5 * MAZE_HEIGHT;
                }
                else if (maze[i][j] == 'F'){
                    rect->w = 3 * MAZE_WIDTH;
                    rect->h = 3 * MAZE_HEIGHT;
                }
                else {
                    rect->w = MAZE_WIDTH;
                    rect->h = MAZE_HEIGHT;
                }
                // rect->w = 4 * MAZE_WIDTH;
                // rect->h = 2 * MAZE_HEIGHT;

                rect->x = j * MAZE_WIDTH + MAZE_WIDTH / 2 - (x + PLAYER_WIDTH / 2) + SCREEN_WIDTH / 2;
                rect->y = i * MAZE_HEIGHT + MAZE_HEIGHT / 2 - (y + PLAYER_HEIGHT / 2) + SCREEN_HEIGHT / 2;
                if (maze[i][j] == 'R' && i > 0 && maze[i - 1][j] == 'R' && i < 44 && maze[i + 1][j] == 'R' && j > 0 && maze[i][j - 1] == 'R' && j < 99 && maze[i][j + 1] == 'R') image = roads[3];
                else if (maze[i][j] == 'R' && i > 0 && maze[i - 1][j] == 'R' && i < 44 && maze[i + 1][j] == 'R' && j > 0 && maze[i][j - 1] == 'R') image = roads[2];
                else if (maze[i][j] == 'R' && i > 0 && maze[i - 1][j] == 'R' && i < 44 && maze[i + 1][j] == 'R' && j < 99 && maze[i][j + 1] == 'R') image = roads[8];
                else if (maze[i][j] == 'R' && i > 0 && maze[i - 1][j] == 'R' && j > 0 && maze[i][j - 1] == 'R' && j < 99 && maze[i][j + 1] == 'R') image = roads[7];
                else if (maze[i][j] == 'R' && i < 44 && maze[i + 1][j] == 'R' && j > 0 && maze[i][j - 1] == 'R' && j < 99 && maze[i][j + 1] == 'R') image = roads[5];
                else if (maze[i][j] == 'R' && i > 0 && maze[i - 1][j] == 'R' && j > 0 && maze[i][j - 1] == 'R') image = roads[4];
                else if (maze[i][j] == 'R' && i < 44 && maze[i + 1][j] == 'R' && j > 0 && maze[i][j - 1] == 'R') image = roads[6];
                else if (maze[i][j] == 'R' && i > 0 && maze[i - 1][j] == 'R' && j < 99 && maze[i][j + 1] == 'R') image = roads[10];
                else if (maze[i][j] == 'R' && i < 44 && maze[i + 1][j] == 'R' && j < 99 && maze[i][j + 1] == 'R') image = roads[9];
                else if (maze[i][j] == 'R' && ((i > 0 && maze[i - 1][j] == 'R') || (i < 44 && maze[i + 1][j] == 'R'))) image = roads[0];
                else if (maze[i][j] == 'R' && ((j > 0 && maze[i][j - 1] == 'R') || (j < 99 && maze[i][j + 1] == 'R'))) image = roads[1];
                else if (maze[i][j] == 'X') image = grass;
                else if (maze[i][j] == 'J'){
                    if (maze[i - 1][j] != 'J' && maze[i][j - 1] != 'J') image = bharti;
                    else continue;
                }
                else if (maze[i][j] == 'H'){
                    if (maze[i - 1][j] != 'H' && maze[i][j - 1] != 'H') image = tennisCourt;
                    else continue;
                }
                else if (maze[i][j] == 'F'){
                    if (maze[i - 1][j] != 'F' && maze[i][j - 1] != 'F') image = delhi16;
                    else continue;
                }
                // else if (maze[i][j] == 'J') image = bharti;
                else if (maze[i][j] == 'Y'){
                    if (i > 0 && maze[i - 1][j] == 'Y') image = yulu[3];
                    else if (i < 44 && maze[i + 1][j] == 'Y') image = yulu[2];
                    else if (j > 0 && maze[i][j - 1] == 'Y') image = yulu[1];
                    else image = yulu[0];
                }
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
        for (int i = 0; i < 11; i++){
            string name = "Images/Road" + to_string(i + 1) + ".bmp";
            roads[i] = SDL_LoadBMP(name.c_str());
            if (roads[i] == NULL) cerr << "Failed\n";
        }
        yulu[0] = SDL_LoadBMP("Images/YuluStandHorizontal1.bmp");
        yulu[1] = SDL_LoadBMP("Images/YuluStandHorizontal2.bmp");
        yulu[2] = SDL_LoadBMP("Images/YuluStandVertical1.bmp");
        yulu[3] = SDL_LoadBMP("Images/YuluStandVertical2.bmp");
        bharti = SDL_LoadBMP("Images/Bharti.bmp");
        tennisCourt = SDL_LoadBMP("Images/TennisCourt.bmp");
        delhi16 = SDL_LoadBMP("Images/Delhi16.bmp");
        // if (bharti == NULL) cerr << "Failed to load\n";
        road = SDL_LoadBMP("Images/road.bmp");
        grass = SDL_LoadBMP("Images/grass.bmp");
        gate = SDL_LoadBMP("Images/gate.bmp");
        // if (road == NULL || grass == NULL || gate == NULL) cerr << "Nah man\n";
    }
};



#endif // MAZE_HPP