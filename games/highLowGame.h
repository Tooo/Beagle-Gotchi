// highLowGame.h
// Module for the the high Low guessing game
// Game where user will guess whether the number is higher or lower from the 14 seg display 
// Depending on win or loss affects pet's mood
#ifndef HIGH_LOW_GAME_H_
#define HIGH_LOW_GAME_H_

// Begins Game, is blocking NOT A THREAD
// Will give back control when game is done 
// Takes ~10 seconds 
void HighLowGame_Start(void);

#endif