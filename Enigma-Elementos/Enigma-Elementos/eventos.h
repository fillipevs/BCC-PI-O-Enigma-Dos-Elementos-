#include "funcoes.h"

void movimentacao(Personagem* character) {  

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
}

void destroyShots(Tiro shots[]) {
  for( int i = 0; i < 5; i++ ) {
    if( shots[i].ativo ) {
      al_destroy_bitmap(shots[i].image);
      shots[i].ativo = false;
    }
  }
}

void morrendo(Personagem* character, bool* done, GameStatus* gameStatus) {
  if( character->alive ) {
    al_destroy_bitmap(character->sprite);
    character->sprite = al_load_bitmap("./assets/heroi/morrendo.png");
    character->frame = 0;
    character->frameAtualY = 0;
    character->alive = false;
  } else {
    character->frame += 0.03;
    if( character->frame > character->frameMax ) {
      character->frame -= character->frameMax;
      *done = true;
      gameStatus->coming = gameStatus->going;
      gameStatus->going = GAMEOVER;
    }
  }
}

void shotExploding(Tiro* shot) {
  shot->vel = 0;
  shot->frame += 0.70;
  if( shot->frame > shot->frameMax ) {
    shot->frame -= shot->frameMax;
    if( shot->ativo ) {
      al_destroy_bitmap(shot->image);
    }
    shot->ativo = false;
  }
}

void atacar(int mx, int my, Interface* interface) {
  if( heroi.tempoAtacar <= 0 ) {
    double angulo = atan2((double)my - heroi.posY, (double)mx - heroi.posX);

    if( heroi.estaAtacando.fireball ) {
      for(int i = 0; i < 5; i++) {
        if( !heroi.tiros[i].ativo ) {
          heroi.tiros[i].altura = 80;
          heroi.tiros[i].largura = 80;
          heroi.tiros[i].angulo = angulo;
          heroi.tiros[i].ativo = true;
          heroi.tiros[i].posX = heroi.posX-20;
          heroi.tiros[i].posY = heroi.posY-20;
          heroi.tiros[i].type.fireball = true;
          heroi.tiros[i].type.element = false;
          heroi.tiros[i].frameMax = 19;
          heroi.tiros[i].frame = 0.0f;
          heroi.tiros[i].vel = 6;
          heroi.tiros[i].isExploding = false;
          heroi.tiros[i].image = al_load_bitmap("./assets/poderes/shot.png");
          heroi.tempoAtacar = 5.5;
          break;
        } 
      }
    } else if( heroi.estaAtacando.element && interface->attack2SlotType != EMPTY ) {
      for( int i = 0; i < 5; i++ ) {
        if( !heroi.tiros[i].ativo ) {
          heroi.tiros[i].altura = 32;
          heroi.tiros[i].largura = 32;
          heroi.tiros[i].angulo = angulo;
          heroi.tiros[i].ativo = true;
          heroi.tiros[i].posX = heroi.posX;
          heroi.tiros[i].posY = heroi.posY;
          heroi.tiros[i].type.element = true;  
          heroi.tiros[i].type.fireball = false;  
          heroi.tiros[i].frameMax = 0;
          heroi.tiros[i].frame = 0.0f;
          heroi.tiros[i].vel = 6;
          heroi.tiros[i].isExploding = false;
          heroi.tempoAtacar = 5.6;

          switch (interface->attack2SlotType) {
            case ACIDO_CLORIDRICO:
              heroi.tiros[i].image = al_load_bitmap("./assets/e3-t.bmp");
              break;
            case HIDROXIDO_AMONIO:
              heroi.tiros[i].image = al_load_bitmap("./assets/e1-t.bmp");
              break;
            case VERIFICATION:
              heroi.tiros[i].image = al_load_bitmap("./assets/e2-t.bmp");
              break;
            default:
              break;
          }
          break;
        }
      }
    }
  } 
}

void takeElement(Interface* interface, Crystal* crystal) {
  if( interface->attack2SlotType == crystal->name ) return;

  al_destroy_bitmap(interface->attack2Img);
  interface->attack2SlotType = EMPTY;

  switch (crystal->name)
  {
  case ACIDO_CLORIDRICO:
    interface->attack2SlotType = ACIDO_CLORIDRICO;
    interface->attack2Img = al_load_bitmap("./assets/e3.png");
    break;
  case HIDROXIDO_AMONIO:
    interface->attack2SlotType = HIDROXIDO_AMONIO;
    interface->attack2Img = al_load_bitmap("./assets/e1.png");
    break;
  case VERIFICATION:
    interface->attack2SlotType = VERIFICATION;
    interface->attack2Img = al_load_bitmap("./assets/e2.png");
    break;
  case EMPTY: 
    interface->attack2SlotType = EMPTY;
    interface->attack2Img = al_load_bitmap("./assets/slotEmpty.png");
    break;
  default:
    break;
  }
}
