#include "structs.h"
#include <math.h>

void movimentacao() {  
  // aqui, por enquanto, faz a movimentação e troca da img do protagonista

  if( protagonista.indoCima ) {
    protagonista.pos.y -= protagonista.vel;
    protagonista.frameAtualY = 48.5 * 3; 
  } 
  
  if( protagonista.indoDireita ) {
    protagonista.pos.x += protagonista.vel;
    protagonista.frameAtualY = 48.5 * 2; 
  }
  
  if( protagonista.indoBaixo ) {
    protagonista.pos.y += protagonista.vel;
    protagonista.frameAtualY = 48.5 * 0; 
  }
  
  if( protagonista.indoEsquerda ) {
    protagonista.pos.x -= protagonista.vel;
    protagonista.frameAtualY = 48.5 * 1; 
  }

  if( protagonista.indoCima || protagonista.indoDireita || protagonista.indoBaixo || protagonista.indoEsquerda ) {
    protagonista.frame += 0.2;
  }

  if( protagonista.frame > protagonista.frameMax ) 
    protagonista.frame -= protagonista.frameMax;
}

// mx --> posição x do mouse
// my --> posição y do mouse
void atacar(int mx, int my) {
  if( protagonista.tempoAtacar <= 0 ) {
    double angulo = atan2((double)my - protagonista.pos.y, (double)mx - protagonista.pos.x);

    for(int i = 0; i < 5; i++) {
      if( !protagonista.tiros[i].ativo ) {
        protagonista.tiros[i].altura = 32;
        protagonista.tiros[i].largura = 32;
        protagonista.tiros[i].angulo = angulo;
        protagonista.tiros[i].ativo = true;
        protagonista.tiros[i].pos.x = protagonista.pos.x;
        protagonista.tiros[i].pos.y = protagonista.pos.y;
        protagonista.tiros[i].image = al_load_bitmap("./assets/bolafogo1.png");
      } 
    }
    
    protagonista.tempoAtacar = 10;
  } else {
    protagonista.tempoAtacar -= 0.1;
  }

}
