#ifndef INIT_DEST_H
#define INIT_DEST_H

#include "backbone.h"
#include "gui.h"

//-----------------------------------------------------------------------------
// Initialize allegro an semaphores.
// Executed in main function.
//-----------------------------------------------------------------------------
void init(void);

void *init_player(void *arg);

void *inititialize_enemy(void *arg);

void init_bullet(int i);

//-----------------------------------------------------------------------------
// function that deallocate allegro components and files
// Executed in ::main function when the player close the game
//-----------------------------------------------------------------------------
void dest_allegro(void);

void reset_bullet(void);

void reinit(void);

#endif