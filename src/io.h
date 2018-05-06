#ifndef IO_H
#define IO_H

#include "backbone.h"

//-----------------------------------------------------------------------------
// This function set the boolean values of array "key" initializated in
// game_loop function depending on whether the key was pressed or released.
// This is executed in game_loop function, once to assign to setting true,
// if a key (among the default ones) is pressed, another time to assign 
// to false setting, when this key is released.
// - event: contain the event of key
// - key: array that contain the state of pressed or not pressed keys
// - setting: value to be given to the boolean field of key array
//-----------------------------------------------------------------------------
void update_keys(ALLEGRO_EVENT event, bool key[], bool setting);

//-----------------------------------------------------------------------------
// Write the high score obtained on the save file "save.txt"
// It's used at "GAME OVER" state when the user press ESC key
//-----------------------------------------------------------------------------
void save_score(void);

//-----------------------------------------------------------------------------
// Read the high score form the save file "save.txt"
// It's used from game loop function
//-----------------------------------------------------------------------------
int read_score(void);

#endif