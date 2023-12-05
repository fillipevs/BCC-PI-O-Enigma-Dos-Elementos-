#include "main.h"

int main () {

  Allegro allegro = init();

  GameStatus gameStatus = {MENU, MENU };

  Barreira barreira;
  barreira.chumbo = true;
  barreira.mercurio = true;
  barreira.prata = true;
  barreira.verificar = true;

  Interface interface;
  interface.heart = al_load_bitmap("./assets/heart.png");
  interface.mouseBtnLeftImg = al_load_bitmap("./assets/mouse-left.png");
  interface.mouseBtnRightImg = al_load_bitmap("./assets/mouse-right.png");
  interface.attack1SlotType = FIREBALL;
  interface.attack1Img = al_load_bitmap("./assets/power.png");
  interface.attack2SlotType = EMPTY;
  interface.attack2Img = al_load_bitmap("./assets/slotEmpty.png");
  interface.interactBtnImg = al_load_bitmap("./assets/pressE.png");

  while(!allegro.close) {
    switch (gameStatus.going)
    {
    case MENU:
      menu(&allegro, &gameStatus);
      break;
    case PROLOGUE: 
      prologue(&allegro, &gameStatus);
      break;
    case LOBBY: 
      lobby(&allegro, &gameStatus, &interface, &barreira);
      break;
    case WATER: 
      water(&allegro, &gameStatus, &interface);
      break;
    case FIRE: 
      fire(&allegro, &gameStatus, &interface);
      break;
    case GRASS: 
      grass(&allegro, &gameStatus, &interface);
      break;
    case EXIT: 
      allegro.close = true;
      break;
    
    default:
      break;
    }
  }

  al_destroy_bitmap(interface.heart);
  al_destroy_bitmap(interface.mouseBtnLeftImg);
  al_destroy_bitmap(interface.mouseBtnRightImg);
  al_destroy_bitmap(interface.attack1Img);
  al_destroy_bitmap(interface.attack2Img);
  al_destroy_bitmap(interface.interactBtnImg);
  destroy(&allegro);
  return 0;
}
