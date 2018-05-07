#ifndef MOVEMENTS_H
#define MOVEMENTS_H

#include "backbone.h"
#include "io.h"
#include "gui.h"
#include "init_dest.h"

//-----------------------------------------------------------------------------
// Performs the movement of the player and controls the collision against the 
// border of the screen.
// Used by player_control function.
//-----------------------------------------------------------------------------
void move_player(bool key[]);

//-----------------------------------------------------------------------------
// Performs the movement of the single bullet and controls the collision
// against the border of the screen and against the enemies.
// If the bullet exit from the screen, his "alive" variable will set as false
// Executed by single bullet's thread, passing for argument the index
// of bullet.
//-----------------------------------------------------------------------------
void *move_bullet(void *arg);

//-----------------------------------------------------------------------------
// Performs the movement of the single enemy and controls the collision against
// the player. The enemy's movement consists of following the player taking his
// position and checking which quadrant he is in ([+,+],[+,-],[-,+],[-,-]), and 
// choosing at random one of the two directions dedicated to that quadrant.
// It's executed by single enemy's thread, passing for argument the index of 
// enemy.
//-----------------------------------------------------------------------------
void *move_enemy(void *arg);

#endif