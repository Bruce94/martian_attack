#ifndef GUI_H
#define GUI_H

#include "backbone.h"

//-----------------------------------------------------------------------------
// Used from game_loop for print the menu.
// The int varible "menu" denote the option selected by the user.
//-----------------------------------------------------------------------------
void draw_screen_menu(int menu);
void draw_countdown();

//-----------------------------------------------------------------------------
// Draw all the components of the game including the player character, 
// the enemies, the bullets the score and the level.
//-----------------------------------------------------------------------------
void draw_play(void);

//-----------------------------------------------------------------------------
// Draw the player death animation before the game over screen
//-----------------------------------------------------------------------------
void draw_player_death(int death_anim);
void draw_game_over(int h_score);
void draw_pause(void);
void draw_controls(void);
void draw_high_score(int h_score);

#endif