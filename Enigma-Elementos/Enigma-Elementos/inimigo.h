float timerr = 0;

void movi(){

  if(timerr <= 0) {
    if( bobOmb.indoCima ) {
      bobOmb.indoDireita = true;
      bobOmb.indoCima = false;
    } else if( bobOmb.indoDireita ) {
      bobOmb.indoBaixo = true;
      bobOmb.indoDireita = false;
    } else if( bobOmb.indoBaixo ) {
      bobOmb.indoEsquerda = true;
      bobOmb.indoBaixo = false;
    } else if( bobOmb.indoEsquerda ) {
      bobOmb.indoCima = true;
      bobOmb.indoEsquerda = false;
    } else {
      bobOmb.indoCima = true;
    }

    timerr = 20;
  } else {

    if( bobOmb.indoCima ) {
      bobOmb.frameAtualY = 38 * 0;
      bobOmb.posY -= bobOmb.vel;

    } else if( bobOmb.indoDireita ) {
      bobOmb.frameAtualY = 38 * 1;
      bobOmb.posX += bobOmb.vel;

    } else if( bobOmb.indoBaixo ) {
      bobOmb.frameAtualY = 38 * 2;
      bobOmb.posY += bobOmb.vel;
      
    } else if( bobOmb.indoEsquerda ) {
      bobOmb.frameAtualY = 38 * 3;
      bobOmb.posX -= bobOmb.vel;
      
    }

    // bobOmb.frame = 0;
    bobOmb.frame += 0.085;
    if( bobOmb.frame > bobOmb.frameMax )
      bobOmb.frame -= bobOmb.frameMax;

    timerr -= 0.1;
  }
}
