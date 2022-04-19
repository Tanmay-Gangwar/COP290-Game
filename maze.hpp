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
    SDL_Surface *bharti, *tennisCourt, *delhi16, *playground, *karakoram;
    SDL_Surface *acad, *hostel, *mart, *hostelLeft, *hostelDown, *chaayos;
    SDL_Surface *apartment, *Grass, *house, *ccd, *mainBuilding, *library;
    SDL_Surface *lhc, *biotechLawn, *amaltas, *oat, *hospital, *blank;
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
                else if (maze[i][j] == 'P'){
                    rect->w = 22 * MAZE_WIDTH;
                    rect->h = 7 * MAZE_HEIGHT;
                }
                else if (maze[i][j] == 'A'){
                    rect->w = 4 * MAZE_WIDTH;
                    rect->h = 6 * MAZE_HEIGHT;
                }
                else if (maze[i][j] == '1' || maze[i][j] == '2' || maze[i][j] == '3' || maze[i][j] == '4' || maze[i][j] == '6' || maze[i][j] == '7' || maze[i][j] == '8' || maze[i][j] == '+'){
                    rect->w = 6 * MAZE_WIDTH;
                    rect->h = 6 * MAZE_HEIGHT;
                }
                else if (maze[i][j] == '9' || maze[i][j] == 'V'){
                    rect->w = 7 * MAZE_WIDTH;
                    rect->h = 5 * MAZE_HEIGHT;
                }
                else if (maze[i][j] == 'D' || maze[i][j] == 'O' || maze[i][j] == '0' || maze[i][j] == 'Z'){
                    rect->w = 2 * MAZE_WIDTH;
                    rect->h = 2 * MAZE_HEIGHT;
                }
                else if (maze[i][j] == '?'){
                    rect->w = 2 * MAZE_WIDTH;
                    rect->h = 3 * MAZE_HEIGHT;
                }
                else if (maze[i][j] == 'C'){
                    rect->w = 7 * MAZE_WIDTH;
                    rect->h = 5 * MAZE_HEIGHT;
                }
                else if (maze[i][j] == '$'){
                    rect->w = 1 * MAZE_WIDTH;
                    rect->h = 2 * MAZE_HEIGHT;
                }
                else if (maze[i][j] == 'B'){
                    rect->w = 2 * MAZE_WIDTH;
                    rect->h = 1 * MAZE_HEIGHT;
                }
                else if (maze[i][j] == 'L'){
                    rect->w = 5 * MAZE_WIDTH;
                    rect->h = 5 * MAZE_HEIGHT;
                }
                else if (maze[i][j] == 'M'){
                    rect->w = 7 * MAZE_WIDTH;
                    rect->h = 2 * MAZE_HEIGHT;
                }
                else if (maze[i][j] == 'I'){
                    rect->w = 10 * MAZE_WIDTH;
                    rect->h = 3 * MAZE_HEIGHT;
                }
                else if (maze[i][j] == 'S'){
                    rect->w = 5 * MAZE_WIDTH;
                    rect->h = 6 * MAZE_HEIGHT;
                }
                else if (maze[i][j] == 'Q' || maze[i][j] == '5'){
                    rect->w = 6 * MAZE_WIDTH;
                    rect->h = 6 * MAZE_HEIGHT;
                }
                else if (maze[i][j] == 'T'){
                    rect->w = 5 * MAZE_WIDTH;
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
                else if (maze[i][j] == 'P'){
                    if (maze[i - 1][j] != 'P' && maze[i][j - 1] != 'P') image = playground;
                    else continue;
                }
                else if (maze[i][j] == 'Q'){
                    if (maze[i - 1][j] != 'Q' && maze[i][j - 1] != 'Q') image = amaltas;
                    else continue;
                }
                else if (maze[i][j] == 'A'){
                    if (maze[i - 1][j] != 'A' && maze[i][j - 1] != 'A') image = acad;
                    else continue;
                }
                else if (maze[i][j] == '1'){
                    if (maze[i - 1][j] != '1' && maze[i][j - 1] != '1') image = hostel;
                    else continue;
                }
                else if (maze[i][j] == '2'){
                    if (maze[i - 1][j] != '2' && maze[i][j - 1] != '2') image = hostel;
                    else continue;
                }
                else if (maze[i][j] == '3'){
                    if (maze[i - 1][j] != '3' && maze[i][j - 1] != '3') image = hostel;
                    else continue;
                }
                else if (maze[i][j] == '4'){
                    if (maze[i - 1][j] != '4' && maze[i][j - 1] != '4') image = hostel;
                    else continue;
                }
                else if (maze[i][j] == '5'){
                    if (maze[i - 1][j] != '5' && maze[i][j - 1] != '5') image = hostelLeft;
                    else continue;
                }
                else if (maze[i][j] == '6'){
                    if (maze[i - 1][j] != '6' && maze[i][j - 1] != '6') image = hostelLeft;
                    else continue;
                }
                else if (maze[i][j] == '7'){
                    if (maze[i - 1][j] != '7' && maze[i][j - 1] != '7') image = hostelLeft;
                    else continue;
                }
                else if (maze[i][j] == '8'){
                    if (maze[i - 1][j] != '8' && maze[i][j - 1] != '8') image = hostelLeft;
                    else continue;
                }
                else if (maze[i][j] == '+'){
                    if (maze[i - 1][j] != '+' && maze[i][j - 1] != '+') image = hostelLeft;
                    else continue;
                }
                else if (maze[i][j] == '9'){
                    if (maze[i - 1][j] != '9' && maze[i][j - 1] != '9') image = hostelDown;
                    else continue;
                }
                else if (maze[i][j] == 'V'){
                    if (maze[i - 1][j] != 'V' && maze[i][j - 1] != 'V') image = hostelDown;
                    else continue;
                }
                else if (maze[i][j] == '?'){
                    if (maze[i - 1][j] != '?' && maze[i][j - 1] != '?') image = chaayos;
                    else continue;
                }
                else if (maze[i][j] == 'S'){
                    if (maze[i - 1][j] != 'S' && maze[i][j - 1] != 'S') image = oat;
                    else continue;
                }
                else if (maze[i][j] == 'L'){
                    if (maze[i - 1][j] != 'L' && maze[i][j - 1] != 'L') image = lhc;
                    else continue;
                }
                else if (maze[i][j] == 'H'){
                    if (maze[i - 1][j] != 'H' && maze[i][j - 1] != 'H') image = tennisCourt;
                    else continue;
                }
                else if (maze[i][j] == 'C'){
                    if (maze[i - 1][j] != 'C' && maze[i][j - 1] != 'C') image = Grass;
                    else continue;
                }
                else if (maze[i][j] == 'T'){
                    if (maze[i - 1][j] != 'T' && maze[i][j - 1] != 'T') image = hospital;
                    else continue;
                }
                else if (maze[i][j] == 'Z'){
                    if (maze[i - 1][j] != 'Z' && maze[i][j - 1] != 'Z') image = mart;
                    else continue;
                }
                else if (maze[i][j] == 'O'){
                    if (maze[i - 1][j] != 'O' && maze[i][j - 1] != 'O') image = apartment;
                    else continue;
                }
                else if (maze[i][j] == 'D'){
                    if (maze[i - 1][j] != 'D' && maze[i][j - 1] != 'D') image = mart;
                    else continue;
                }
                else if (maze[i][j] == 'F'){
                    if (maze[i - 1][j] != 'F' && maze[i][j - 1] != 'F') image = delhi16;
                    else continue;
                }
                else if (maze[i][j] == '0'){
                    if (maze[i - 1][j] != '0' && maze[i][j - 1] != '0') image = house;
                    else continue;
                }
                else if (maze[i][j] == '$'){
                    if (maze[i - 1][j] != '$' && maze[i][j - 1] != '$') image = ccd;
                    else continue;
                }
                else if (maze[i][j] == 'B'){
                    if (maze[i - 1][j] != 'B' && maze[i][j - 1] != 'B') image = library;
                    else continue;
                }
                else if (maze[i][j] == 'I'){
                    if (maze[i - 1][j] != 'I' && maze[i][j - 1] != 'I') image = biotechLawn;
                    else continue;
                }
                else if (maze[i][j] == 'M'){
                    if (maze[i - 1][j] != 'M' && maze[i][j - 1] != 'M') image = mainBuilding;
                    else continue;
                }
                // else if (maze[i][j] == 'J') image = bharti;
                else if (maze[i][j] == 'Y'){
                    if (i > 0 && maze[i - 1][j] == 'Y') image = yulu[3];
                    else if (i < 44 && maze[i + 1][j] == 'Y') image = yulu[2];
                    else if (j > 0 && maze[i][j - 1] == 'Y') image = yulu[1];
                    else image = yulu[0];
                }
                else if (maze[i][j] == 'W') image = blank;
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
            // if (roads[i] == NULL) cerr << "Failed\n";
        }
        yulu[0] = SDL_LoadBMP("Images/YuluStandHorizontal1.bmp");
        yulu[1] = SDL_LoadBMP("Images/YuluStandHorizontal2.bmp");
        yulu[2] = SDL_LoadBMP("Images/YuluStandVertical1.bmp");
        yulu[3] = SDL_LoadBMP("Images/YuluStandVertical2.bmp");
        bharti = SDL_LoadBMP("Images/Bharti.bmp");
        tennisCourt = SDL_LoadBMP("Images/TennisCourt.bmp");
        delhi16 = SDL_LoadBMP("Images/Delhi16.bmp");
        playground = SDL_LoadBMP("Images/Playground.bmp");
        karakoram = SDL_LoadBMP("Images/Karakoram.bmp");
        acad = SDL_LoadBMP("Images/AcadArea.bmp");
        hostel = SDL_LoadBMP("Images/Hostel.bmp");
        hostelLeft = SDL_LoadBMP("Images/HostelLeft.bmp");
        hostelDown = SDL_LoadBMP("Images/HostelDown.bmp");
        mart = SDL_LoadBMP("Images/Mart.bmp");
        chaayos = SDL_LoadBMP("Images/Chaayos.bmp");
        apartment = SDL_LoadBMP("Images/Apartment.bmp");
        house = SDL_LoadBMP("Images/house.bmp");
        ccd = SDL_LoadBMP("Images/CCD.bmp");
        mainBuilding = SDL_LoadBMP("Images/MainBuilding.bmp");
        library = SDL_LoadBMP("Images/Library.bmp");
        amaltas = SDL_LoadBMP("Images/Amaltas.bmp");
        lhc = SDL_LoadBMP("Images/LHCNew.bmp");
        oat = SDL_LoadBMP("Images/OAT.bmp");
        hospital = SDL_LoadBMP("Images/Hospital.bmp");
        blank = SDL_LoadBMP("Images/White.bmp");
        // if (bharti == NULL) cerr << "Failed to load\n";
        road = SDL_LoadBMP("Images/road.bmp");
        grass = SDL_LoadBMP("Images/grass.bmp");
        Grass = SDL_LoadBMP("Images/Grass.bmp");
        gate = SDL_LoadBMP("Images/gate.bmp");
        biotechLawn = SDL_LoadBMP("Images/BiotechLawn.bmp");
        // if (road == NULL || grass == NULL || gate == NULL) cerr << "Nah man\n";
    }
};



#endif // MAZE_HPP