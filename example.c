#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h> // biblioteca padrão do Allegro
#include <allegro5/allegro_font.h> 
#include <allegro5/allegro_ttf.h> // biblioteca para adicionar nossas fontes
#include <allegro5/allegro_image.h> // biblioteca para adicionar nossas imagens
#include <allegro5/keyboard.h> // biblioteca para usar o teclado

int main (){

  al_init(); // para iniciar o Allegro
  al_init_font_addon(); 
  al_init_ttf_addon(); // para iniciar o adicionador das nossas fontes
  al_init_image_addon(); // para iniciar o adicionador das nossas imagens
  al_install_keyboard(); // para instalar o teclado no game
  al_install_mouse();

// criamos nossa "janela" e definimos o tamanho dela
  ALLEGRO_DISPLAY * display = al_create_display(1280,720);

// aqui é para informar onde vai abrir essa janela
  al_set_window_position(display, 200, 200); 
// aqui é para definir o titulo da janela
  al_set_window_title(display, "Here Be Dragons!");

// definimos nossa fonte -> passamos o caminho do arquivo, tamanho, display(sempre 0)
  ALLEGRO_FONT* font = al_load_font("./font.ttf", 25, 0); 

// aqui é pra definir o FPS
  ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0); 

// aqui carregamos as nossas imagens
  ALLEGRO_BITMAP * sprite = al_load_bitmap("./dragon.png"); // 573 / 3 = 191 -> largura; 644 / 4 = 161 -> altura;
  ALLEGRO_BITMAP * bg = al_load_bitmap("./bg.png");

// aqui definimos a fila de eventos
  ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue(); 
// registramos um evento, a nossa janela!
  al_register_event_source(event_queue, al_get_display_event_source(display)); 
// registramos o timer/FPS
  al_register_event_source(event_queue, al_get_timer_event_source(timer)); 
// registramos os eventos do teclado
  al_register_event_source(event_queue, al_get_keyboard_event_source());

  al_start_timer(timer); // para poder utilizar os eventos

  float frame = 0.f; // frame da imagem
  int pos_x = 0, pos_y = 0; // posições x e y do dragão
  int current_frame_y = 161; // frame y atual

  while(true){
// criamos variável evento
    ALLEGRO_EVENT event; 
// para esperar um evento, passamos a fila de eventos e o endereço do evento criado acima
    al_wait_for_event(event_queue, &event);
// aqui verifica se o usuário clicou no X da janela 
    if( event.type == ALLEGRO_EVENT_DISPLAY_CLOSE ){ 
      break; // para o loop(while) e termina o game
    }else if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT) { // se apertar seta direita do teclado
// altura dos frames da imagem que vão para direita
       current_frame_y = 161; 
// vai movimentar o pos_x para direita
       pos_x += 20; 
    }else if(event.keyboard.keycode == ALLEGRO_KEY_LEFT) { // se apertar seta esquerda do teclado
// altura dos frames da imagem que vão para esquerda
       current_frame_y = 161 * 3; 
// vai movimentar o pos_x para esquerda
       pos_x -= 20; 
    }else if(event.keyboard.keycode == ALLEGRO_KEY_DOWN) { // se apertar seta baixo do teclado
// altura dos frames da imagem que vão para baixo
       current_frame_y = 161 * 2; 
// vai movimentar o pos_y para baixo
       pos_y += 20; 
    }else if(event.keyboard.keycode == ALLEGRO_KEY_UP) { // se apertar seta cima do teclado
// altura dos frames da imagem que vão para cima
       current_frame_y = 0; 
// vai movimentar o pos_y para cima
       pos_y -= 20; 
    }

    frame += 0.3; // incrementamos um valor, quanto menor mais lento
    if(frame > 3) { // temos 3 frames, então não pode passar de 3
       frame -= 3; // se passar de 3, volta pra 0
    }

    al_clear_to_color(al_map_rgb(255,255,255));// para colocar uma cor.

// para desenhar uma imagem na tela; imagem, pos_x, pos_y, display(Sempre 0)
    al_draw_bitmap(bg, 0, 0, 0);

// para desenhar uma parte da imagem; imagem, ponto_x, ponto_y, larg, altu, pos_x, pos_y, display(sempre 0)
    al_draw_bitmap_region(sprite, 191 * (int)frame, current_frame_y, 191, 161, pos_x, pos_y, 0);

// para escrever na tela
// passamos a fonte, a cor, pos_x, pos_y, display(passamos sempre 0), texto;
    al_draw_text(font, al_map_rgb(0, 0, 0), 7, 7, 0, "SCORE: DRAGONS"); // para fazer sombreamento
    al_draw_text(font, al_map_rgb(255, 255, 255), 5, 5, 0, "SCORE: DRAGONS"); 
    al_flip_display();
  }

// Aqui precisamos excluir a maioria das coisas que criamos
  al_destroy_bitmap(bg);
  al_destroy_bitmap(sprite);
  al_destroy_font(font);
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);

  return 0;
}
