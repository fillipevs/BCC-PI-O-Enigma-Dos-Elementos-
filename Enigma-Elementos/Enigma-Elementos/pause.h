#include "funcoes.h"

void pauseGame(Allegro* allegro, GameStatus* gameStatus) {
  bool draw = true;
  bool done = false;
  bool displayControls = false;

  heroi.indoBaixo = false;
  heroi.indoCima = false;
  heroi.indoDireita = false;
  heroi.indoEsquerda = false;
  heroi.estaAtacando.fireball = false;
  heroi.estaAtacando.element = false;

  MapSquare continuar = {358, 640, 298, 350};
  MapSquare controles = {358, 640, 363, 413};
  MapSquare menu = {358, 640, 425, 475};
  MapSquare voltar = {420, 585, 460, 490}; 

  ALLEGRO_BITMAP* pauseImg = al_load_bitmap("./assets/pause.png");
  ALLEGRO_BITMAP* controlesImg = al_load_bitmap("./assets/controles.png");

  do {
    while(!al_is_event_queue_empty(allegro->eventQueue)) {
      ALLEGRO_EVENT event; 
      al_wait_for_event(allegro->eventQueue, &event);

      switch(event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE: 
          done = true;
          break;
        case ALLEGRO_EVENT_TIMER:
          al_get_mouse_state(&allegro->mouse);
          break;
        case ALLEGRO_EVENT_KEY_UP:
          if( event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            done = true;
          break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
          if( event.mouse.button == 1 ) {
            if( !displayControls && allegro->mouse.x >= continuar.x0 && allegro->mouse.x <= continuar.x1 && allegro->mouse.y >= continuar.y0 && allegro->mouse.y <= continuar.y1 ) {
              done = true;
            } else if( !displayControls && allegro->mouse.x >= controles.x0 && allegro->mouse.x <= controles.x1 && allegro->mouse.y >= controles.y0 && allegro->mouse.y <= controles.y1 ) {
              displayControls = true;
              draw = true;
            } else if( !displayControls && allegro->mouse.x >= menu.x0 && allegro->mouse.x <= menu.x1 && allegro->mouse.y >= menu.y0 && allegro->mouse.y <= menu.y1 ) {
              done = true;
              gameStatus->going = MENU;
            } else if( displayControls && allegro->mouse.x >= voltar.x0 && allegro->mouse.x <= voltar.x1 && allegro->mouse.y >= voltar.y0 && allegro->mouse.y <= voltar.y1 ) {
              displayControls = false;
              draw = true;
            }
          }
          break;
        default: 
          break;
      }
    }

    if( draw ) {
      draw = false;

      if( !displayControls ) {
        al_draw_bitmap(pauseImg, 250, 200, 0);
        al_draw_text(allegro->font[0], al_map_rgb(0,0,0), 400, 305, 0, "CONTINUAR");
        al_draw_text(allegro->font[0], al_map_rgb(0,0,0), 400, 370, 0, "CONTROLES");
        al_draw_text(allegro->font[0], al_map_rgb(0,0,0), 445, 435, 0, "MENU");
      } else {
        al_draw_bitmap(controlesImg, 250, 200, 0);
        al_draw_text(allegro->font[1], al_map_rgb(0,0,0), 445, 460, 0, "VOLTAR");
      }

      al_flip_display();
    }
    
  } while(!done);

  al_destroy_bitmap(pauseImg);
  al_destroy_bitmap(controlesImg);
}
