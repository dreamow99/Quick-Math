#include <bits/stdc++.h>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <windows.h>
#include <chrono>
#include <thread>
#include "equation.h"
#include "drawer.h"
#include "Audio.h"

using namespace std;

SDL_Window* gWindow;
SDL_Renderer* gRenderer;
drawer gameDraw(gWindow, gRenderer);
Audio openSound;
Audio overSound;
Audio defuseSound;
Audio inGameSound;

void printIntro(){
    gameDraw.initWindow();
    //InitAudio();
    //gWindow = SDL_CreateWindow(gameName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT
    //                            , SDL_WINDOW_SHOWN);
    //gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    //Mix_Chunk *gScratch1 = nullptr;
    //gScratch1 = Mix_LoadWAV( "planting.WAV" );
    //Mix_PlayChannel( -1, gScratch1, 0 );
    //planSceneClass.play("planting.WAV");
    //Mix_PlayChannel(-1, planScene, 0);
    openSound.load("planting.wav");
    defuseSound.load("defusing.wav");
    openSound.play();
    for (int i = 0; i < 8; i++)
    {
        gameDraw.getImage("introScene1.png");
        SDL_Delay(100);
        gameDraw.getImage("introScene2.png");
        SDL_Delay(100);
    }
    gameDraw.getImage("introScene3.png");
    SDL_Delay(500);
    gameDraw.getImage("introScene4.png");
    SDL_Delay(250);
    gameDraw.getImage("introScene5.png");
    SDL_Delay(1600);
    defuseSound.play();
    gameDraw.getImage("defusing.png");
    SDL_Delay(1300);
    //Mix_FreeChunk( gScratch1 );
    //soundEffect.stop();
    defuseSound.stop();
    openSound.stop();
    SDL_RenderClear(gRenderer);
    //SDL_DestroyWindow(gWindow);
    //SDL_Quit();
    //gameDraw.reset();
}

string getStringEquation(equation eq)
{
    string finalString;
    stringstream ss;
    ss << eq.num1;
    finalString = ss.str();
    stringstream ss2;
    ss2 << eq.num2;
    finalString = finalString + " + " + ss2.str();
    stringstream ss3;
    ss3 << eq.num3;
    finalString = finalString + " = " + ss3.str();
    return finalString;
}

void printEq(equation eq){
    //SDL_DestroyRenderer(gRenderer);
    //SDL_DestroyWindow(gWindow);
    //SDL_Quit();
    //gameDraw.initWindow();
    gameDraw.getImage("defusing.png");
    inGameSound.load("imgame.wav");
    //gameDraw.getButton("wrong.png", 30, 400, 165, 145);
    //gameDraw.getButton("right.png", 230, 400, 165, 145);
    /*SDL_Rect timeLeft;
    timeLeft.x = 10;
    timeLeft.y = 10;
    timeLeft.w = 400;
    timeLeft.h = 10;
    SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
    SDL_RenderFillRect(gRenderer, &timeLeft);
    SDL_RenderPresent(gRenderer);*/
    //cout << eq.num1 << " + " << eq.num2 << " = " << eq.num3;
//cout << endl << "Y for yes. N for no" << endl;
    //gameDraw.clearRender();
    inGameSound.play();
    SDL_Delay(500);
    gameDraw.printEquation(getStringEquation(eq));
    gameDraw.getButton("wrong.png", 30, 400, 165, 145);
    gameDraw.getButton("right.png", 210, 400, 165, 145);
    gameDraw.clearRender();
    inGameSound.stop();
}

bool timer(){
    /*using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
    sleep_for(seconds(3));*/
    return true;
}

bool aKeyPressed(equation eq, int point)
{
    SDL_Event playerAns;
    char ansChar = ' ';
    Uint32 startTime = SDL_GetTicks();
    int lastWidth = 0;
    int countTick = 0;
    int key;
    unsigned int timeLimit;
    int step = 46;
    if (point < 5)
    {
        timeLimit = 2500;
        key = 30;
    }
        else{
            timeLimit = 1000;
            key = 10;
        }
    while(SDL_GetTicks() - startTime <= timeLimit){
        gameDraw.drawTimeLeft(lastWidth);
        if (SDL_PollEvent(&playerAns) != 0 && playerAns.type == SDL_KEYDOWN){
            if (playerAns.key.keysym.sym == SDLK_LEFT){
                ansChar = 'N';
                //cout << SDL_GetTicks() << endl;
                break;
            }
            if (playerAns.key.keysym.sym == SDLK_RIGHT){
                ansChar = 'Y';
                //cout << SDL_GetTicks() << endl;
                break;
            }
        }
        if (countTick > key)
        {
            lastWidth += step;
            key += countTick;
            countTick++;
        }
        countTick++;
        //cout << countTick << "& " << key << "w = " << lastWidth << endl;
    }
    if (ansChar == eq.key) return true;
    return false;
    /*char ans;
    cin >> ans;
    if (ans == eq.key) return true;
    return false;
*/
}

string getPointString(int point)
{
    string finalString;
    stringstream ss;
    ss << point;
    finalString = ss.str();
    return finalString;
}

void gameOver(int point);

bool timeDiscounting(equation eq, int point){
    //while (timer()){}
        if (aKeyPressed(eq, point)){
            return true;
        }
        return false;
    return false;
}

void startARound(int point)
{
    //gameDraw.reset();
    if (point == 0){
        printIntro();
    }
    else{
        gameDraw.resetAfterARound();
    }
    int lv;
    if (point > 5){
        if (point > 10){
            lv = 3;
        }
        else lv = 2;
    }
    else lv = 1;
    //cout << "level: " << lv << endl;
    equation eq;
    eq.getEquation(lv);
    printEq(eq);
    if (timeDiscounting(eq, point)){
        point++;
        //cout << endl << point << endl;
        //SDL_DestroyRenderer(gRenderer);
        //SDL_DestroyWindow(gWindow);
        //SDL_Quit();
        startARound(point);
    }
    else gameOver(point);
    //SDL_DestroyRenderer(gRenderer);
    //SDL_DestroyWindow(gWindow);
    //SDL_Quit();
    //cout << "Hello";
}

void printMenu()
{
    /*Mix_Chunk *gScratch = nullptr;
    gScratch = Mix_LoadWAV( "menuMusic.WAV" );
    Mix_PlayChannel( -1, gScratch, 0 );*/
    //soundEffect.play("menuMusic.WAV");
    const int statButtonX = 40;
    const int startButtonY = 300;
    const int startButtonW = 145;
    const int startButtonH = 63;
    const int quitButtonX = 210;
    const int quitButtonY = 300;
    const int quitButtonW = 145;
    const int quitButtonH = 62;
    /*cout << "Two plus two is four. Minus one that's three quick math" << endl << "press 1 for New game. 0 for Exit" << endl;
    int playerChoice;
    cin >> playerChoice;
    if (playerChoice) startARound(0);
    return;*/
    /*if (newGamePressed())
        startARound(0);
    if (exitGamePressed()){
        cout << "Are you sure?? 1 or 0" << endl;
    }*/
    gameDraw.getImage("menu.png");
    gameDraw.getButton("startButton.png", statButtonX, startButtonY, startButtonW, startButtonH);
    gameDraw.getButton("quitButton.png", quitButtonX, quitButtonY, quitButtonW, quitButtonH);
    bool quit = false;
    SDL_Event e;
    while (!quit){

        if (SDL_PollEvent(&e) != 0 && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT){
            int mouseX = e.button.x;
            int mouseY = e.button.y;
            if ((mouseX > statButtonX) && (mouseX < statButtonX + startButtonW) &&
                (mouseY > startButtonY) && (mouseY < startButtonY + startButtonH)){
                //Mix_FreeChunk( gScratch );
                //soundEffect.stop();
                //if (Mix_PlayingMusic())
                //Mix_HaltMusic();
                //Mix_FreeMusic( gSound );
                //gSound = nullptr;
               // Mix_Quit();
                SDL_RenderClear(gRenderer);
                SDL_DestroyRenderer(gRenderer);
                SDL_DestroyWindow(gWindow);
                SDL_Quit();
                startARound(0);
                quit = true;

            }
            if ((mouseX > quitButtonX) && (mouseX < quitButtonX + quitButtonW) &&
                (mouseY > quitButtonY) && (mouseY < quitButtonY + quitButtonH))
                quit = true;
        }
    }
    //soundEffect.stop();
    //if (Mix_PlayingMusic())
    //Mix_HaltMusic();
    //Mix_FreeMusic( gSound );
    //gSound = nullptr;
    //Mix_Quit();
    //Mix_FreeChunk( gScratch );
    SDL_RenderClear(gRenderer);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    //printMenu();
    gameDraw.initWindow();
    printMenu();
    return 0;
}

void gameOver(int point)
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
    gameDraw.initWindow();
    //cout << "Game over. Point: " << point;
//    gameOverSceneClass.play("gameOver.WAV
    overSound.load("gameOver.wav");
    overSound.play();
    gameDraw.getImage("endGame1.png");
    SDL_Delay(800);
    gameDraw.getImage("endGame2.png");
    SDL_Delay(800);
    gameDraw.getImage("endGame3.png");
    SDL_Delay(800);
    gameDraw.getImage("endGame4.png");
    gameDraw.printScore(getPointString(point));
    bool quit = false;
    SDL_Event e;
    while (!quit){
        if (SDL_PollEvent(&e) != 0 && e.type == SDL_KEYDOWN){
            if (e.key.keysym.sym == SDLK_ESCAPE){
                quit = true;
            }
            else
            {
                overSound.stop();
                SDL_RenderClear(gRenderer);
                SDL_DestroyRenderer(gRenderer);
                SDL_DestroyWindow(gWindow);
                SDL_Quit();
                startARound(0);
                quit = true;

            }
        }
    }
    overSound.stop();
    SDL_RenderClear(gRenderer);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}
