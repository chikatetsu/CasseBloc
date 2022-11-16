#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bombs.h"
#include "time.h"

void findPlayerOnTheMap(char** map, int rows, int columns, int player_id, Player * players){

    int player_car = 'X';

    switch(player_id){
        case 0 :
            player_car = '1';
            break;
        case 1 :
            player_car = '2';
            break;
        case 2 :
            player_car = '3';
            break;
        case 3 :
            player_car = '4';
            break;
    }

    if(player_car != 'X'){
        for(int i = 0; i<rows; i++){
            for(int y = 0; y<columns; y++){
                if(map[i][y] == player_car){
                    players[player_id].v_pos = i;
                    players[player_id].h_pos = y;
                    //printf("\n** DEBUG ** -> Le joueur *%d* est en [%d][%d] !\n",player_id+1,i,y);
                }
            }
        }
    }
    else printf("\n** DEBUG ** -> Il y a une erreur pour trouver le joueur, player_id = %d\n",player_id);
}

int checkIfWin(Player * players, int player_size){

   int count = 0;

   for(int i = 0; i<player_size; i++) if(players[i].dead == 0) count++;

   //printf("\n** DEBUG ** -> Il y a %d joueurs en vie\n",count);

   if(count == 1){
       for(int i = 0; i<player_size; i++) if(players[i].dead == 0) return i+1;
   }
   if(count == 0) return 0;

   return -1;
}

void game(int player_size){
    int rows = 20;
    int columns = 20;
    char ** map = malloc(sizeof(char*)*rows);

    for(int i = 0; i<rows; i++){
        for(int y = 0; y<columns; y++) map[i] = malloc(sizeof(char)*columns);
    }

    for(int i = 0; i<rows; i++){
        for(int y = 0; y<columns; y++){
            map[i][y] = ' ';
            if(i == 0 || i == rows-1 || y == 0 || y == columns-1) map[i][y] = 'x';
            if(i == 9 || i == 10 || y == 9 || y == 10) map[i][y] = 'm';
        }
    }
    map[2][3] = '1';
    map[17][3] = '2';
    map[2][16] = '3';

    displayMap(map,rows,columns);

    ///Players Inits :

    Player player_1 = {
            .hp = 3,
            .max_hp = 3,
            .max_bombs = 2,
            .range = 2,
            .current_bombs = 2,
            .invincibility = 0, //isn't invincible yet
            .bomb_special_power_up = -1, //don't have any special power up
            .heart=0, //didn't get a heart this game
            .bombs_car="ABC",
            .dead = 0,
            .v_pos = 0,
            .h_pos = 0
    };

    Player player_2 = {
            .hp = 3,
            .max_hp = 3,
            .max_bombs = 2,
            .range = 2,
            .current_bombs = 2,
            .invincibility = 0, //isn't invincible yet
            .bomb_special_power_up = -1, //don't have any special power up
            .heart=0, //didn't get a heart this game
            .bombs_car="DEF",
            .dead = 0,
            .v_pos = 0,
            .h_pos = 0
    };

    Player player_3 = {
            .hp = 3,
            .max_hp = 3,
            .max_bombs = 2,
            .range = 2,
            .current_bombs = 2,
            .invincibility = 0, //isn't invincible yet
            .bomb_special_power_up = -1, //don't have any special power up
            .heart=0, //didn't get a heart this game
            .bombs_car="GHI",
            .dead = 0,
            .v_pos = 0,
            .h_pos = 0
    };

    Player player_4 = {
            .hp = 3,
            .max_hp = 3,
            .max_bombs = 2,
            .range = 2,
            .current_bombs = 2,
            .invincibility = 0, //isn't invincible yet
            .bomb_special_power_up = -1, //don't have any special power up
            .heart=0, //didn't get a heart this game
            .bombs_car="JKL",
            .dead = 1,
            .v_pos = 0,
            .h_pos = 0
    };

    Player players[4] = {player_1, player_2, player_3, player_4};

    for(int i = 0; i<player_size; i++) findPlayerOnTheMap(map, rows, columns, i, players);

    ///START OF TURNS

    int is_playing = 1;
    int turns = 1;
    int who_is_playing = 1;

    printf("\n - - TOUR(S) %d -- \n",turns);

    while(is_playing == 1){

        for(int i = 0; i<player_size; i++) if(players[i].hp <= 0 && players[i].dead == 0) playersDeath(map,players,player_size);
        int win = checkIfWin(players,player_size);
        if(win != 0 && win != -1){
            printf("\n\nLe joueur *%d* a gagne !!!!\n\n",win);
            break;
        }
        else if(win == 0){
            printf("\n\nEGALITE\n\n");
            break;
        }

        if(players[who_is_playing-1].dead) who_is_playing++;

        printf("\nACTIONS : ");
        printf("\nC'est au joueur %d de jouer !\n",who_is_playing);
        printf("- Entre '1' si tu veux aller a droite\n");
        printf("- Entre '2' si tu veux aller a gauche\n");
        printf("- Entre '3' si tu veux aller a haut\n");
        printf("- Entre '4' si tu veux aller a bas\n");
        printf("- Entre '0' si tu veux quitter la partie.\n");
        printf("\nInput : ");
        int value;
        int input = scanf("%d",&value);
        fflush(stdin);
        system("cls");

        displayMap(map,rows,columns);
        printf("\n - - TOUR(S) %d -- \n",turns);
        printf("\nINFOS : \n");
        if(input){
            if(value == 0) is_playing = 0;
            else if(value == -1) takeDamage('1',players);
            else printf("\nvalue = %d\n",value);
        }
        else printf("\n** DEBUG ** -> Il y a un problème avec la saisie utilisateur !\n");

        who_is_playing++;
        if(who_is_playing > player_size) who_is_playing = 1;
        turns++;
    }

}

int main() {

    //printf("Hello, World!\n"); //affiche

    srand(time(NULL));

    /*

    ///Players Inits :

    Player player_1 = {
            .hp = 3,
            .max_hp = 3,
            .max_bombs = 2,
            .range = 2,
            .current_bombs = 2,
            .invincibility = 0, //isn't invincible yet
            .bomb_special_power_up = -1, //don't have any special power up
            .heart=0, //didn't get a heart this game
            .bombs_car="ABC",
            .dead = 0,
            .v_pos = 0,
            .h_pos = 0
    };

    Player player_2 = {
            .hp = 3,
            .max_hp = 3,
            .max_bombs = 2,
            .range = 2,
            .current_bombs = 2,
            .invincibility = 0, //isn't invincible yet
            .bomb_special_power_up = -1, //don't have any special power up
            .heart=0, //didn't get a heart this game
            .bombs_car="DEF",
            .dead = 0,
            .v_pos = 3,
            .h_pos = 7
    };

    Player player_3 = {
            .hp = 3,
            .max_hp = 3,
            .max_bombs = 2,
            .range = 2,
            .current_bombs = 2,
            .invincibility = 0, //isn't invincible yet
            .bomb_special_power_up = -1, //don't have any special power up
            .heart=0, //didn't get a heart this game
            .bombs_car="GHI",
            .dead = 0,
            .v_pos = 5,
            .h_pos = 5
    };

    Player player_4 = {
            .hp = 3,
            .max_hp = 3,
            .max_bombs = 2,
            .range = 2,
            .current_bombs = 2,
            .invincibility = 0, //isn't invincible yet
            .bomb_special_power_up = -1, //don't have any special power up
            .heart=0, //didn't get a heart this game
            .bombs_car="JKL",
            .dead = 0,
            .v_pos = 2,
            .h_pos = 2
    };

    Player players[4] = {player_1, player_2, player_3, player_4};

    //test(10,15, players); //Function to test that bombs are working
    */

    game(3);

    return 0;
}
