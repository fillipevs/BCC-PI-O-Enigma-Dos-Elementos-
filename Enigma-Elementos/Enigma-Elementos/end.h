#include "funcoes.h"

void meetHero(Personagem* character);

void end(Allegro* allegro, GameStatus* gameStatus) {
  bool draw = false;
  bool done = false;
  bool alreadyTalked = false;

  float kingHeroDistance = 0.0f;
  float princessHeroDistance = 0.0f;

  ALLEGRO_BITMAP* lobby = al_load_bitmap("./assets/mapa/lobby.bmp");
  heroi.sprite = al_load_bitmap("./assets/heroi/andando.png");
  king.sprite = al_load_bitmap("./assets/npc/king.png");
  princess.sprite = al_load_bitmap("./assets/npc/princess.png");
  heroi.face = al_load_bitmap("./assets/heroi/face.png");
  king.face = al_load_bitmap("./assets/npc/king-face.png");
  princess.face = al_load_bitmap("./assets/npc/princess-face.png");

  do {
    while(!al_is_event_queue_empty(allegro->eventQueue)) {
      ALLEGRO_EVENT event; 
      al_wait_for_event(allegro->eventQueue, &event);

      switch(event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE: 
          done = true;
          gameStatus->going = EXIT;
          break;

        case ALLEGRO_EVENT_TIMER:
          draw = true;
          if( heroi.indoCima || heroi.indoDireita || heroi.indoBaixo || heroi.indoEsquerda ) {
            movimentacao(&heroi); // movimentação do herói
          } else {
            heroi.frame = 1;
          }
          break;

        case ALLEGRO_EVENT_KEY_DOWN:
          break;

        case ALLEGRO_EVENT_KEY_UP:
          break;

        default: 
          break;
      }
    }

    if( draw ) {
      draw = false;
      al_clear_to_color(al_map_rgb(0 ,0 ,0 ));
      al_draw_bitmap(lobby, 0, 0, 0);
      al_draw_bitmap_region(heroi.sprite, heroi.largura * (int)heroi.frame, heroi.frameAtualY, heroi.largura, heroi.altura, heroi.posX, heroi.posY, 0); 
      al_draw_bitmap_region(king.sprite, king.largura * (int)king.frame, king.frameAtualY, king.largura, king.altura, king.posX, king.posY, 0); 
      al_draw_bitmap_region(princess.sprite, princess.largura * (int)princess.frame, princess.frameAtualY, princess.largura, princess.altura, princess.posX, princess.posY, 0); 

      kingHeroDistance = sqrt( pow( (heroi.posX+heroi.largura/2) - (king.posX+king.largura/2), 2 ) + pow( (heroi.posY+heroi.altura/2) - (king.posY+king.altura/2), 2 ) );
      princessHeroDistance = sqrt( pow( (heroi.posX+heroi.largura/2) - (princess.posX+princess.largura/2), 2 ) + pow( (heroi.posY+heroi.altura/2) - (princess.posY+princess.altura/2), 2 ) );

      if( !alreadyTalked ) {
        if( heroi.posY+heroi.altura > 110 && heroi.posY+heroi.altura < 200) {
          heroi.indoCima = true;
        } else {
          heroi.indoCima = false;
        }

        if( kingHeroDistance > 40 )
          meetHero(&king);
        if( princessHeroDistance > 40 )
          meetHero(&princess);

        if( heroi.posY > king.posY ) {
          heroi.frameAtualY = heroi.altura * 3;
        } else {
          heroi.frameAtualY = heroi.altura * 0;
        }
        if( kingHeroDistance <= 40 && princessHeroDistance <= 40 ) {
          dialogBox(allegro, "Alex, em nome de todo o reino, agradeço por ter libertado nossa amada Princesa das garras da barreira alquímica", &king);
          dialogBox(allegro, "Alex, minha gratidão é eterna. Você trouxe esperança e liberdade quando eu estava aprisionada. Não tenho palavras para expressar minha gratidão.", &princess);
          dialogBox(allegro, "Majestade, Princesa, minha missão foi concluída com alegria ao vê-la livre. Estou honrado em ter servido ao reino.", &heroi);
          dialogBox(allegro, "Permitam-me deixá-los a sós para desfrutarem deste momento de reencontro. Estarei em meus aposentos se precisarem de algo mais.", &heroi);
          dialogBox(allegro, "Obrigado Alex!", &king);
          alreadyTalked = true;
        }
      }

      if( alreadyTalked ) {
        if( heroi.posY+heroi.altura < 170 )
          heroi.indoBaixo = true;
        else if( heroi.posY+heroi.altura < 600 ) {
          heroi.indoBaixo = false;
          if( heroi.posX+heroi.largura/2 > 487) 
            heroi.indoEsquerda = true;
          else 
            heroi.indoEsquerda = false;

          if( heroi.posX+heroi.largura/2 < 483 ) 
            heroi.indoDireita = true;
          else if( heroi.posX+heroi.largura/2 > 483 && heroi.posX+heroi.largura/2 < 487 && heroi.posY+heroi.altura < 600 ) {
            heroi.indoDireita = false;
            heroi.indoBaixo = true;
          } 
        } else if( heroi.posX+heroi.largura/2 < 580 ) {
          heroi.indoBaixo = false;
          heroi.indoDireita = true;
        } else if( heroi.posY+heroi.altura < 800) {
          heroi.indoDireita = false;
          heroi.indoBaixo = true;
        } else {
          heroi.indoBaixo = false;
          gameStatus->coming = END;
          gameStatus->going = MENU;
          done = true;
        }
      }

      al_flip_display();
    }
  } while(!done);

  al_destroy_bitmap(lobby);  
  al_destroy_bitmap(heroi.sprite);  
  al_destroy_bitmap(heroi.face);  
  al_destroy_bitmap(king.sprite);  
  al_destroy_bitmap(king.face);  
  al_destroy_bitmap(princess.sprite);  
  al_destroy_bitmap(princess.face);  
} 

void meetHero(Personagem* character){
  if( character->indoCima ) {
    character->posY -= character->vel;
    character->frameAtualY = character->altura * 3; 
  } 
  else if( character->indoBaixo ) {
    character->posY += character->vel;
    character->frameAtualY = character->altura * 0; 
  }
  else if( character->indoDireita ) {
    character->posX += character->vel;
    character->frameAtualY = character->altura * 2; 
  }
  else if( character->indoEsquerda ) {
    character->posX -= character->vel;
    character->frameAtualY = character->altura * 1; 
  }

  character->frame += 0.13;
  if( character->frame > character->frameMax ) 
    character->frame -= character->frameMax;

  // seguir o heroi
  double angulo = atan2((double)heroi.posY - character->posY, (double)heroi.posX - character->posX);
  double cosPositive = cos(angulo) > 0 ? cos(angulo) : -cos(angulo);
  double sinPositive = sin(angulo) > 0 ? sin(angulo) : -sin(angulo);

  if( cosPositive > sinPositive ) {
    character->indoBaixo = false;
    character->indoCima = false;
    if( cos(angulo) > 0 && cos(angulo) != sin(angulo)) {
      character->indoEsquerda = false;
      character->indoDireita = true;
    } else if( cos(angulo) < 0 && cos(angulo) != sin(angulo)) {
      character->indoEsquerda = true;
      character->indoDireita = false;
    } 
  } else if( cosPositive < sinPositive ) {
    character->indoEsquerda = false;
    character->indoDireita = false;
    if( sin(angulo) > 0 && cos(angulo) != sin(angulo)) {
      character->indoCima = false;
      character->indoBaixo = true;
    } else if (sin(angulo) < 0 && cos(angulo) != sin(angulo)) {
      character->indoCima = true;
      character->indoBaixo = false;
    }
  } 
}
