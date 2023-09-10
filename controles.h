#include <allegro5/allegro.h>

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
} Personagem;

Personagem protagonista = {0, 0, 4, false, false, false, false, 0.f, 3, 0};

void controles(ALLEGRO_EVENT evento) {  
  protagonista.indoDireita = ( evento.keyboard.keycode == ALLEGRO_KEY_RIGHT || evento.keyboard.keycode == ALLEGRO_KEY_D );
  protagonista.indoEsquerda = ( evento.keyboard.keycode == ALLEGRO_KEY_LEFT || evento.keyboard.keycode == ALLEGRO_KEY_A );
  protagonista.indoBaixo = ( evento.keyboard.keycode == ALLEGRO_KEY_DOWN || evento.keyboard.keycode == ALLEGRO_KEY_S );  
  protagonista.indoCima = ( evento.keyboard.keycode == ALLEGRO_KEY_UP || evento.keyboard.keycode == ALLEGRO_KEY_W ); 

  if( protagonista.indoCima ) {
    protagonista.posY -= protagonista.vel;
    protagonista.frameAtualY = 48.5 * 3; 
    protagonista.frame += 0.2;
    if( protagonista.frame > protagonista.frameMax ) 
      protagonista.frame -= protagonista.frameMax; 
  } 
  
  if( protagonista.indoDireita ) {
    protagonista.posX += protagonista.vel;
    protagonista.frameAtualY = 48.5 * 2; 
    protagonista.frame += 0.2;
    if( protagonista.frame > protagonista.frameMax ) 
      protagonista.frame -= protagonista.frameMax; 
  }
  
  if( protagonista.indoBaixo ) {
    protagonista.posY += protagonista.vel;
    protagonista.frameAtualY = 48.5 * 0; 
    protagonista.frame += 0.2;
    if( protagonista.frame > protagonista.frameMax ) 
      protagonista.frame -= protagonista.frameMax; 
  }
  
  if( protagonista.indoEsquerda ) {
    protagonista.posX -= protagonista.vel;
    protagonista.frameAtualY = 48.5 * 1; 
    protagonista.frame += 0.2;
    if( protagonista.frame > protagonista.frameMax ) 
      protagonista.frame -= protagonista.frameMax;
  }
}
