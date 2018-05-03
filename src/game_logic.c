#include"game_logic.h"

void update_level(void){
    level ++;
    dead_enemies = 0;
    reset_bullet();
    n_enemies = 10 + level - 1;
    if (n_enemies > MAX_ENEMIES)
        n_enemies = MAX_ENEMIES;
    al_stop_sample(&audio.id);
}

//-----------------------------------------------------------------------------
// The menu_function handle the user interaction with the "MENU" game phase
// here the user can go up and down on the menu options and select one of these
// with ENTER key.
// This function is used in game_loop function.
//-----------------------------------------------------------------------------
void menu_function(){
    if (!start_menu_song){
        if(!al_play_sample(audio.sample_game, 1.0, 0.0, 1, ALLEGRO_PLAYMODE_LOOP, &audio.id))
            printf("Audio Error! - does not start sample_game audio\n");
        start_menu_song = true;
    }
    if (key[DOWN]){
        al_play_sample(audio.shot, 1.0, 0.0, 1, ALLEGRO_PLAYMODE_ONCE , 0);
        menu ++;
        if(menu > 3)
            menu = 3;
        key[DOWN] = false;
    }
   else if (key[UP]){
        al_play_sample(audio.shot, 1.0, 0.0, 1, ALLEGRO_PLAYMODE_ONCE , 0);
        menu --;
        if(menu < 1)
            menu = 1;
        key[UP] = false;
    }
    if (key[ENTER]){
        key[ENTER] = false;
        switch (menu){
        case 1:
            al_stop_sample(&audio.id);
            start_menu_song = false;
            update_level();
            if (!al_play_sample(audio.monster_start, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,0))
                printf("Audio Error! - does not start monster_start udio\n");
            game_state = LOAD;
            break;
        case 2:
            game_state = CONTROLS;
            break;
        case 3:
            game_state = HIGH_SCORE;
            break;
        }
    }
    if (key[ESCAPE]){
        game_state = QUIT;
        key[ESCAPE] = false;
    }
}

//-----------------------------------------------------------------------------
// The loading_function is used to initialize enemies and player data and show 
// the countdown of the game. The initialization is managed by n_enemies + 1 
// pthreads, at the same time the main thread will show the countdown and then 
// wait for the end of their execution to continue passing to the PLAY phase.
// This function is used in game_loop function.
//-----------------------------------------------------------------------------
void load_function(void){
    int i;
    pthread_attr_t attr;
    pthread_t p[n_enemies+1];    

    pthread_attr_init(&attr);
    for (i = 0; i < n_enemies; i++){
        int *arg = malloc(sizeof(*arg));
        if (arg == NULL)
            printf("Couldn't allocate memory for thread arg.\n");
        *arg = i;
		pthread_create(&p[i], &attr, inititialize_enemy, arg);
    }
    pthread_create(&p[n_enemies], &attr, init_player, NULL);

    pthread_attr_destroy(&attr);

    al_stop_timer(timer);
    draw_countdown(font);
    al_start_timer(timer);
    
    for (i = 0; i < n_enemies+1; i++)
	    pthread_join(p[i], NULL);
    if(!al_play_sample(audio.game_loop, 0.5, 0.0, 1, ALLEGRO_PLAYMODE_LOOP, &audio.id))
        printf("Audio Error! - does not start sample_game audio\n");
    game_state = PLAY;
}

void shot_bullet(void){
    int i;
    for(i = 0; i < MAX_BULLETS; i++){
        if(!bullet[i].f.alive){
            init_bullet(i);
            return;
        }
    }
}

void *player_comands(void *arg){
    int i;
    if (key[ESCAPE]){
        game_state = MENU;
        al_stop_sample(&audio.id);
        reinit();
        for (i = 0; i < MAX_BULLETS; i++)
            bullet[i].f.alive = false;
        key[ESCAPE] = false;
    }
    if (key[P]){
        game_state = PAUSE;
        key[P] = false;
    }
    move_player(key);
    if (key[SPACE]){
        al_play_sample(audio.shot, 1.0, 0.0, 1, ALLEGRO_PLAYMODE_ONCE , 0);
        sem_wait(&sem_bullet);
        shot_bullet();
        sem_post(&sem_bullet);
        key[SPACE] = false;
    }
    if (!player.alive)
        game_state = GAME_OVER;
}

void play_function(void){
    int i;
    pthread_attr_t attr;
    pthread_t e[n_enemies], b[MAX_BULLETS], p;

    pthread_attr_init(&attr);
    
    pthread_create(&p, &attr, player_comands, NULL);

    for (i = 0; i < n_enemies; i++){
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&e[i], &attr, move_enemy, (void *)arg);
    }
    for (i = 0; i < MAX_BULLETS; i++){
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&b[i], &attr, move_bullet, (void *)arg);
    }

    pthread_join(p, NULL);

    for (i = 0; i < n_enemies; i++)
        pthread_join(e[i], NULL);
    
    for(i = 0; i < MAX_BULLETS; i++)
        pthread_join(b[i], NULL);
    
    pthread_attr_destroy(&attr);

    draw_play();

    if (dead_enemies == n_enemies){
        for (i = 0; i < MAX_BULLETS; i++){
            if (bullet[i].explosion){
                return;
            }
        }
        al_play_sample(audio.oh_yeah,0.5,0.0, 1,
            ALLEGRO_PLAYMODE_ONCE , 0);
        game_state = LOAD;
        update_level();
    }

}

void game_over_function(void){
    int h_score = read_score();

    draw_game_over(h_score);

    if (key[ESCAPE]){
        game_state = MENU;
        key[ESCAPE] = false;
        if (h_score < score)
            save_score();
        reinit();
    }
    
}

void pause_funtion(void){
    draw_pause();
    
    if (key[ESCAPE]){
        al_stop_sample(&audio.id);
        game_state = MENU;
        key[ESCAPE] = false;
        reinit();
    }

    if (key[P]){
        game_state = PLAY;
        key[P] = false;
    }
}

void show_controls_function(void){
    draw_controls();
    if (key[ESCAPE]){
        game_state = MENU;
        key[ESCAPE] = false;
    }
}

void high_score_function(void){
    int h_score = read_score();

    draw_high_score(h_score);
    if (key[ESCAPE]){
        game_state = MENU;
        key[ESCAPE] = false;
    }

}

void game_loop(void){
    bool finish = false;
    game_state = MENU;
    menu = 1;
    start_menu_song = false;
    
    while(!finish){
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_KEY_DOWN){
            update_keys(event, key, true);
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP){
            update_keys(event, key, false);
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            game_state = QUIT;
        else if (event.type == ALLEGRO_EVENT_TIMER)
        {
            switch (game_state){
            case MENU:
                menu_function();
                draw_screen_menu(menu);
                break;
            case LOAD:
                load_function();
                break;
            case PLAY:
                play_function();
                break;
            case PAUSE:
                pause_funtion();
                break;
            case CONTROLS:
                show_controls_function();
                break;
            case HIGH_SCORE:
                high_score_function();
                break;
            case GAME_OVER:
                game_over_function();
                break;
            case QUIT:
                finish = true;
                break;
            }
        }
    }
}