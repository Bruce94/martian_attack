#include"init_dest.h"

//-----------------------------------------------------------------------------
// Load audio files.
// Executed in init_allegro function.
//-----------------------------------------------------------------------------
void init_audio(void){
    audio.sample_game = al_load_sample("data/sound/sample_game.wav");
    if(audio.sample_game == NULL)
        printf("Audio Error, sample_game.wav error!\n");
    audio.sample_lose = al_load_sample("data/sound/sample_lose.wav");
    if(audio.sample_lose == NULL)
        printf("Audio Error, sample_lose.wav error!\n");
    audio.shot = al_load_sample("data/sound/shot.wav");
    if(audio.shot == NULL)
        printf("Audio Error, shot.wav error!\n");
    audio.player_death = al_load_sample("data/sound/player_death1.wav");
    if(audio.player_death == NULL)
        printf("Audio Error, player_death1.wav error!\n");
    audio.oh_yeah = al_load_sample("data/sound/oh_yeah.wav");
    if(audio.oh_yeah == NULL)
        printf("Audio Error, oh_yeah.wav error!\n");
    audio.enemy_death = al_load_sample("data/sound/enemy_death.wav");
    if(audio.enemy_death == NULL)
        printf("Audio Error, enemy_death.wav error!\n");    
    audio.monster_start = al_load_sample("data/sound/monster_start.wav");
    if(audio.monster_start == NULL)
        printf("Audio Error, monster_start.wav error!\n");   
    audio.game_loop = al_load_sample("data/sound/game_loop.wav");
    if(audio.game_loop == NULL)
        printf("Audio Error, game_loop.wav error!\n");    
}

//-----------------------------------------------------------------------------
// Load font files.
// Executed in init_allegro function.
//-----------------------------------------------------------------------------
void init_font(void){
    font.h1 = al_load_font("data/font/DRIVEBY.TTF",50, 0);
    if (font.h1 == NULL){
        printf("Font Error, DRIVEBY.TTF error!\n");
    }
    font.h2 = al_load_font("data/font/ResagnictoBold.ttf",20, 0);
    font.h3 = al_load_font("data/font/ResagnictoBold.ttf",18, 0);
    font.h4 = al_load_font("data/font/ResagnictoBold.ttf",10, 0);
    if (font.h2 == NULL){
        printf("Font Error, ResagnictoBold.ttf error!\n");
    }
    font.h5 = al_load_font("data/font/basica.ttf",15, 0);
}


//-----------------------------------------------------------------------------
// Load image files.
// Executed in init_allegro function.
//-----------------------------------------------------------------------------
void init_bitmap(void){
    bitmap.bullet = al_load_bitmap("data/img/shoot_sprite.png");
	if (bitmap.bullet == NULL)
        printf("Bitmap Error, shoot_sprite error!\n");
    bitmap.background = al_load_bitmap("data/img/background.png");
    if (bitmap.background == NULL)
        printf("Bitmap Error, background error!\n");
    bitmap.explosion = al_load_bitmap("data/img/explosion_sprite.png");
    if (bitmap.explosion == NULL)
        printf("Bitmap Error, explosion_sprite error!\n");
    bitmap.enemy = al_load_bitmap("data/img/enemy_sprite.png");
    if (bitmap.enemy == NULL)
        printf("Bitmap Error, enemy_sprite error!\n");
    bitmap.player = al_load_bitmap("data/img/player_sprite.png");
    if (bitmap.player == NULL)
        printf("\n Bitmap Error, player_sprite.png error!");
    bitmap.right_arrow = al_load_bitmap("data/img/right_arrow.png");
    if (bitmap.right_arrow == NULL)
        printf("\n Bitmap Error, right_arrow.png error!");
    bitmap.left_arrow = al_load_bitmap("data/img/left_arrow.png");
    if (bitmap.left_arrow == NULL)
        printf("\n Bitmap Error, left_arrow.png error!");
    bitmap.up_arrow = al_load_bitmap("data/img/up_arrow.png");
    if (bitmap.up_arrow == NULL)
        printf("\n Bitmap Error, up_arrow.png error!");
    bitmap.down_arrow = al_load_bitmap("data/img/down_arrow.png");
    if (bitmap.down_arrow == NULL)
        printf("\n Bitmap Error, down_arrow.png error!");
}

//-----------------------------------------------------------------------------
// Initialize allegro components files.
// Executed in init function.
//-----------------------------------------------------------------------------
void init_allegro(void){
    if (!al_init())
        al_show_native_message_box(NULL,"Allegro Error","Error",
            "Could not initialize Allegro 5","Ok",ALLEGRO_MESSAGEBOX_ERROR);
    
    al_init_primitives_addon();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_acodec_addon();
    al_install_audio();
    al_reserve_samples(10);
    al_install_keyboard();

    al_set_new_display_flags(0);
    al_set_new_window_position(XPWIN,YPWIN);
    display = al_create_display(XWIN, YWIN);
    if(!display)
        al_show_native_message_box(display,"Display Error", "Error",
            "Display window could not be shown","Ok",ALLEGRO_MESSAGEBOX_ERROR);
    al_set_window_title(display, "Shoot Game");
    event_queue = al_create_event_queue();

    timer = al_create_timer(1.0/PER);
    // timer2 = al_create_timer(1.0 / FTIME);
    // timermov = al_create_timer(1.0 / FMOV);

    init_font();
    init_audio();
    init_bitmap();

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_start_timer(timer);
}


//-----------------------------------------------------------------------------
// Initialize allegro an semaphores.
// Executed in main function.
//-----------------------------------------------------------------------------
void init(void){
    init_allegro();

    sem_init(&sem_enemies_init, 0, 1);
	sem_init(&sem_enemies_move, 0, 1);
    sem_init(&sem_bullet,0,1);
    score = 0;
    level = 0;
}

void *init_player(void *arg){
    player.dir = DIR_UP;
    player.last_dir = DIR_UP;
    player.movespeed = 4;
    player.sourcex = 0;
    player.sourcey = 0;
    player.x = XWIN/2;
    player.y = YWIN/2;
    player.alive = true;
}

void bullet_x_y(struct FIGURE_t *b){
    if (b->dir == DIR_RIGHT){
        b->x = player.x + 37;
        b->y = player.y + 22;
    }
    else if (b->dir == DIR_LEFT){
        b->x = player.x;
        b->y = player.y + 7;
    }
    else if (b->dir == DIR_DOWN){
        b->x = player.x + 7;
        b->y = player.y + 37;
    }
    else if (b->dir == DIR_UP){
        b->x = player.x + 22;
        b->y = player.y;
    }
}

void bullet_sourcexy(struct FIGURE_t *b){
    b->sourcey = 0;
    if (b->dir == DIR_DOWN){
        b->sourcex = 0;
    }
    else if (b->dir == DIR_UP){
        b->sourcex = 6;
    }
    else if (b->dir == DIR_RIGHT){
        b->sourcex = 12;
    }
    else if (b->dir == DIR_LEFT){
        b->sourcex = 28;
    }
}

void init_bullet(int b_index){
    bullet[b_index].dir = player.last_dir;
    bullet[b_index].movespeed = 10;
    bullet_sourcexy(&bullet[b_index]);
    bullet_x_y(&bullet[b_index]);
    bullet[b_index].alive = true;    
}

void random_x_y(struct FIGURE_t *e){
    if (e->dir == DIR_UP){
        e->x = rand() % XWIN;
        e->y = YWIN;
    }
    else if (e->dir == DIR_DOWN){
        e->x = rand() % XWIN;
        e->y = -38;
    }
    else if (e->dir == DIR_LEFT){
        e->x = XWIN;
        e->y = rand() % YWIN;
    }
    else if (e->dir == DIR_RIGHT){
        e->x = -38;
        e->y = rand() % YWIN;
    }
}

//TODO: fare apparire dai bordi
void init_enemy(int e_index){
    enemy[e_index].dir = rand() % DIR_STOP;
    enemy[e_index].last_dir = enemy[e_index].dir;
    if (level <= 35)
        enemy[e_index].movespeed = 3 + (rand() % ((level / 5) + 1));
    else
        enemy[e_index].movespeed = 3 + (rand() % 36);
    enemy[e_index].sourcex = 0;
    enemy[e_index].sourcey = 0;
    random_x_y(&enemy[e_index]);
    enemy[e_index].alive = true;
}


//-----------------------------------------------------------------------------
// Initialize enemy data, executed by single thread.
// The argument contain the index of thread.
//-----------------------------------------------------------------------------
void *inititialize_enemy(void *arg){
    int i = *((int *) arg);
    sem_wait(&sem_enemies_init);
        init_enemy(i);
    sem_post(&sem_enemies_init);
}

//-----------------------------------------------------------------------------
// function that deallocate the loaded fonts
// Executed in ::dest_allegro function when the player close the game
//-----------------------------------------------------------------------------
void dest_font(void){
    al_destroy_font(font.h1);
    al_destroy_font(font.h2);
    al_destroy_font(font.h3);
    al_destroy_font(font.h4);
    al_destroy_font(font.h5);
}

//-----------------------------------------------------------------------------
// function that deallocate the loaded audio files
// Executed in ::dest_allegro function when the player close the game
//-----------------------------------------------------------------------------
void dest_audio(){
    #if defined(unix) || defined(__unix__) || defined(__unix)
        al_destroy_sample(audio.sample_game);
        al_destroy_sample(audio.sample_lose);
        al_destroy_sample(audio.shot);
        al_destroy_sample(audio.player_death);
        al_destroy_sample(audio.enemy_death);
        al_destroy_sample(audio.monster_start);
        al_destroy_sample(audio.oh_yeah);
        al_destroy_sample(audio.game_loop);

    #endif //defined unix
    #if defined(_WIN32)
        al_free(audio.sample_game);
        al_free(audio.sample_lose);
        al_free(audio.shoot);
        al_free(audio.player_death);
        al_free(audio.enemy_death);       
        al_free(audio.oh_yeah);
        al_free(audio.game_loop);

    #endif
}

void dest_allegro(void){
    dest_audio();
    dest_font();
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}

void reset_bullet(void){
    int i;
    for (i = 0; i < MAX_BULLETS; i ++){
        bullet[i].alive = false;
    }
}

void reinit(void){
    reset_bullet();
    score = 0;
    level = 0;
}

