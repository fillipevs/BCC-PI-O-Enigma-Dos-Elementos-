#include "funcoes.h"

bool characterCollision(Personagem* char1, Personagem* char2) {
  if( char1->exploding || char2->exploding ) return false;

  if( 
    (   
      (char1->posX >= char2->posX && char1->posX <= char2->posX+char2->largura) || 
      (char1->posX+char1->largura >= char2->posX && char1->posX+char1->largura <= char2->posX+char2->largura) 
    )
    && 
    ( 
      (char1->posY >= char2->posY && char1->posY <= char2->posY+char2->altura) ||
      (char1->posY+char1->altura >= char2->posY && char1->posY+char1->altura <= char2->posY+char2->altura) 
    )
  ) {
    // character 1
    if( char1->indoCima ) {
      char1->indoCima = false;
      char1->posY += char1->vel;
    }
    if( char1->indoDireita ) {
      char1->indoDireita = false;
      char1->posX -= char1->vel;
    }
    if( char1->indoBaixo ) {
      char1->indoBaixo = false;
      char1->posY -= char1->vel;
    }
    if( char1->indoEsquerda ) {
      char1->indoEsquerda = false;
      char1->posX += char1->vel;
    }

    // character 2
    if( char2->indoCima ) {
      char2->indoCima = false;
      char2->posY += char2->vel;
    }
    if( char2->indoDireita ) {
      char2->indoDireita = false;
      char2->posX -= char2->vel;
    }
    if( char2->indoBaixo ) {
      char2->indoBaixo = false;
      char2->posY -= char2->vel;
    }
    if( char2->indoEsquerda ) {
      char2->indoEsquerda = false;
      char2->posX += char2->vel;
    }

    return true;
  } else {
    return false;
  }
  
}

bool mapCollision(Personagem* char1, MapSquare* square) {

  if( 
    ( char1->posX >= square->x0 && char1->posX+char1->largura <= square->x1) &&
    ( char1->posY+char1->altura >= square->y0 && char1->posY+char1->altura <= square->y1 )
  ) {
    return true;
  } else {
    // character 1
    if( char1->indoCima ) {
      char1->indoCima = false;
      char1->posY += char1->vel;
    }
    if( char1->indoDireita ) {
      char1->indoDireita = false;
      char1->posX -= char1->vel;
    }
    if( char1->indoBaixo ) {
      char1->indoBaixo = false;
      char1->posY -= char1->vel;
    }
    if( char1->indoEsquerda ) {
      char1->indoEsquerda = false;
      char1->posX += char1->vel;
    }

    return false;
  }


}

bool enemyHit(Tiro* shot, Personagem* char1) {
  if( shot->type.element ) return false;

  if( 
    (   
      (shot->posX >= char1->posX && shot->posX <= char1->posX+char1->largura) || 
      (shot->posX+shot->largura >= char1->posX && shot->posX+shot->largura <= char1->posX+char1->largura) 
    )
    && 
    ( 
      (shot->posY >= char1->posY && shot->posY <= char1->posY+char1->altura) ||
      (shot->posY+shot->altura >= char1->posY && shot->posY+shot->altura <= char1->posY+char1->altura) 
    )
  ) {
    if( shot->ativo ) {
      al_destroy_bitmap(shot->image);
    }
    shot->ativo = false;
    char1->exploding = true;
    return true;
  } else {
    return false;
  }
}

bool barreiraHit(Tiro* shot, MapSquare* square) {
  if( shot->type.fireball ) return false;

  if( 
    (   
      (shot->posX >= square->x0 && shot->posX <= square->x1) || 
      (shot->posX+shot->largura >= square->x0 && shot->posX+shot->largura <= square->x1) 
    )
    && 
    ( 
      (shot->posY >= square->y0 && shot->posY <= square->y1) ||
      (shot->posY+shot->altura >= square->y1 && shot->posY+shot->altura <= square->y1) 
    )
  ) {
    if( shot->ativo ) {
      al_destroy_bitmap(shot->image);
    }
    shot->ativo = false;
    return true;
  }
  return false;
}
