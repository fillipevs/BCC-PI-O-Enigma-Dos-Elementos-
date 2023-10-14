#include <math.h>
#include "structs.h"
#include "eventos.h"
#include "inimigo.h"

#define JANELA_LARGURA 1020
#define JANELA_ALTURA 720

int main (){
  al_init(); 
  al_init_image_addon(); 
  al_install_keyboard();
  al_install_mouse();

// DECLARAÇÕES ALLEGRO
  ALLEGRO_DISPLAY* janela = al_create_display(JANELA_LARGURA, JANELA_ALTURA);
  ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0); 
  ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue(); 
  ALLEGRO_MOUSE_STATE mouse;
  ALLEGRO_BITMAP* lobby = al_load_bitmap("./assets/mapa.bmp");

// DECLARAÇÕES NOSSA
  heroi.sprite = al_load_bitmap("./assets/andando.png");
  bobOmb.sprite = al_load_bitmap("./assets/bob-omb-0.png");
  bool jogando = true;

  al_set_window_position(janela, 200, 200); 
  al_set_window_title(janela, "O Enigma dos Elementos");

  al_register_event_source(fila_eventos, al_get_display_event_source(janela)); 
  al_register_event_source(fila_eventos, al_get_timer_event_source(timer)); 
  al_register_event_source(fila_eventos, al_get_keyboard_event_source());
  al_register_event_source(fila_eventos, al_get_mouse_event_source());
  al_start_timer(timer); 

  while(jogando){
    bool redesenha = false;

    while(!al_is_event_queue_empty(fila_eventos)) {
      ALLEGRO_EVENT evento; 
      al_wait_for_event(fila_eventos, &evento);

      // verifica quais eventos estão ocorrendo
      switch(evento.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE: 
          jogando = false;
          break;
        case ALLEGRO_EVENT_TIMER:
          redesenha = true;
          movi();
          if( heroi.indoCima || heroi.indoDireita || heroi.indoBaixo || heroi.indoEsquerda ) {
            movimentacao(); // movimentação do player por enquanto
          }
          if( heroi.estaAtacando ) {
            al_get_mouse_state(&mouse);
            atacar(mouse.x, mouse.y);
          }
          break;
        case ALLEGRO_EVENT_KEY_DOWN:
          if ( evento.keyboard.keycode == ALLEGRO_KEY_RIGHT || evento.keyboard.keycode == ALLEGRO_KEY_D ) {
            heroi.indoDireita = true;
          }
          else if ( evento.keyboard.keycode == ALLEGRO_KEY_LEFT || evento.keyboard.keycode == ALLEGRO_KEY_A ) {
            heroi.indoEsquerda = true;
          }
          else if ( evento.keyboard.keycode == ALLEGRO_KEY_DOWN || evento.keyboard.keycode == ALLEGRO_KEY_S ) {
            heroi.indoBaixo = true;
          }
          else if ( evento.keyboard.keycode == ALLEGRO_KEY_UP || evento.keyboard.keycode == ALLEGRO_KEY_W ) {
            heroi.indoCima = true;
          }
          break;
        case ALLEGRO_EVENT_KEY_UP:
          if ( evento.keyboard.keycode == ALLEGRO_KEY_RIGHT || evento.keyboard.keycode == ALLEGRO_KEY_D ) {
            heroi.indoDireita = false;
          }
          if ( evento.keyboard.keycode == ALLEGRO_KEY_LEFT || evento.keyboard.keycode == ALLEGRO_KEY_A ) {
            heroi.indoEsquerda = false;
          }
          if ( evento.keyboard.keycode == ALLEGRO_KEY_DOWN || evento.keyboard.keycode == ALLEGRO_KEY_S ) {
            heroi.indoBaixo = false;
          }
          if ( evento.keyboard.keycode == ALLEGRO_KEY_UP || evento.keyboard.keycode == ALLEGRO_KEY_W ) {
            heroi.indoCima = false;
          }
          break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
          if( evento.mouse.button == 1 ) {
            heroi.estaAtacando = true;
          }
          break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
          if( evento.mouse.button == 1 ) {
            heroi.estaAtacando = false;
          }
          break;
        
      }
    }
    
    // caso passou o tempo de FPS ele redesenha a tela
    if(redesenha) {
      al_clear_to_color(al_map_rgb(0 ,0 ,0 ));
      al_draw_bitmap(lobby, 0, 0, 0);
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

// Aqui precisamos excluir a maioria das coisas que criamos
  al_destroy_bitmap(lobby);
  al_destroy_bitmap(heroi.sprite);
  al_destroy_bitmap(bobOmb.sprite);
  al_destroy_event_queue(fila_eventos);
  al_destroy_timer(timer);
  al_destroy_display(janela);

// Frees

  return 0;
}
