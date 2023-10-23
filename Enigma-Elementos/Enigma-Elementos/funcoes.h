Allegro init();
void movimentacao(Personagem* character);
void atacar(int mx, int my);
void movi();

void dialogBox(Allegro* allegro, char string[], Personagem* character);
GAME_STATUS menu(Allegro* allegro);
GAME_STATUS prologue(Allegro* allegro);
GAME_STATUS lobby(Allegro* allegro);

void destroy(Allegro* allegro);
