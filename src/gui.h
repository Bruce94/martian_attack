#ifndef GUI_H
#define GUI_H

#include "backbone.h"


//-----------------------------------------------------------------------------
// Used from game_loop for print the menu.
// The int varible "menu" denote the option selected by the user.
//-----------------------------------------------------------------------------
void draw_screen_menu(int menu);

//-----------------------------------------------------------------------------
// Used from loading_function for print the countdown
//-----------------------------------------------------------------------------
void draw_countdown();

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void draw_play(void);

void draw_game_over(int h_score);

void draw_pause(void);

void draw_controls(void);

void draw_high_score(int h_score);

#endif