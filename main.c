#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/keyboard.h> 
#include <allegro5/allegro_image.h> 

#include "controles.h"

#define JANELA_LARGURA 1280
#define JANELA_ALTURA 720

int main (){
  al_init(); 
  al_init_image_addon(); 
  al_install_keyboard();
  al_install_mouse();

  ALLEGRO_DISPLAY* janela = al_create_display(JANELA_LARGURA, JANELA_ALTURA);
  ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0); 
  ALLEGRO_BITMAP* sprite; // 141 / 3 = 47 -> largura; 194 / 4 = 48.5 -> altura;
  ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue(); 

  al_set_window_position(janela, 200, 200); 
  al_set_window_title(janela, "Save the princess!");

  al_register_event_source(fila_eventos, al_get_display_event_source(janela)); 
  al_register_event_source(fila_eventos, al_get_timer_event_source(timer)); 
  al_register_event_source(fila_eventos, al_get_keyboard_event_source());
  al_start_timer(timer); 

  sprite = al_load_bitmap("./assets/andando.png"); 
  while(true){
    ALLEGRO_EVENT evento; 
    al_wait_for_event(fila_eventos, &evento);

    if( evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE ){ 
      break; 
    } else {
      controles(evento);
    }

    al_clear_to_color(al_map_rgb(0 ,0 ,0 ));
    al_draw_bitmap_region(sprite, 47 * (int)protagonista.frame, protagonista.frameAtualY, 47, 48.5, protagonista.posX, protagonista.posY, 0); // imagem, ponto_img_x, ponto_img_y, larg, altu, pos_x, pos_y, display(sempre 0)

    al_flip_display();
  }

// Aqui precisamos excluir a maioria das coisas que criamos
  al_destroy_bitmap(sprite);
  al_destroy_display(janela);
  al_destroy_event_queue(fila_eventos);

  return 0;
}
