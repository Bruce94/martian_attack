#ifndef MOVEMENTS_H
#define MOVEMENTS_H

#include "backbone.h"
#include "io.h"
#include "gui.h"
#include "init_dest.h"

void move_player(bool key[]);
void *move_bullet(void *arg);
void *move_enemy(void *arg);

#endif