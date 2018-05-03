#include"io.h"

void update_keys(ALLEGRO_EVENT event, bool key[], bool setting){
    switch(event.keyboard.keycode){
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
    FILE *f = fopen("sav.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f, "%d", score);
    fclose(f);
}

int read_score(void){
    FILE* file = fopen ("sav.txt", "r");
    int i = 0;

    fscanf (file, "%d", &i);    
    while (!feof (file))
    {  
        fscanf (file, "%d", &i);      
    }
    fclose (file);
    return i;
}