#include "eventos.h"

#define JANELA_LARGURA 1280
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
  ALLEGRO_BITMAP* imgFundo = al_load_bitmap("./assets/mapa.png");
  ALLEGRO_MOUSE_STATE mouse;

// DECLARAÇÕES NOSSA
  protagonista.sprite = al_load_bitmap("./assets/andando.png");
  bool jogando = true;

  al_set_window_position(janela, 200, 200); 
  al_set_window_title(janela, "Save the princess!");

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
          if( protagonista.indoCima || protagonista.indoDireita || protagonista.indoBaixo || protagonista.indoEsquerda ) {
            movimentacao(); // movimentação do player por enquanto
          }
          if( protagonista.estaAtacando ) {
            al_get_mouse_state(&mouse);
            atacar(mouse.x, mouse.y);
          }
          break;
        case ALLEGRO_EVENT_KEY_DOWN:
          if ( evento.keyboard.keycode == ALLEGRO_KEY_RIGHT || evento.keyboard.keycode == ALLEGRO_KEY_D ) {
            protagonista.indoDireita = true;
          }
          else if ( evento.keyboard.keycode == ALLEGRO_KEY_LEFT || evento.keyboard.keycode == ALLEGRO_KEY_A ) {
            protagonista.indoEsquerda = true;
          }
          else if ( evento.keyboard.keycode == ALLEGRO_KEY_DOWN || evento.keyboard.keycode == ALLEGRO_KEY_S ) {
            protagonista.indoBaixo = true;
          }
          else if ( evento.keyboard.keycode == ALLEGRO_KEY_UP || evento.keyboard.keycode == ALLEGRO_KEY_W ) {
            protagonista.indoCima = true;
          }
          break;
        case ALLEGRO_EVENT_KEY_UP:
          if ( evento.keyboard.keycode == ALLEGRO_KEY_RIGHT || evento.keyboard.keycode == ALLEGRO_KEY_D ) {
            protagonista.indoDireita = false;
          }
          if ( evento.keyboard.keycode == ALLEGRO_KEY_LEFT || evento.keyboard.keycode == ALLEGRO_KEY_A ) {
            protagonista.indoEsquerda = false;
          }
          if ( evento.keyboard.keycode == ALLEGRO_KEY_DOWN || evento.keyboard.keycode == ALLEGRO_KEY_S ) {
            protagonista.indoBaixo = false;
          }
          if ( evento.keyboard.keycode == ALLEGRO_KEY_UP || evento.keyboard.keycode == ALLEGRO_KEY_W ) {
            protagonista.indoCima = false;
          }
          break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
          if( evento.mouse.button == 1 ) {
            protagonista.estaAtacando = true;
          }
          break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
          if( evento.mouse.button == 1 ) {
            protagonista.estaAtacando = false;
          }
          break;
        
      }
    }
    
    // caso passou o tempo de FPS ele redesenha a tela
    if(redesenha) {
      al_clear_to_color(al_map_rgb(0 ,0 ,0 ));
      // al_draw_bitmap(imgFundo, 0, 0, 0);
      al_draw_bitmap_region(protagonista.sprite, 47 * (int)protagonista.frame, protagonista.frameAtualY, 47, 48.5, protagonista.pos.x, protagonista.pos.y, 0); // imagem, ponto_img_x, ponto_img_y, larg, altu, pos_x, pos_y, display(sempre 0)

      
      for(int i = 0; i < 5; i++) {
        if( protagonista.tiros[i].ativo && (protagonista.tiros[i].pos.x > JANELA_LARGURA || protagonista.tiros[i].pos.x < 0 || protagonista.tiros[i].pos.y > JANELA_ALTURA || protagonista.tiros[i].pos.y < 0) ) {
          protagonista.tiros[i].ativo = false;
          al_destroy_bitmap(protagonista.tiros[i].image);
        }

        if( protagonista.tiros[i].ativo ) {
          protagonista.tiros[i].pos.x += 6 * cos(protagonista.tiros[i].angulo);
          protagonista.tiros[i].pos.y += 6 * sin(protagonista.tiros[i].angulo);
          al_draw_bitmap(protagonista.tiros[i].image, protagonista.tiros[i].pos.x, protagonista.tiros[i].pos.y, 0);
        }
      }

      al_flip_display();
    }
  }

// Aqui precisamos excluir a maioria das coisas que criamos
  al_destroy_bitmap(imgFundo);
  al_destroy_bitmap(protagonista.sprite);
  al_destroy_display(janela);
  al_destroy_event_queue(fila_eventos);
  al_destroy_timer(timer);

// Frees

  return 0;
}
