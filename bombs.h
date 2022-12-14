/*
    Autheurs : Charles CRETOIS
*/

typedef struct player{
    int hp;
    int max_hp;
    int current_bombs;
    int max_bombs;
    int range;
    int bomb_special_power_up; //-1=rien, 0=Passe bomb, 1=Bomb kick
    int invincibility; //tours restants d'invincibilité
    int heart; //-1=coeur déjà utilisé, 0=pas de coeur, 1=a un coeur
    char* bombs_car; //Bombs states
    int dead; //0=player not dead, 1= player dead
    int v_pos; // Player vertical position
    int h_pos; // Player horizontal position
}Player;

void displayMap(char**map, int rows, int columns);
void displayMapDEBUG(char**map, int rows, int columns);
void displayPlayersStats(Player * players,int players_size);
int findPlayerWithBomb(char bomb);
char ** clearExplosions(char**map,int rows, int columns);
char ** dropObjectSymbol(char** map, int v_pos, int h_pos);
void dropObject(Player * player,int player_number);
void takeDamage(char player_number,Player * players);
char** explosionAtThatPlace(char**map, int rows, int columns, int v_pos, int h_pos, Player* players,char bomb);
int checkRange(char bomb, Player * players);
char** bombExplosion(char**map, int rows, int columns, int v_pos, int h_pos, int range, Player* players);
char** checkBombsOfOnePlayer(char**map, int rows, int columns, Player* players, char* bomb_car);
char** checkAllBombs(char**map, int rows, int columns, Player* players);
char** dropBomb(char**map, int v_pos, int h_pos, Player* player, char* bomb_car);
char** playersDeath(char** map, Player * players, int players_size);
int checkIfOutOfTheMap(int rows, int columns,int v_pos,int h_pos);
char** bombKick(char** map,int rows, int columns,char direction,int bomb_v_pos,int bomb_h_pos);
void test(int rows, int columns, Player* players);
int checkBombKick(char **map, Player player, char direction);
int checkPlaceBomb(char **map, Player player, char direction);
