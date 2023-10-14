#include "main.h"

int main () {

  Allegro allegro = init();

  while(!allegro.close) {
    bool desenhar = false;

    eventos(&allegro, &desenhar);
    
    if( desenhar ) {
      al_clear_to_color(al_map_rgb(0 ,0 ,0 ));
      al_draw_bitmap_region(heroi.sprite, heroi.largura * (int)heroi.frame, heroi.frameAtualY, heroi.largura, heroi.altura, heroi.posX, heroi.posY, 0); // imagem, ponto_img_x, ponto_img_y, larg, altu, pos_x, pos_y, display(sempre 0)
      al_draw_bitmap_region(bobOmb.sprite, bobOmb.largura * (int)bobOmb.frame, bobOmb.frameAtualY, bobOmb.largura, bobOmb.altura, bobOmb.posX, bobOmb.posY, 0); // imagem, ponto_img_x, ponto_img_y, larg, altu, pos_x, pos_y, display(sempre 0)

      for(int i = 0; i < 5; i++) {
        if( heroi.tiros[i].ativo && (heroi.tiros[i].posX > JANELA_LARGURA || heroi.tiros[i].posX < 0 || heroi.tiros[i].posY > JANELA_ALTURA || heroi.tiros[i].posY < 0) ) {
          heroi.tiros[i].ativo = false;
          al_destroy_bitmap(heroi.tiros[i].image);
        }

        if( heroi.tiros[i].ativo ) {
          heroi.tiros[i].posX += 6 * cos(heroi.tiros[i].angulo);
          heroi.tiros[i].posY += 6 * sin(heroi.tiros[i].angulo);
          al_draw_bitmap(heroi.tiros[i].image, heroi.tiros[i].posX, heroi.tiros[i].posY, 0);
        }
      }

      al_flip_display();
    }
  }

  destroy(&allegro);
  return 0;
}
