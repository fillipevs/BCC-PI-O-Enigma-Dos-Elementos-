Allegro init();
void movimentacao(Personagem* character);
void atacar(int mx, int my);
void movi();
bool characterCollision(Personagem* char1, Personagem* char2);
bool mapCollision(Personagem* char1, MapSquare* square);
bool enemyHit(Tiro* shot, Personagem* char1);

void dialogBox(Allegro* allegro, char string[], Personagem* character);
GAME_STATUS menu(Allegro* allegro);
GAME_STATUS prologue(Allegro* allegro);
GAME_STATUS lobby(Allegro* allegro);

void destroy(Allegro* allegro);
