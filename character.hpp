#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include<iostream>
#include<SDL2/SDL.h>
#include<vector>
#include"data.hpp"
#include<ctime>

using namespace std;
class Character{
    public:
    SDL_Rect *rect;
    SDL_Surface* left[3], *right[3], *up[3], *down[3];
    SDL_Surface* bicycles[4];
    int imgCounter;
    bool pressed;
    int direction;
    int x, y;
    string color;
    bool onBicycle;
    int horizontalBikeWidth = 80;
    int bikeHight = 50;
    int verticalBikeWidth = 40;
    SDL_Rect* bikeRect;
    time_t lastUpdated;
    int score;

    Character(){}
    
    Character(std::string color, vector<pair<int, int>> gateCoord){
        rect = new SDL_Rect();
        int gate = rand() % 6;
        // cerr << "1\n";
        rect->w = PLAYER_WIDTH;
        rect->h = PLAYER_HEIGHT;
        rect->x = SCREEN_WIDTH / 2 - rect->w / 2;
        rect->y = SCREEN_HEIGHT / 2 - rect->h / 2;
        x = gateCoord[gate].second * MAZE_WIDTH + rect->w / 2;
        // x = 0;
        y = gateCoord[gate].first * MAZE_HEIGHT + rect->h / 2;

        bikeRect = new SDL_Rect();
        // y = 0;
        // cerr << x << " " << y << "\n";
        // cerr << "1\n";
        // rect->x = 0;
        // rect->y = 0;
        // cerr << "1\n";
        loadImages(color);
        imgCounter = 3;
        direction = 0;
        pressed = false;
        onBicycle = false;
        lastUpdated = time(0);
        score = 0;
        // cerr << "1\n";
    }

    void loadImages(std::string color){
        // cerr << color << "\n";
        this->color = color;
        std::string Up[3], Down[3], Left[3], Right[3];
        Up[0]    = "Images/" + color + "Up0.bmp";
        Up[1]    = "Images/" + color + "Up1.bmp";
        Up[2]    = "Images/" + color + "Up2.bmp";
        Down[0]  = "Images/" + color + "Down0.bmp";
        Down[1]  = "Images/" + color + "Down1.bmp";
        Down[2]  = "Images/" + color + "Down2.bmp";
        Left[0]  = "Images/" + color + "Left0.bmp";
        Left[1]  = "Images/" + color + "Left1.bmp";
        Left[2]  = "Images/" + color + "Left2.bmp";
        Right[0] = "Images/" + color + "Right0.bmp";
        Right[1] = "Images/" + color + "Right1.bmp";
        Right[2] = "Images/" + color + "Right2.bmp";
        bicycles[0] = SDL_LoadBMP("Images/BikeLeft.bmp");
        bicycles[1] = SDL_LoadBMP("Images/BikeRight.bmp");
        bicycles[2] = SDL_LoadBMP("Images/BikeUp.bmp");
        bicycles[3] = SDL_LoadBMP("Images/BikeDown.bmp");

        for (int i = 0; i < 3; i++){
            left[i]  = SDL_LoadBMP(Left[i].c_str());
            right[i] = SDL_LoadBMP(Right[i].c_str());
            up[i]    = SDL_LoadBMP(Up[i].c_str());
            down[i]  = SDL_LoadBMP(Down[i].c_str());
            // if (left[i] == NULL || right[i] == NULL || up[i] == NULL || down[i] == NULL) std::cerr << "Flop\n";
        }
    }

    void move(SDL_Event &e, vector<vector<char>> &maze, vector<pair<string, char>> &hints, vector<string> &solvedBy, vector<int> &points){
        lastUpdated = time(0);
        if (e.type == SDL_KEYDOWN){
            if (e.key.keysym.sym == SDLK_LEFT) {
                int i = y / MAZE_HEIGHT;
                int j = (x - (onBicycle ? 20: 10)) / MAZE_WIDTH;
                if (j > 0 && maze[i][j] != 'X') x -= (onBicycle ? 20: 10);
                direction = 0;
            }
            else if (e.key.keysym.sym == SDLK_RIGHT) {
                int i = y / MAZE_HEIGHT;
                int j = (x + (onBicycle ? 20: 10)) / MAZE_WIDTH;
                if (j < 100 && maze[i][j] != 'X') x += (onBicycle ? 20: 10);
                direction = 1;
            }
            else if (e.key.keysym.sym == SDLK_UP){
                int i = (y - (onBicycle ? 20: 10)) / MAZE_HEIGHT;
                int j = x / MAZE_WIDTH;
                if (i > 0 && maze[i][j] != 'X') y -= (onBicycle ? 20: 10);
                direction = 2;
            }
            else if (e.key.keysym.sym == SDLK_DOWN){
                int i = (y + (onBicycle ? 20: 10)) / MAZE_HEIGHT;
                int j = x / MAZE_WIDTH;
                if (i < 45 && maze[i][j] != 'X') y += (onBicycle ? 20: 10);
                direction = 3;
            }
            else if (e.key.keysym.sym == SDLK_SPACE){
                int i = y / MAZE_HEIGHT;
                int j = x / MAZE_WIDTH;
                if (maze[i][j] == 'Y') onBicycle = !onBicycle;
            }
            else if (e.key.keysym.sym == SDLK_0 || e.key.keysym.sym == SDLK_KP_0){
                int i = y / MAZE_HEIGHT;
                int j = x / MAZE_WIDTH;
                if (maze[i][j] == hints[0].second && solvedBy[0] == "None"){
                    score += points[0];
                    solvedBy[0] = color;
                }
            }
            else if (e.key.keysym.sym == SDLK_1 || e.key.keysym.sym == SDLK_KP_1){
                int i = y / MAZE_HEIGHT;
                int j = x / MAZE_WIDTH;
                if (maze[i][j] == hints[1].second && solvedBy[1] == "None"){
                    score += points[1];
                    solvedBy[1] = color;
                }
            }
            else if (e.key.keysym.sym == SDLK_2 || e.key.keysym.sym == SDLK_KP_2){
                int i = y / MAZE_HEIGHT;
                int j = x / MAZE_WIDTH;
                if (maze[i][j] == hints[2].second && solvedBy[2] == "None"){
                    score += points[2];
                    solvedBy[2] = color;
                }
            }
            else if (e.key.keysym.sym == SDLK_3 || e.key.keysym.sym == SDLK_KP_3){
                int i = y / MAZE_HEIGHT;
                int j = x / MAZE_WIDTH;
                if (maze[i][j] == hints[3].second && solvedBy[3] == "None"){
                    score += points[3];
                    solvedBy[3] = color;
                }
            }
            else if (e.key.keysym.sym == SDLK_4 || e.key.keysym.sym == SDLK_KP_4){
                int i = y / MAZE_HEIGHT;
                int j = x / MAZE_WIDTH;
                if (maze[i][j] == hints[4].second && solvedBy[4] == "None"){
                    score += points[4];
                    solvedBy[4] = color;
                }
            }
            else if (e.key.keysym.sym == SDLK_5 || e.key.keysym.sym == SDLK_KP_5){
                int i = y / MAZE_HEIGHT;
                int j = x / MAZE_WIDTH;
                if (maze[i][j] == hints[5].second && solvedBy[5] == "None"){
                    score += points[5];
                    solvedBy[5] = color;
                }
            }
            else if (e.key.keysym.sym == SDLK_6 || e.key.keysym.sym == SDLK_KP_6){
                int i = y / MAZE_HEIGHT;
                int j = x / MAZE_WIDTH;
                if (maze[i][j] == hints[6].second && solvedBy[6] == "None"){
                    score += points[6];
                    solvedBy[6] = color;
                }
            }
            else if (e.key.keysym.sym == SDLK_7 || e.key.keysym.sym == SDLK_KP_7){
                int i = y / MAZE_HEIGHT;
                int j = x / MAZE_WIDTH;
                if (maze[i][j] == hints[7].second && solvedBy[7] == "None"){
                    score += points[7];
                    solvedBy[7] = color;
                }
            }
            else if (e.key.keysym.sym == SDLK_8 || e.key.keysym.sym == SDLK_KP_8){
                int i = y / MAZE_HEIGHT;
                int j = x / MAZE_WIDTH;
                if (maze[i][j] == hints[8].second && solvedBy[8] == "None"){
                    score += points[8];
                    solvedBy[8] = color;
                }
            }
            else if (e.key.keysym.sym == SDLK_9 || e.key.keysym.sym == SDLK_KP_9){
                int i = y / MAZE_HEIGHT;
                int j = x / MAZE_WIDTH;
                if (maze[i][j] == hints[9].second && solvedBy[9] == "None"){
                    score += points[9];
                    solvedBy[9] = color;
                }
            }
            pressed = true;
            imgCounter = (imgCounter + 1) % 3;
        }
        else if (e.type == SDL_KEYUP) pressed = false;
    }

    string getDataToSend(vector<string> &solvedBy){
        string toSend = "Data#";
        toSend += to_string(x);
        toSend += "#";
        toSend += to_string(y);
        toSend += "#";
        toSend += to_string(imgCounter);
        toSend += "#";
        toSend += to_string(direction);
        toSend += "#";
        toSend += color;
        toSend += "#";
        toSend += to_string(onBicycle);
        toSend += "#";
        toSend += to_string(score);
        toSend += "#";
        toSend += to_string(solvedBy.size());
        for (int i = 0; i < solvedBy.size(); i++){
            toSend += "#";
            toSend += solvedBy[i];
        }
        toSend += "#";
        return toSend;
    }

    SDL_Surface* getImage(){
        if (direction == 0) return left[imgCounter];
        if (direction == 1) return right[imgCounter];
        if (direction == 2) return up[imgCounter];
        if (direction == 3) return down[imgCounter];
    }

    void draw(SDL_Surface* screen, int Otherx, int Othery){
        if (time(0) - lastUpdated > 5) return;
        // cerr << "MyCoord: " << x << " " << y << "\n";
        // cerr << "OtCoord: " << Otherx << " " << Othery << "\n";
        rect->w = PLAYER_WIDTH;
        rect->h = PLAYER_HEIGHT;
        rect->x = SCREEN_WIDTH / 2 + rect->w / 2 + x - Otherx;
        rect->y = SCREEN_HEIGHT / 2 + rect->h / 2 + y - Othery + (onBicycle ? 10: 0);
        auto z = getImage();
        // if (z == NULL) std::cerr << "fucked up\n";
        // else std::cerr << "again fucked up\n";
        if (onBicycle){
            if (direction == 0){
                bikeRect->w = horizontalBikeWidth;
                bikeRect->h = bikeHight;
                bikeRect->x = SCREEN_WIDTH / 2 + - bikeRect->w / 4 + x - Otherx;
                bikeRect->y = SCREEN_HEIGHT / 2 + 3 * bikeRect->h / 4 + y - Othery;
                SDL_BlitScaled(bicycles[direction], NULL, screen, bikeRect);
                SDL_BlitScaled(z, NULL, screen, rect);
            }
            else if (direction == 1){
                bikeRect->w = horizontalBikeWidth;
                bikeRect->h = bikeHight;
                bikeRect->x = SCREEN_WIDTH / 2 + bikeRect->w / 8 + x - Otherx;
                bikeRect->y = SCREEN_HEIGHT / 2 + 3 * bikeRect->h / 4 + y - Othery;
                SDL_BlitScaled(bicycles[direction], NULL, screen, bikeRect);
                SDL_BlitScaled(z, NULL, screen, rect);
            }
            else if (direction == 2){
                bikeRect->w = verticalBikeWidth;
                bikeRect->h = bikeHight;
                bikeRect->x = SCREEN_WIDTH / 2 + bikeRect->w / 2 + x - Otherx;
                bikeRect->y = SCREEN_HEIGHT / 2 + bikeRect->h / 2 + y - Othery;
                SDL_BlitScaled(bicycles[direction], NULL, screen, bikeRect);
                SDL_BlitScaled(z, NULL, screen, rect);
            }
            else {
                bikeRect->w = verticalBikeWidth;
                bikeRect->h = bikeHight;
                bikeRect->x = SCREEN_WIDTH / 2 + bikeRect->w / 2 + x - Otherx;
                bikeRect->y = SCREEN_HEIGHT / 2 + bikeRect->h / 2 + y - Othery;
                SDL_BlitScaled(z, NULL, screen, rect);
                SDL_BlitScaled(bicycles[direction], NULL, screen, bikeRect);
            }
        }
        else SDL_BlitScaled(z, NULL, screen, rect);
        // SDL_BlitSurface(getImage(), NULL, screen, rect);
    }

    void erase(){
        for (int i = 0; i < 3; i++){
            SDL_FreeSurface(up[i]);
            SDL_FreeSurface(down[i]);
            SDL_FreeSurface(left[i]);
            SDL_FreeSurface(right[i]);
            up[i] = NULL;
            down[i] = NULL;
            left[i] = NULL;
            right[i] = NULL;
        }
    }
};
    
#endif // CHARACTER_HPP