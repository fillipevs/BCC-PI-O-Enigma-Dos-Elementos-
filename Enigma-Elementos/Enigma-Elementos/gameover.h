#include "funcoes.h"

void gameover(Allegro* allegro, GameStatus* gameStatus, Interface* interface) {
  bool draw = false;
  bool done = false;
  float textColorTime = 100;
  int textColorTimeDirection = 1;

  heroi.alive = true;
  heroi.lifes = 5;
  heroi.indoBaixo = false;
  heroi.indoCima = false;
  heroi.indoDireita = false;
  heroi.indoEsquerda = false;
  gameStatus->coming = GAMEOVER;
  gameStatus->going = LOBBY;
  interface->attack2SlotType = EMPTY;
  al_destroy_bitmap(interface->attack2Img);
  interface->attack2Img = al_load_bitmap("./assets/slotEmpty.png");

  ALLEGRO_BITMAP* gameoverImg = al_load_bitmap("./assets/gameover.png");

  do {
    while(!al_is_event_queue_empty(allegro->eventQueue)) {
      ALLEGRO_EVENT event; 
      al_wait_for_event(allegro->eventQueue, &event);

      switch (event.type)
      {
      case ALLEGRO_EVENT_DISPLAY_CLOSE: 
        done = true;
        gameStatus->going = EXIT;
        break;
      case ALLEGRO_EVENT_TIMER:
          draw = true;
          break;
      case ALLEGRO_EVENT_KEY_UP:
        if ( event.keyboard.keycode == ALLEGRO_KEY_SPACE ) {
          done = true;
        }
        break;
      case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
        if( event.mouse.button == 1 ) 
          done = true;
        break;
      
      default:
        break;
      }
      
    }

    if( draw ) {
      draw = false;
      al_clear_to_color(al_map_rgb(0,0,0));
      al_draw_bitmap(gameoverImg, 0, 0, 0);

      textColorTime += textColorTimeDirection * 2;
      if( textColorTime >= 200 || textColorTime <= 0 ) {
        textColorTimeDirection = textColorTimeDirection * -1;
      }
      al_draw_text(allegro->font[1], al_premul_rgba(255,255,255, textColorTime), 390, 650, 0, "clique para continuar");

      al_flip_display();
    }
  } while(!done);

  al_destroy_bitmap(gameoverImg);  
}
