#include "movements.h"

void down(struct FIGURE_t *f){
    f->y += f->movespeed;
    f->dir = DIR_DOWN;
}

void up(struct FIGURE_t *f){
    f->y -= f->movespeed;
    f->dir = DIR_UP;
}

void right(struct FIGURE_t *f){
    f->x += f->movespeed;
    f->dir = DIR_RIGHT;
}

void left(struct FIGURE_t *f){
    f->x -= f->movespeed;
    f->dir = DIR_LEFT;
}

void player_border_collision(void){
    if(player.dir == DIR_RIGHT && player.x + PLAYER_H >= XWIN){
        player.x -= player.movespeed;
    }
    else if(player.dir == DIR_LEFT && player.x < 0){
        player.x += player.movespeed;
    }
    else if(player.dir == DIR_UP && player.y < 0){
        player.y += player.movespeed;
    }
    else if(player.dir == DIR_DOWN && player.y + PLAYER_H >= YWIN){
        player.y -= player.movespeed;
    }
}

void bullet_enemy_collision(int i){
    int j;
    int bx = bullet[i].f.x;
    int by = bullet[i].f.y;
    int bw = bullet[i].f.x + BULLET_W;
    int bh = bullet[i].f.x + BULLET_H;
    int ex, ey, ew, eh;
    
    for (j = 0; j < n_enemies; j++){
        if (enemy[j].alive){
            ex = enemy[j].x;
            ey = enemy[j].y;
            if (enemy[j].dir == DIR_DOWN || enemy[j].dir == DIR_UP){
                ew = enemy[j].x + ENEMY_W;
                eh = enemy[j].y + ENEMY_H;
            }
            else{
                ew = enemy[j].x + ENEMY_H;           
                eh = enemy[j].y + ENEMY_W;
            }
            //if (((bx >= ex && bx <= ew) || (bw >= ex && bw <= ew)) &&
            //    ((by >= ey && by <= eh) || (bh >= ey && bh <= eh))){
            if ((bx >= ex && bx <= ew) && (by >= ey && by <= eh)){
                bullet[i].f.alive = false;
                bullet[i].explosion = true;
                enemy[j].alive = false;
                score ++;
                dead_enemies ++;
                al_play_sample(audio.enemy_death,0.2,0.0, 1,
                    ALLEGRO_PLAYMODE_ONCE , 0);
                return;
            }
        }
    }
}

void enemy_player_collision(int i){
    int ex = enemy[i].x + 5;
    int ey = enemy[i].y + 5;
    int px = player.x + 5;
    int py = player.y + 5;
    int pw, ph, ew, eh;

    if (enemy[i].dir == DIR_DOWN || enemy[i].dir == DIR_UP){
        ew = enemy[i].x + ENEMY_W;
        eh = enemy[i].y + ENEMY_H;
    }
    else{
        ew = enemy[i].x + ENEMY_H;           
        eh = enemy[i].y + ENEMY_W;
    } 
    if (player.dir == DIR_DOWN || player.dir == DIR_UP){
        pw = player.x + PLAYER_W;
        ph = player.y + PLAYER_H;
    }
    else{
        pw = player.x + PLAYER_H;           
        ph = player.y + PLAYER_W;
    }
    if (((px >= ex && px <= ew) || (pw >= ex && pw <= ew))&&
        ((py >= ey && py <= eh) || (ph >= ey && ph <= eh))){
        al_stop_sample(&audio.id);
        al_play_sample(audio.player_death,0.4,0.0, 1,
            ALLEGRO_PLAYMODE_ONCE , 0);
        al_play_sample(audio.sample_lose,1.0,0.0, 1,
            ALLEGRO_PLAYMODE_ONCE , 0);               
        player.alive = false;
    }
}

void move_player(bool key[]){
    if (player.dir != DIR_STOP)
        player.last_dir = player.dir;
    if (key[DOWN])
        down(&player);
    else if (key[UP])
        up(&player);
    else if (key[RIGHT])
        right(&player);
    else if (key[LEFT])
        left(&player);
    else
        player.dir = DIR_STOP;
    player_border_collision();
}

void *move_bullet(void *arg){
    int i = *((int *) arg);
    sem_wait(&sem_bullet);
        if (bullet[i].f.alive){
            if (bullet[i].f.x < 0 || bullet[i].f.x > XWIN || 
                bullet[i].f.y < 0 || bullet[i].f.y > YWIN){
                bullet[i].f.alive = false;
            }
            else{
                if (bullet[i].f.dir == DIR_DOWN)
                    down(&bullet[i].f);
                if (bullet[i].f.dir == DIR_UP)
                    up(&bullet[i].f);
                if (bullet[i].f.dir == DIR_RIGHT)
                    right(&bullet[i].f);
                if (bullet[i].f.dir == DIR_LEFT)
                    left(&bullet[i].f);
                //printf("Bullet[%d]:x[%f],y[%f]\n",i,bullet[i].x,bullet[i].y);
            }
            sem_wait(&sem_enemies_move);
                bullet_enemy_collision(i);
            sem_post(&sem_enemies_move);
        }
    sem_post(&sem_bullet);
}

void *move_enemy(void *arg){
    int i = *((int *) arg);
    float dx, dy;
    bool ud_rl;
    sem_wait(&sem_enemies_move);
    if(enemy[i].alive){
        dx = player.x - enemy[i].x;
        dy = player.y - enemy[i].y;
        ud_rl = rand() & 1;
        enemy[i].last_dir = enemy[i].dir;

        if (dx >= 0 && dy >= 0){
            if (enemy[i].dir == DIR_RIGHT)
                right(&enemy[i]);
            else if (enemy[i].dir == DIR_DOWN)
                down(&enemy[i]);
            else if(ud_rl)
                right(&enemy[i]); 
            else
                down(&enemy[i]); 
        }
        else if (dx >= 0 && dy <= 0){
            if (enemy[i].dir == DIR_RIGHT)
                right(&enemy[i]);
            else if (enemy[i].dir == DIR_UP)
                up(&enemy[i]);
            else if (ud_rl)
                right(&enemy[i]);
            else
                up(&enemy[i]);
        }
        else if (dx <= 0 && dy >= 0){
            if (enemy[i].dir == DIR_LEFT)
                left(&enemy[i]);
            else if (enemy[i].dir == DIR_DOWN)
                down(&enemy[i]);
            else if (ud_rl)
                left(&enemy[i]);
            else
                down(&enemy[i]);
        }
        else if (dx <= 0 && dy <= 0){
            if (enemy[i].dir == DIR_LEFT)
                left(&enemy[i]);
            else if (enemy[i].dir == DIR_UP)
                up(&enemy[i]);
            else if (ud_rl)
                left(&enemy[i]);
            else
                up(&enemy[i]);
        }
        enemy_player_collision(i);
    }
    sem_post(&sem_enemies_move);
}