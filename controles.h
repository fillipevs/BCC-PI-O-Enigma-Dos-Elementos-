#include "structs.h"

void controles(ALLEGRO_EVENT evento) {  
  // aqui, por enquanto, faz a movimentação e troca da img do protagonista

  if( protagonista.indoCima ) {
    protagonista.posY -= protagonista.vel;
    protagonista.frameAtualY = 48.5 * 3; 
    protagonista.frame += 0.2;
  } 
  
  if( protagonista.indoDireita ) {
    protagonista.posX += protagonista.vel;
    protagonista.frameAtualY = 48.5 * 2; 
    protagonista.frame += 0.2;
  }
  
  if( protagonista.indoBaixo ) {
    protagonista.posY += protagonista.vel;
    protagonista.frameAtualY = 48.5 * 0; 
    protagonista.frame += 0.2;
  }
  
  if( protagonista.indoEsquerda ) {
    protagonista.posX -= protagonista.vel;
    protagonista.frameAtualY = 48.5 * 1; 
    protagonista.frame += 0.2;
  }

  if( protagonista.frame > protagonista.frameMax ) 
    protagonista.frame -= protagonista.frameMax;
}
