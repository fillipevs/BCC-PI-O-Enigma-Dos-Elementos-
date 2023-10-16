#include "funcoes.h"

GAME_STATUS lobby(Allegro* allegro) {
  GAME_STATUS gameStatus = LOBBY;
  bool draw = false;
  bool done = false;

  heroi.sprite = al_load_bitmap("./assets/heroi/andando.png");
  bobOmb.sprite = al_load_bitmap("./assets/inimigos/bob-omb-0.png");

  do {
    while(!al_is_event_queue_empty(allegro->eventQueue)) {
      ALLEGRO_EVENT event; 
      al_wait_for_event(allegro->eventQueue, &event);

      switch(event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE: 
          done = true;
          gameStatus = EXIT;
          break;

        case ALLEGRO_EVENT_TIMER:
          draw = true;
          al_get_mouse_state(&allegro->mouse);
          movi(); // movimentacao do bob-omb provisorio
          if( heroi.indoCima || heroi.indoDireita || heroi.indoBaixo || heroi.indoEsquerda ) {
            movimentacao(); // movimentação do player por enquanto
          }
          if( heroi.estaAtacando ) {
            atacar(allegro->mouse.x, allegro->mouse.y);
          }
          break;

        case ALLEGRO_EVENT_KEY_DOWN:
          if ( event.keyboard.keycode == ALLEGRO_KEY_RIGHT || event.keyboard.keycode == ALLEGRO_KEY_D ) {
            heroi.indoDireita = true;
          }
          else if ( event.keyboard.keycode == ALLEGRO_KEY_LEFT || event.keyboard.keycode == ALLEGRO_KEY_A ) {
            heroi.indoEsquerda = true;
          }
          else if ( event.keyboard.keycode == ALLEGRO_KEY_DOWN || event.keyboard.keycode == ALLEGRO_KEY_S ) {
            heroi.indoBaixo = true;
          }
          else if ( event.keyboard.keycode == ALLEGRO_KEY_UP || event.keyboard.keycode == ALLEGRO_KEY_W ) {
            heroi.indoCima = true;
          }
          break;

        case ALLEGRO_EVENT_KEY_UP:
          if ( event.keyboard.keycode == ALLEGRO_KEY_RIGHT || event.keyboard.keycode == ALLEGRO_KEY_D ) {
            heroi.indoDireita = false;
          }
          if ( event.keyboard.keycode == ALLEGRO_KEY_LEFT || event.keyboard.keycode == ALLEGRO_KEY_A ) {
            heroi.indoEsquerda = false;
          }
          if ( event.keyboard.keycode == ALLEGRO_KEY_DOWN || event.keyboard.keycode == ALLEGRO_KEY_S ) {
            heroi.indoBaixo = false;
          }
          if ( event.keyboard.keycode == ALLEGRO_KEY_UP || event.keyboard.keycode == ALLEGRO_KEY_W ) {
            heroi.indoCima = false;
          }
          break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
          if( event.mouse.button == 1 ) {
            heroi.estaAtacando = true;
          }
          break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
          if( event.mouse.button == 1 ) {
            heroi.estaAtacando = false;
          }
          break;
        
        default: 
          break;
      }
    }

    if( draw ) {
    draw = false;
    al_clear_to_color(al_map_rgb(0 ,0 ,0 ));

    al_draw_bitmap_region(heroi.sprite, heroi.largura * (int)heroi.frame, heroi.frameAtualY, heroi.largura, heroi.altura, heroi.posX, heroi.posY, 0); 

    al_draw_bitmap_region(bobOmb.sprite, bobOmb.largura * (int)bobOmb.frame, bobOmb.frameAtualY, bobOmb.largura, bobOmb.altura, bobOmb.posX, bobOmb.posY, 0); 

    for(int i = 0; i < 5; i++) {
      if( heroi.tiros[i].ativo && (heroi.tiros[i].posX > JANELA_LARGURA || heroi.tiros[i].posX < 0 || heroi.tiros[i].posY > JANELA_ALTURA || heroi.tiros[i].posY < 0) ) {
        heroi.tiros[i].ativo = false;
        al_destroy_bitmap(heroi.tiros[i].image);
      }

      if( heroi.tiros[i].ativo ) {
        heroi.tiros[i].posX += 6 * cos(heroi.tiros[i].angulo);
        heroi.tiros[i].posY += 6 * sin(heroi.tiros[i].angulo);
        al_draw_bitmap(heroi.tiros[i].image, heroi.tiros[i].posX, heroi.tiros[i].posY, 0);
      }
    }

    al_flip_display();
    }
    
  } while(!done);

  al_destroy_bitmap(heroi.sprite);  
  al_destroy_bitmap(bobOmb.sprite);
  for(int i = 0; i < 5; i++) 
    al_destroy_bitmap(bobOmb.tiros[i].image);

  return gameStatus;
} 