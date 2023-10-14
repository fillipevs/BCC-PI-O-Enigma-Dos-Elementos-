void movimentacao() {  
  // aqui, por enquanto, faz a movimentação e troca da img do heroi

  if( heroi.indoCima ) {
    heroi.posY -= heroi.vel;
    heroi.frameAtualY = 48.5 * 3; 
  } 
  
  if( heroi.indoDireita ) {
    heroi.posX += heroi.vel;
    heroi.frameAtualY = 48.5 * 2; 
  }
  
  if( heroi.indoBaixo ) {
    heroi.posY += heroi.vel;
    heroi.frameAtualY = 48.5 * 0; 
  }
  
  if( heroi.indoEsquerda ) {
    heroi.posX -= heroi.vel;
    heroi.frameAtualY = 48.5 * 1; 
  }

  heroi.frame += 0.15;
  if( heroi.frame > heroi.frameMax ) 
    heroi.frame -= heroi.frameMax;
}

// mx --> posição x do mouse
// my --> posição y do mouse
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
