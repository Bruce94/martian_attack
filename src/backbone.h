#ifndef BACKBONE_H
#define BACKBONE_H
// Allegro headers
#include<allegro5/allegro.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_color.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_acodec.h>
// C headers
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>
#include<string.h>
#include<sys/time.h>

//-----------------------------------------------------------------------------
// GRAPHIC CONSTANTS
//-----------------------------------------------------------------------------
#define     XWIN    750     // window X resolution
#define     YWIN    600     // window Y resolution
#define     XPWIN   200     // window X position
#define     YPWIN   40      // window Y position
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// TASK CONSTANTS
//-----------------------------------------------------------------------------
#define     PER     15      // task periods in ms
//#define     PRI     80      // task priority
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// GAME CONSTANTS
//-----------------------------------------------------------------------------
#define     MAX_ENEMIES    50      // number of enemies
#define     MAX_BULLETS    20      // max number of bullets on screeen
#define     ENEMY_W        42      // weight in pixel of single sprite of enemy
#define     ENEMY_H        38      // height in pixel of single sprite of enemy
#define     PLAYER_W       32      // weight in pixel of single sprite of player
#define     PLAYER_H       37      // height in pixel of single sprite of player
#define     BULLET_W       6       // weight in pixel of single sprite of bullet
#define     BULLET_H       16      // height in pixel of single sprite of bullet
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// GLOBAL ENUMS
//-----------------------------------------------------------------------------
// Direction state for the player and the enemies 
enum DIR { DIR_DOWN, DIR_UP, DIR_RIGHT, DIR_LEFT, DIR_STOP };

//--------------------------------------------------------------
// State of the game, used for the game_loop function 
// to perform different operations depending 
// on the phase in which the game is located.  
//--------------------------------------------------------------
enum GAME_STATE{ MENU, LOAD, PLAY, PAUSE, CONTROLS,
                 HIGH_SCORE, GAME_OVER, DEATH, QUIT};

// Values that will be attribuited to the game_loop key array
enum KEYS{ UP, DOWN, RIGHT, LEFT, ENTER, D, ESCAPE, SPACE, S, P };
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// GLOBAL STRUCTURES
//-----------------------------------------------------------------------------
struct  FIGURE_t    {   // Struct containing figure's data
        enum DIR        dir;              // direction of figure
        enum DIR        last_dir;
        float           movespeed;
        int             sourcex;          // Coordinate x for the region of the sheet
        int             sourcey;          // Coordinate x for the region of the sheet
        float           x;                // screen coordinate x
        float           y;                // screen coordinate y
        bool            alive;              
};

struct  BULLET_t    {
        struct FIGURE_t f;
        bool            explosion;
        int             anim;
};

struct  AUDIO_t     {   // Struct containing audio data
        ALLEGRO_SAMPLE_ID   id;
        ALLEGRO_SAMPLE      *enemy_death;
        ALLEGRO_SAMPLE      *shot;
        ALLEGRO_SAMPLE      *sample_lose;
        ALLEGRO_SAMPLE      *player_death;
        ALLEGRO_SAMPLE      *sample_game;
        ALLEGRO_SAMPLE      *monster_start;
        ALLEGRO_SAMPLE      *oh_yeah;
        ALLEGRO_SAMPLE      *game_loop;
};

struct  BITMAP_t    {   // Struct containing bitmap to use
        ALLEGRO_BITMAP  *bullet;
        ALLEGRO_BITMAP  *explosion;
        ALLEGRO_BITMAP  *background;
        ALLEGRO_BITMAP  *enemy;
        ALLEGRO_BITMAP  *player;
        ALLEGRO_BITMAP  *right_arrow;
        ALLEGRO_BITMAP  *left_arrow;
        ALLEGRO_BITMAP  *up_arrow;
        ALLEGRO_BITMAP  *down_arrow;
        ALLEGRO_BITMAP  *player_blood;
};

struct  FONT_t      {   // Struct containing font data
        ALLEGRO_FONT    *h1;
        ALLEGRO_FONT    *h2;
        ALLEGRO_FONT    *h3;
        ALLEGRO_FONT    *h4;
        ALLEGRO_FONT    *h5;

};             
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// GLOBAL VARIABLES
//-----------------------------------------------------------------------------
int                 score;
int                 level;
int                 n_enemies;
int                 dead_enemies;
struct FIGURE_t     player;
struct FIGURE_t     enemy[MAX_ENEMIES];
struct BULLET_t     bullet[MAX_BULLETS];
struct FONT_t       font;
struct AUDIO_t      audio;
struct BITMAP_t     bitmap;
ALLEGRO_DISPLAY     *display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_TIMER       *timer; 
sem_t               sem_enemies_init;
sem_t               sem_enemies;
sem_t               sem_bullet;
//-----------------------------------------------------------------------------

#endif