#include "funcoes.h"

void enemyMove(Personagem* enemy){
  if( !enemy->exploding ) {
    // movimentação do inimigo
    if( enemy->indoCima ) {
      enemy->posY -= enemy->vel;
      enemy->frameAtualY = enemy->altura * 0; 
    } 
    else if( enemy->indoBaixo ) {
      enemy->posY += enemy->vel;
      enemy->frameAtualY = enemy->altura * 2; 
    }
    else if( enemy->indoDireita ) {
      enemy->posX += enemy->vel;
      enemy->frameAtualY = enemy->altura * 1; 
    }
    else if( enemy->indoEsquerda ) {
      enemy->posX -= enemy->vel;
      enemy->frameAtualY = enemy->altura * 3; 
    }

    enemy->frame += 0.13;
    if( enemy->frame > enemy->frameMax ) 
      enemy->frame -= enemy->frameMax;

    if( enemy->tempoAtacar > 0 ) {
      enemy->tempoAtacar -= 0.1;
      return;
    }

  // seguir o heroi
    double angulo = atan2((double)heroi.posY - enemy->posY, (double)heroi.posX - enemy->posX);
    double cosPositive = cos(angulo) > 0 ? cos(angulo) : -cos(angulo);
    double sinPositive = sin(angulo) > 0 ? sin(angulo) : -sin(angulo);

    if( cosPositive > sinPositive ) {
      enemy->indoBaixo = false;
      enemy->indoCima = false;
      if( cos(angulo) > 0 && cos(angulo) != sin(angulo)) {
        enemy->indoEsquerda = false;
        enemy->indoDireita = true;
      } else if( cos(angulo) < 0 && cos(angulo) != sin(angulo)) {
        enemy->indoEsquerda = true;
        enemy->indoDireita = false;
      } 
    } else if( cosPositive < sinPositive ) {
      enemy->indoEsquerda = false;
      enemy->indoDireita = false;
      if( sin(angulo) > 0 && cos(angulo) != sin(angulo)) {
        enemy->indoCima = false;
        enemy->indoBaixo = true;
      } else if (sin(angulo) < 0 && cos(angulo) != sin(angulo)) {
        enemy->indoCima = true;
        enemy->indoBaixo = false;
      }
    } 

    enemy->tempoAtacar = 2;
  }
}

void enemyExplosion(Personagem* enemy) {
  if( enemy->vel != 0 ) {
    enemy->frameAtualY = 0;
    enemy->frame = 0;
  }
  enemy->vel = 0;
  al_destroy_bitmap(enemy->sprite);
  enemy->sprite = al_load_bitmap("./assets/inimigos/bob-omb-5.png");
  enemy->largura = 48;
  enemy->altura = 38;

  enemy->frame += 0.13;
  if( enemy->frame > enemy->frameMax ) {
    enemy->frame -= enemy->frameMax;
    enemy->frameAtualY += enemy->altura;

    if(enemy->frameAtualY > enemy->altura && enemy->alive) {
      enemy->alive = false;
      enemy->exploding = false;
      al_destroy_bitmap(enemy->sprite);
    }
  }
}
