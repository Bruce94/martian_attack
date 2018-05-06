#include"gui.h"

void draw_text_font_h1(int x, int y, char *str){
    al_draw_text(font.h1, al_map_rgb(255,255,255), x, y,
        ALLEGRO_ALIGN_CENTER, str);
}

void draw_text_font_h2(int x, int y, char *str){
    al_draw_text(font.h2, al_map_rgb(255,255,255), x, y,
        ALLEGRO_ALIGN_CENTER, str);
}

void draw_screen_menu(int menu){
    al_clear_to_color(al_map_rgb(0,0,0));
    draw_text_font_h1(XWIN / 2, YWIN * 10 / 100, "Martian Attack");
    draw_text_font_h2(XWIN / 2, YWIN * 55 / 100, "Start Game");
    draw_text_font_h2(XWIN / 2, YWIN * 65 / 100, "Controls");
    draw_text_font_h2(XWIN / 2, YWIN * 75 / 100, "High Score");

    al_draw_text(font.h4, al_map_rgb(255,255,255), XWIN / 2, 
            YWIN * 95 / 100, ALLEGRO_ALIGN_CENTER, "Powered by Bruno Ghion");
    switch (menu)
    {
    case 1:
        al_draw_bitmap_region(bitmap.bullet, 12, 0, BULLET_H, BULLET_W,
                XWIN * 34 / 100, YWIN * 56 / 100, 0);
        al_draw_bitmap_region(bitmap.bullet, 28, 0, BULLET_H, BULLET_W,
                XWIN * 66 / 100, YWIN * 56 / 100, 0);
        break;
    case 2:
        al_draw_bitmap_region(bitmap.bullet, 12, 0, BULLET_H, BULLET_W,
                XWIN * 34 / 100, YWIN * 66 / 100, 0);
        al_draw_bitmap_region(bitmap.bullet, 28, 0, BULLET_H, BULLET_W,
                XWIN * 66 / 100, YWIN * 66 / 100, 0);
        break;
    case 3:
        al_draw_bitmap_region(bitmap.bullet, 12, 0, BULLET_H, BULLET_W,
                XWIN * 34 / 100, YWIN * 76 / 100, 0);
        al_draw_bitmap_region(bitmap.bullet, 28, 0, BULLET_H, BULLET_W,
                XWIN * 66 / 100, YWIN * 76 / 100, 0);
        break;
    }
    al_flip_display();
}

void draw_string_tmp(char *str){
    al_clear_to_color(al_map_rgb(0,0,0));
    draw_text_font_h1(XWIN / 2, YWIN * 50 / 100, str);
    al_flip_display();
    al_rest(2.0);
}

void draw_countdown(){
    draw_string_tmp("THREE");
    draw_string_tmp("TWO");
    draw_string_tmp("ONE");
}

void draw_figure_bitmap(struct FIGURE_t *f, int w, int h, int s,
                        struct ALLEGRO_BITMAP *img){
    if(f->dir != DIR_STOP){
        if(f->last_dir != f->dir)
            f->sourcex = 0;
        f->sourcex += w;
        if(f->sourcex >= w*3){
            f->sourcex = 0;
        }
        f->sourcey = f->dir % 2;
    }
    else{
        f->sourcex = 0;
        f->sourcey = f->last_dir % 2;
    }
    al_draw_bitmap_region(img, f->sourcex,
        s + f->sourcey * h, w, 
        h, f->x, f->y, 0);
}

void draw_enemy(int i){
    if(enemy[i].alive){
        if (enemy[i].dir == DIR_DOWN || enemy[i].dir == DIR_UP){
            draw_figure_bitmap(&enemy[i], 
                ENEMY_W, ENEMY_H, 0, bitmap.enemy);
        }
        else {
            draw_figure_bitmap(&enemy[i], 
                ENEMY_H, ENEMY_W, ENEMY_H * 2, bitmap.enemy);
        }
    }
}

void draw_player(void){
    if ((player.dir == DIR_STOP && 
        (player.last_dir == DIR_DOWN || player.last_dir == DIR_UP))||
        (player.dir == DIR_DOWN || player.dir == DIR_UP)){
        draw_figure_bitmap(&player, PLAYER_W, PLAYER_H, 0, bitmap.player);
    }
    else if ((player.dir == DIR_STOP && 
        (player.last_dir == DIR_LEFT || player.last_dir == DIR_RIGHT))||
        (player.dir == DIR_LEFT || player.dir == DIR_RIGHT)){
        draw_figure_bitmap(&player, PLAYER_H, PLAYER_W, PLAYER_H * 2, bitmap.player);
    }  
}

void draw_background(void){
    al_draw_bitmap(bitmap.background, 0, 0, 0);
}

//-----------------------------------------------------------------------------
// If the bullet has the variable "explosion" set to false and the variable
// "alive" set to true draws the bullet otherwise if "explosion" is true it
// draws the animation of the bullet explosion
//-----------------------------------------------------------------------------
void draw_bullet(int i){
    if (!bullet[i].explosion){ 
        if (bullet[i].f.alive){
            if (bullet[i].f.dir == DIR_UP || bullet[i].f.dir == DIR_DOWN)
                al_draw_bitmap_region(bitmap.bullet, bullet[i].f.sourcex,
                    bullet[i].f.sourcey, BULLET_W, 
                    BULLET_H, bullet[i].f.x, bullet[i].f.y, 0);
            if (bullet[i].f.dir == DIR_RIGHT || bullet[i].f.dir == DIR_LEFT)
                al_draw_bitmap_region(bitmap.bullet, bullet[i].f.sourcex,
                    bullet[i].f.sourcey, BULLET_H, 
                    BULLET_W, bullet[i].f.x, bullet[i].f.y, 0);
        }
    }
    else{
        switch (bullet[i].anim){
            case 0:
                al_draw_bitmap_region(bitmap.explosion, 0, 0, 8, 8,
                    bullet[i].f.x, bullet[i].f.y, 0);
                bullet[i].anim ++;
                break;
            case 1:
                al_draw_bitmap_region(bitmap.explosion, 8, 0, 12, 12,
                    bullet[i].f.x-2, bullet[i].f.y-2, 0);
                bullet[i].anim ++;
                break;
            case 2:
                al_draw_bitmap_region(bitmap.explosion, 20, 0, 16, 16,
                    bullet[i].f.x-4, bullet[i].f.y-4, 0);
                bullet[i].anim = 0;
                bullet[i].explosion = false;
                break;
        }
    }
}

void draw_score_level_life(void){
    char s[255];
    char l[255];
    char lf[255];

	snprintf(s, 255, "score: %d", score);
    snprintf(l, 255, "level: %d", level);
    al_draw_text(font.h5, al_map_rgb(0,0,0), XWIN * 3 / 100, 
            YWIN * 3 / 100, ALLEGRO_ALIGN_LEFT, s);
    al_draw_text(font.h5, al_map_rgb(0,0,0), XWIN * 80 / 100, 
            YWIN * 3 / 100, ALLEGRO_ALIGN_LEFT, l);
}

void draw_play(void){
    int i;

    draw_background();
    for(i = 0; i < MAX_BULLETS; i++)
        draw_bullet(i);

    for (i = 0; i < n_enemies; i++)
        draw_enemy(i);

    draw_player(); 

    draw_score_level_life();
    al_flip_display();
}

void draw_player_death(int death_anim){
    draw_background();
    switch (death_anim){
    case 0:
        al_draw_bitmap_region(bitmap.player_blood, 0, 0, 20, 31,
            player.x, player.y, 0);
        break;
    case 1:
        al_draw_bitmap_region(bitmap.player_blood, 20, 0, 34, 41,
            player.x, player.y, 0);
        break;
    case 2:
        al_draw_bitmap_region(bitmap.player_blood, 54, 0, 34, 41,
            player.x, player.y, 0);
        break;
    case 3:
        al_draw_bitmap_region(bitmap.player_blood, 88, 0, 44, 47,
            player.x, player.y, 0);
        break;
    case 4:
        al_draw_bitmap_region(bitmap.player_blood, 132, 0, 55, 45,
            player.x, player.y, 0);
        break;
    case 5:
        al_draw_bitmap_region(bitmap.player_blood, 187, 0, 49, 43,
            player.x, player.y, 0);
        break;
    }
    al_flip_display();
}

void draw_game_over(int h_score){
    char s[255];
    	    
    snprintf(s, 255, "score: %d", score);
    al_clear_to_color(al_map_rgb(0,0,0));
    draw_text_font_h1(XWIN / 2, YWIN * 50 / 100, "Game Over!");
    draw_text_font_h2(XWIN / 2, YWIN * 60 / 100, s);

    if (h_score < score)
        al_draw_text(font.h2, al_map_rgb(255,0,0), XWIN / 2, 
            YWIN * 65 / 100, ALLEGRO_ALIGN_CENTER, "New High Score!");
    al_draw_text(font.h3, al_map_rgb(255,255,255), XWIN / 2, 
            YWIN * 90 / 100, ALLEGRO_ALIGN_CENTER, 
            "Press ESC to return to the menu!");
    al_flip_display();
}

void draw_pause(void){  	   
    draw_text_font_h1(XWIN / 2, YWIN * 50 / 100, "Pause!");
    draw_text_font_h2(XWIN / 2, YWIN * 65 / 100, 
        "Press P to return at geme or ESC to return to the menu!");
    al_flip_display();
}



void draw_controls(void){
    al_clear_to_color(al_map_rgb(0,0,0));
    draw_text_font_h1(XWIN / 2, YWIN * 10 / 100, "CONTROLS");
    al_draw_bitmap(bitmap.up_arrow, XWIN * 20 / 100, YWIN * 30 / 100, 0);
    al_draw_bitmap(bitmap.down_arrow, XWIN * 20 / 100, YWIN * 40 / 100, 0);
    al_draw_bitmap(bitmap.right_arrow, XWIN * 20 / 100, YWIN * 50 / 100, 0);
    al_draw_bitmap(bitmap.left_arrow, XWIN * 20 / 100, YWIN * 60 / 100, 0);
    al_draw_text(font.h5, al_map_rgb(255,255,255), XWIN * 25 / 100, 
        YWIN * 73 / 100, ALLEGRO_ALIGN_CENTER, "space");
    al_draw_text(font.h5, al_map_rgb(255,255,255), XWIN * 25 / 100, 
        YWIN * 80 / 100, ALLEGRO_ALIGN_CENTER, "p");

    draw_text_font_h2(XWIN * 70 / 100, YWIN * 35 / 100, "UP");
    draw_text_font_h2(XWIN * 70 / 100, YWIN * 45 / 100, "DOWN");
    draw_text_font_h2(XWIN * 70 / 100, YWIN * 55 / 100, "RIGHT");
    draw_text_font_h2(XWIN * 70 / 100, YWIN * 65 / 100, "LEFT");
    draw_text_font_h2(XWIN * 70 / 100, YWIN * 73 / 100, "SHOOT");
    draw_text_font_h2(XWIN * 70 / 100, YWIN * 80 / 100, "PAUSE");
    al_flip_display();
}

void draw_high_score(int h_score){
    char s[255];
    	    
    snprintf(s, 255, "%d", h_score);

    al_clear_to_color(al_map_rgb(0, 0, 0));

    draw_text_font_h1(XWIN / 2, YWIN * 10 / 100, "HIGH SCORE");

    al_draw_text(font.h1, al_map_rgb(255, 0, 0), XWIN / 2, 
        YWIN / 2, ALLEGRO_ALIGN_CENTER, s);
    al_flip_display();
}