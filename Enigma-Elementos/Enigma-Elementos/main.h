#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/keyboard.h> 
#include <allegro5/allegro_image.h> 

#include "constantes.h"
#include "structs.h"
#include "eventos.h"
#include "inimigo.h"
#include "funcoes.h"

Allegro init() {
  Allegro allegro;

  if( al_init() ) {

    allegro.close = false;

    allegro.display = al_create_display(JANELA_LARGURA, JANELA_ALTURA);
    allegro.eventQueue = al_create_event_queue(); 
    allegro.timer = al_create_timer(1.0 / 60.0);

    al_set_window_position(allegro.display, 200, 200); 
    al_set_window_title(allegro.display, "O Enigma dos Elementos");

    al_init_image_addon(); 
    al_install_keyboard();
    al_install_mouse();

    al_register_event_source(allegro.eventQueue, al_get_display_event_source(allegro.display)); 
    al_register_event_source(allegro.eventQueue, al_get_timer_event_source(allegro.timer)); 
    al_register_event_source(allegro.eventQueue, al_get_keyboard_event_source());
    al_register_event_source(allegro.eventQueue, al_get_mouse_event_source());
    
    al_start_timer(allegro.timer); 

    heroi.sprite = al_load_bitmap("./assets/andando.png");
    bobOmb.sprite = al_load_bitmap("./assets/bob-omb-0.png");
  }

  return allegro;
}

void destroy(Allegro* allegro) {
  al_destroy_bitmap(heroi.sprite);
  al_destroy_bitmap(bobOmb.sprite);

  al_destroy_event_queue(allegro->eventQueue);
  al_destroy_timer(allegro->timer);
  al_destroy_display(allegro->display);
}
