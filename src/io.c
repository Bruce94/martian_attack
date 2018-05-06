#include"io.h"

void update_keys(ALLEGRO_EVENT event, bool key[], bool setting){
    if ((event.keyboard.keycode == ALLEGRO_KEY_UP ||
            event.keyboard.keycode == ALLEGRO_KEY_DOWN ||
            event.keyboard.keycode == ALLEGRO_KEY_RIGHT ||
            event.keyboard.keycode == ALLEGRO_KEY_LEFT )&&
            (event.type == ALLEGRO_EVENT_KEY_DOWN)){
        key[UP] = false;
        key[DOWN] = false;
        key[RIGHT] = false;
        key[LEFT] = false;
    }
    switch (event.keyboard.keycode){
    case ALLEGRO_KEY_UP:
        key[UP] = setting;
        break;
    case ALLEGRO_KEY_DOWN:
        key[DOWN] = setting;
        break;
    case ALLEGRO_KEY_RIGHT:
        key[RIGHT] = setting;
        break;
    case ALLEGRO_KEY_LEFT:
        key[LEFT] = setting;
        break;
    case ALLEGRO_KEY_ENTER:
        key[ENTER] = setting;
        break;
    case ALLEGRO_KEY_SPACE:
        key[SPACE] = setting;
        break;    
    case ALLEGRO_KEY_D:
        key[D] = setting;
        break;
    case ALLEGRO_KEY_ESCAPE:
        key[ESCAPE] = setting;
        break;
    case ALLEGRO_KEY_P:
        key[P] = setting;
        break;
    case ALLEGRO_KEY_S:
        key[S] = setting;
        break;
    }
}

void save_score(void){
    FILE *fw = fopen("sav.txt", "w");
    if (fw == NULL){
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(fw, "%d", score);
    fclose(fw);
}

int read_score(void){
    FILE* fr = fopen ("sav.txt", "r");
    int i = 0;
    if (fr == NULL){
        return 0;
    }
    fscanf (fr, "%d", &i);    
    while (!feof (fr)) 
        fscanf (fr, "%d", &i);
    fclose (fr);
    return i;
}