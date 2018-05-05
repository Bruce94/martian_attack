#ifndef INIT_DEST_H
#define INIT_DEST_H

#include "backbone.h"
#include "gui.h"

//-----------------------------------------------------------------------------
// Initialize allegro an semaphores.
// Executed in main function.
//-----------------------------------------------------------------------------
void init(void);

//-----------------------------------------------------------------------------
//  Initialize the player's data.
//  Executed in load_function by a thread.
//-----------------------------------------------------------------------------
void *init_player(void *arg);

//-----------------------------------------------------------------------------
// Initialize enemy data, executed in load function by single thread.
// The argument contain the index of thread.
//-----------------------------------------------------------------------------
void *inititialize_enemy(void *arg);

//-----------------------------------------------------------------------------
// Initialize bullet's data when the player press the space bar to shoot enemy.
//-----------------------------------------------------------------------------
void init_bullet(int i);

//-----------------------------------------------------------------------------
// Deallocate allegro components and files.
// Executed in main function when the player close the game
//-----------------------------------------------------------------------------
void dest_allegro(void);

//-----------------------------------------------------------------------------
// Set false the alive bool variable of bullet.
// used when switching to a new level or when resetting the game
//-----------------------------------------------------------------------------
void reset_bullet(void);

//-----------------------------------------------------------------------------
// reset status of game
//-----------------------------------------------------------------------------
void reset_game(void);

#endif