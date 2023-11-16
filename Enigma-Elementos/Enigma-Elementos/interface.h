#include "funcoes.h"

void interface(ALLEGRO_BITMAP* heart, ALLEGRO_BITMAP* power, ALLEGRO_BITMAP* element, ALLEGRO_BITMAP* mouseLeft, ALLEGRO_BITMAP* mouseRight) {
  for(int i = 0; i < heroi.lifes; i++) 
    al_draw_bitmap_region(heart, 0, 0, 32, 32, i*30+10, 0, 0);
  al_draw_bitmap(power, 0, 650, 0);
  al_draw_bitmap(element, 0, 690, 0);

  al_draw_bitmap(mouseLeft, 30, 650, 0);
  al_draw_bitmap(mouseRight, 30, 690, 0);
}
