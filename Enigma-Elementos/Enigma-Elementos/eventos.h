#include "funcoes.h"

void eventos(Allegro* allegro, bool *desenhar) {
  while(!al_is_event_queue_empty(allegro->eventQueue)) {
      ALLEGRO_EVENT evento; 
      al_wait_for_event(allegro->eventQueue, &evento);

      // verifica quais eventos estão ocorrendo
      switch(evento.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE: 
          allegro->close = true;
          break;

        case ALLEGRO_EVENT_TIMER:
          *desenhar = true;
          movi();
          if( heroi.indoCima || heroi.indoDireita || heroi.indoBaixo || heroi.indoEsquerda ) {
            movimentacao(); // movimentação do player por enquanto
          }
          if( heroi.estaAtacando ) {
            al_get_mouse_state(&allegro->mouse);
            atacar(allegro->mouse.x, allegro->mouse.y);
          }
          break;

        case ALLEGRO_EVENT_KEY_DOWN:
          if ( evento.keyboard.keycode == ALLEGRO_KEY_RIGHT || evento.keyboard.keycode == ALLEGRO_KEY_D ) {
            heroi.indoDireita = true;
          }
          else if ( evento.keyboard.keycode == ALLEGRO_KEY_LEFT || evento.keyboard.keycode == ALLEGRO_KEY_A ) {
            heroi.indoEsquerda = true;
          }
          else if ( evento.keyboard.keycode == ALLEGRO_KEY_DOWN || evento.keyboard.keycode == ALLEGRO_KEY_S ) {
            heroi.indoBaixo = true;
          }
          else if ( evento.keyboard.keycode == ALLEGRO_KEY_UP || evento.keyboard.keycode == ALLEGRO_KEY_W ) {
            heroi.indoCima = true;
          }
          break;

        case ALLEGRO_EVENT_KEY_UP:
          if ( evento.keyboard.keycode == ALLEGRO_KEY_RIGHT || evento.keyboard.keycode == ALLEGRO_KEY_D ) {
            heroi.indoDireita = false;
          }
          if ( evento.keyboard.keycode == ALLEGRO_KEY_LEFT || evento.keyboard.keycode == ALLEGRO_KEY_A ) {
            heroi.indoEsquerda = false;
          }
          if ( evento.keyboard.keycode == ALLEGRO_KEY_DOWN || evento.keyboard.keycode == ALLEGRO_KEY_S ) {
            heroi.indoBaixo = false;
          }
          if ( evento.keyboard.keycode == ALLEGRO_KEY_UP || evento.keyboard.keycode == ALLEGRO_KEY_W ) {
            heroi.indoCima = false;
          }
          break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
          if( evento.mouse.button == 1 ) {
            heroi.estaAtacando = true;
          }
          break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
          if( evento.mouse.button == 1 ) {
            heroi.estaAtacando = false;
          }
          break;
      }
    }
}

void movimentacao() {  

  if( heroi.indoCima ) {
    heroi.posY -= heroi.vel;
    heroi.frameAtualY = heroi.altura * 3; 
  } 
  
  if( heroi.indoDireita ) {
    heroi.posX += heroi.vel;
    heroi.frameAtualY = heroi.altura * 2; 
  }
  
  if( heroi.indoBaixo ) {
    heroi.posY += heroi.vel;
    heroi.frameAtualY = heroi.altura * 0; 
  }
  
  if( heroi.indoEsquerda ) {
    heroi.posX -= heroi.vel;
    heroi.frameAtualY = heroi.altura * 1; 
  }

  heroi.frame += 0.15;
  if( heroi.frame > heroi.frameMax ) 
    heroi.frame -= heroi.frameMax;
}


void atacar(int mx, int my) {
  if( heroi.tempoAtacar <= 0 ) {
    double angulo = atan2((double)my - heroi.posY, (double)mx - heroi.posX);

    for(int i = 0; i < 5; i++) {
      if( !heroi.tiros[i].ativo ) {
        heroi.tiros[i].altura = 32;
        heroi.tiros[i].largura = 32;
        heroi.tiros[i].angulo = angulo;
        heroi.tiros[i].ativo = true;
        heroi.tiros[i].posX = heroi.posX;
        heroi.tiros[i].posY = heroi.posY;
        heroi.tiros[i].image = al_load_bitmap("./assets/bolafogo.png");
        break;
      } 
    }
    
    heroi.tempoAtacar = 6;
  } else {
    heroi.tempoAtacar -= 0.1;
  }

}
