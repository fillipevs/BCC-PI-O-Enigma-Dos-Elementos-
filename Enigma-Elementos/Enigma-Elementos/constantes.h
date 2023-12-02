#define JANELA_LARGURA 1020
#define JANELA_ALTURA 720

#define PI 3.14159265359

typedef enum {
  MENU,
  PROLOGUE,
  LOBBY,
  WATER,
  FIRE,
  GRASS,
  EXIT,
} GAME_STATUS_TYPE;

typedef enum {
  EMPTY,
  FIREBALL,
  ACIDO_CLORIDRICO,
  HIDROXIDO_AMONIO,
  VERIFICATION,
} SlotType;

typedef enum {
  START,
  TAKE_ELEMENT
} SpawnType;
