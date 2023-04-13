// rpsGame.h
// Module for the the high Low guessing game
// Rock Paper Scissors game 
// Depending on win or loss affects pet's mood
#ifndef RPS_GAME_H_
#define RPS_GAME_H_

// Begins Game, is blocking NOT A THREAD
// Will give back control when game is done 
// Takes ~10 seconds 
void rpsGame_Start(void);

#endif