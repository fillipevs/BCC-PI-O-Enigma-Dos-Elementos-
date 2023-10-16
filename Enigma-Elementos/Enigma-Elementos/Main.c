#include "main.h"

int main () {

  Allegro allegro = init();

  GAME_STATUS gameStatus = MENU;

  while(!allegro.close) {
    switch (gameStatus)
    {
    case MENU:
      gameStatus = menu(&allegro);
      break;
    case LOBBY: 
      gameStatus = lobby(&allegro);
      break;
    case EXIT: 
      allegro.close = true;
      break;
    
    default:
      break;
    }
  }

  destroy(&allegro);
  return 0;
}
