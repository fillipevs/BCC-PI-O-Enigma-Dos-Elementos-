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


void atacar(int mx, int my, Interface* interface) {
  if( heroi.tempoAtacar <= 0 ) {
    double angulo = atan2((double)my - heroi.posY, (double)mx - heroi.posX);

    if( heroi.estaAtacando.fireball ) {
      for(int i = 0; i < 5; i++) {
        if( !heroi.tiros[i].ativo ) {
          heroi.tiros[i].altura = 16;
          heroi.tiros[i].largura = 16;
          heroi.tiros[i].angulo = angulo;
          heroi.tiros[i].ativo = true;
          heroi.tiros[i].posX = heroi.posX;
          heroi.tiros[i].posY = heroi.posY;
          heroi.tiros[i].type.fireball = true;
          heroi.tiros[i].type.element = false;
          heroi.tiros[i].image = al_load_bitmap("./assets/poderes/bolafogo.png");
          heroi.tempoAtacar = 6;
          break;
        } 
      }
    } else if( heroi.estaAtacando.element && interface->attack2SlotType != EMPTY ) {
      switch (interface->attack2SlotType) 
      {
      case ACIDO_CLORIDRICO:
        for(int i = 0; i < 5; i++) {
          if( !heroi.tiros[i].ativo ) {
            heroi.tiros[i].altura = 16;
            heroi.tiros[i].largura = 16;
            heroi.tiros[i].angulo = angulo;
            heroi.tiros[i].ativo = true;
            heroi.tiros[i].posX = heroi.posX;
            heroi.tiros[i].posY = heroi.posY;
            heroi.tiros[i].type.element = true;
            heroi.tiros[i].type.fireball = false;
            heroi.tiros[i].image = al_load_bitmap("./assets/e3-t.bmp");
            heroi.tempoAtacar = 6;
            break;
          } 
        }
        break;
      case HIDROXIDO_AMONIO:
        for(int i = 0; i < 5; i++) {
          if( !heroi.tiros[i].ativo ) {
            heroi.tiros[i].altura = 16;
            heroi.tiros[i].largura = 16;
            heroi.tiros[i].angulo = angulo;
            heroi.tiros[i].ativo = true;
            heroi.tiros[i].posX = heroi.posX;
            heroi.tiros[i].posY = heroi.posY;
            heroi.tiros[i].type.element = true;  
            heroi.tiros[i].type.fireball = false;  
            heroi.tiros[i].image = al_load_bitmap("./assets/e2-t.bmp");
            heroi.tempoAtacar = 6;
            break;
          } 
        }
        break;
      
      default:
        break;
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
    interface->attack2Img = al_load_bitmap("./assets/e2.png");
    break;
  default:
    break;
  }
}
