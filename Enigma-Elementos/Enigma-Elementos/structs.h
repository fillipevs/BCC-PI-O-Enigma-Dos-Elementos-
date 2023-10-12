#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/keyboard.h> 
#include <allegro5/allegro_image.h> 

#define PI 3.14159265359

typedef struct {
  int posX;
  int posY;
  double angulo;
  int altura;
  int largura;
  ALLEGRO_BITMAP* image;
  bool ativo;
} Tiro;

typedef struct {
  int posX;
  int posY;
  int vel;
  bool indoCima;
  bool indoDireita;
  bool indoBaixo;
  bool indoEsquerda;
  float frame;
  int frameMax;
  int frameAtualY;
  ALLEGRO_BITMAP* sprite; // 141 / 3 = 47 -> largura; 194 / 4 = 48.5 -> altura;
  bool estaAtacando;
  float tempoAtacar;
  Tiro tiros[5];
} Personagem;

Personagem heroi = {
  0, // posição x
  0, // posição y
  1, // velocidade
  false, // cima
  false, // direita
  false, // baixo
  false, // esquerda
  0.f, // frame
  3, // frame máximo
  0, // frame atual y
  NULL, // sprite
  false, // está atacando
  0 // tempo para atacar
};
