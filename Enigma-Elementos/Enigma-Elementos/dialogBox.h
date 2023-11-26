#include "funcoes.h"

void dialogBox(Allegro* allegro, char string[], Personagem* character) {
  bool draw = true;
  bool done = false;

  ALLEGRO_BITMAP* box = al_load_bitmap("./assets/dialog-box.png");

  do {
    while(!al_is_event_queue_empty(allegro->eventQueue)) {
      ALLEGRO_EVENT event; 
      al_wait_for_event(allegro->eventQueue, &event);

      switch(event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE: 
          done = true;
          break;

        case ALLEGRO_EVENT_KEY_DOWN:
          if( event.keyboard.keycode == ALLEGRO_KEY_ENTER || event.keyboard.keycode == ALLEGRO_KEY_SPACE)
            done = true;
          break;
        
        default: 
          break;
      }
    }

    if( draw ) {
      draw = false;

      al_draw_bitmap(box, 0, 460, 0);
      al_draw_bitmap(character->face, 745, 484, 0);
      al_draw_multiline_text(allegro->font[1], al_map_rgb(123, 63, 0), 100, 520, 630, 30, 0, string);

      al_flip_display();
    }
    
  } while(!done);

  al_destroy_bitmap(box);
}
