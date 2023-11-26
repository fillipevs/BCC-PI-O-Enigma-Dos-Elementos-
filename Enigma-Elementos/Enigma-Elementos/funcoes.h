Allegro init();
void movimentacao(Personagem* character);
void atacar(int mx, int my, Interface* interface);
void takeElement(Interface* interface, Crystal* crystal);
void enemyMove(Personagem* enemy);
void enemyExplosion(Personagem* enemy);
bool characterCollision(Personagem* char1, Personagem* char2);
bool mapCollision(Personagem* char1, MapSquare* square);
bool enemyHit(Tiro* shot, Personagem* char1);
bool barreiraHit(Tiro* shot, MapSquare* square);

void showInterface(Interface* interface);
void dialogBox(Allegro* allegro, char string[], Personagem* character);
void menu(Allegro* allegro, GameStatus* gameStatus);
void prologue(Allegro* allegro, GameStatus* gameStatus);
void lobby(Allegro* allegro, GameStatus* gameStatus, Interface* interface, Barreira* barreira);
void water(Allegro* allegro, GameStatus* gameStatus, Interface* interface);
void fire(Allegro* allegro, GameStatus* gameStatus, Interface* interface);
void grass(Allegro* allegro, GameStatus* gameStatus, Interface* interface);

void destroy(Allegro* allegro);
