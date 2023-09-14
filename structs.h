#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/keyboard.h> 
#include <allegro5/allegro_image.h> 

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
} Personagem;

Personagem protagonista = {0, 0, 1, false, false, false, false, 0.f, 3, 0};
