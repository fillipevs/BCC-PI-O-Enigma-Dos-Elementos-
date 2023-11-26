#include "funcoes.h"

void showInterface(Interface* interface) {
  for(int i = 0; i < heroi.lifes; i++) 
    al_draw_bitmap_region(interface->heart, 0, 0, 32, 32, i*30+10, 0, 0);
  al_draw_bitmap(interface->attack1Img, 990, 650, 0);
  al_draw_bitmap(interface->attack2Img, 990, 690, 0);

  al_draw_bitmap(interface->mouseBtnLeftImg, 960, 650, 0);
  al_draw_bitmap(interface->mouseBtnRightImg, 960, 690, 0);
}
