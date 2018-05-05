#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "backbone.h"
#include "io.h"
#include "gui.h"
#include "init_dest.h"
#include "movements.h"

//-----------------------------------------------------------------------------
// This function is used by the MAIN and manages the game loop.
// The game is divided into different states:
// - MENU: menu of the game and initial state 
// - LOAD: the countdown is shown and the enemies are initialized 
// - PLAY: 
// - PAUSE: user can pause the game pressing P key 
// - CONTROLS: show the controls to use for play the game
// - HIGH_SCORE: show the high score
// - DEATH:
// - GAME_OVER: 
// - QUIT: close the loop
// - WIN:
//-----------------------------------------------------------------------------
void game_loop(void);

int menu;
int death_anim;
enum GAME_STATE game_state;
bool start_menu_song;
bool key[10];
#endif