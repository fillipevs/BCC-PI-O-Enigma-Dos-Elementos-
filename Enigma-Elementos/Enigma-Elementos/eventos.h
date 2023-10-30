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


void atacar(int mx, int my) {
  if( heroi.tempoAtacar <= 0 ) {
    double angulo = atan2((double)my - heroi.posY, (double)mx - heroi.posX);

    for(int i = 0; i < 5; i++) {
      if( !heroi.tiros[i].ativo ) {
        heroi.tiros[i].altura = 16;
        heroi.tiros[i].largura = 16;
        heroi.tiros[i].angulo = angulo;
        heroi.tiros[i].ativo = true;
        heroi.tiros[i].posX = heroi.posX;
        heroi.tiros[i].posY = heroi.posY;
        heroi.tiros[i].image = al_load_bitmap("./assets/poderes/bolafogo.png");
        break;
      } 
    }
    
    heroi.tempoAtacar = 6;
  } else {
    heroi.tempoAtacar -= 0.1;
  }

}
