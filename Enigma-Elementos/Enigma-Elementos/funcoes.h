Allegro init();
void movimentacao(Personagem* character);
void atacar(int mx, int my);
void enemyMove(Personagem* enemy);
void enemyExplosion(Personagem* enemy);
bool characterCollision(Personagem* char1, Personagem* char2);
bool mapCollision(Personagem* char1, MapSquare* square);
bool enemyHit(Tiro* shot, Personagem* char1);

void interface(ALLEGRO_BITMAP* heart, ALLEGRO_BITMAP* power, ALLEGRO_BITMAP* element, ALLEGRO_BITMAP* mouseLeft, ALLEGRO_BITMAP* mouseRight);
void dialogBox(Allegro* allegro, char string[], Personagem* character);
GAME_STATUS menu(Allegro* allegro);
GAME_STATUS prologue(Allegro* allegro);
GAME_STATUS lobby(Allegro* allegro);

void destroy(Allegro* allegro);
