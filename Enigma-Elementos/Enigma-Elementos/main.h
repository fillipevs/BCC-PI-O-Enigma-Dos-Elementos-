#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/keyboard.h> 
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "constantes.h"
#include "structs.h"
#include "eventos.h"
#include "inimigo.h"
#include "funcoes.h"
#include "dialogBox.h"
#include "menu.h"
#include "prologue.h"
#include "lobby.h"
#include "water.h"
#include "fire.h"
#include "grass.h"
#include "collisions.h"
#include "interface.h"

Allegro init() {
  Allegro allegro;
  srand(time(NULL));

  if( al_init() ) {

    allegro.close = false;

    allegro.display = al_create_display(JANELA_LARGURA, JANELA_ALTURA);
    allegro.eventQueue = al_create_event_queue(); 
    allegro.timer = al_create_timer(1.0 / 60.0);

    al_set_window_position(allegro.display, 200, 200); 
    al_set_window_title(allegro.display, "O Enigma dos Elementos");

    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    allegro.font[0] = al_load_font("./assets/fonts/inter-bold.ttf", 32, 0);
    allegro.font[1] = al_load_font("./assets/fonts/inter-bold.ttf", 26, 0);

    al_init_image_addon(); 
    al_install_keyboard();
    al_install_mouse();
    
    al_set_system_mouse_cursor(allegro.display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

    al_register_event_source(allegro.eventQueue, al_get_display_event_source(allegro.display)); 
    al_register_event_source(allegro.eventQueue, al_get_timer_event_source(allegro.timer)); 
    al_register_event_source(allegro.eventQueue, al_get_keyboard_event_source());
    al_register_event_source(allegro.eventQueue, al_get_mouse_event_source());
    
    al_start_timer(allegro.timer);
  }

  return allegro;
}

void destroy(Allegro* allegro) {
  al_destroy_event_queue(allegro->eventQueue);
  al_destroy_timer(allegro->timer);
  al_destroy_display(allegro->display);
  for(int i = 0; i < 2; i++) 
    al_destroy_font(allegro->font[i]);
}
