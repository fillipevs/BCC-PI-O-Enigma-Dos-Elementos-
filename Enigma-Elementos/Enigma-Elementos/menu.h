#include "funcoes.h"

GAME_STATUS menu(Allegro* allegro) {
  GAME_STATUS gameStatus = MENU;
  bool draw = false;
  bool done = false;

  ALLEGRO_BITMAP* menu = al_load_bitmap("./assets/menu/menu.bmp");
  Button btnPlay = {al_load_bitmap("./assets/menu/botao.png"), JANELA_LARGURA/2.6, JANELA_ALTURA/2.1, 240, 80, 0, false, JANELA_LARGURA/2.25, JANELA_ALTURA/2.01, "JOGAR"};

  Button btnExit = {al_load_bitmap("./assets/menu/botao.png"), JANELA_LARGURA/2.6, JANELA_ALTURA/1.6, 240, 80, 0, false, JANELA_LARGURA/2.15, JANELA_ALTURA/1.55, "SAIR"};

  do {
    while(!al_is_event_queue_empty(allegro->eventQueue)) {
      ALLEGRO_EVENT event; 
      al_wait_for_event(allegro->eventQueue, &event);

      switch (event.type)
      {
      case ALLEGRO_EVENT_DISPLAY_CLOSE: 
        done = true;
        gameStatus = EXIT;
        break;
      case ALLEGRO_EVENT_TIMER:
          draw = true;
          break;
      case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
        if( event.mouse.x > btnPlay.x && event.mouse.x < btnPlay.x + btnPlay.width && event.mouse.y > btnPlay.y && event.mouse.y < btnPlay.y + btnPlay.height) {
          btnPlay.frameX = 1;
          btnPlay.textY += 10;
        } 

        if( event.mouse.x > btnExit.x && event.mouse.x < btnExit.x + btnExit.width && event.mouse.y > btnExit.y && event.mouse.y < btnExit.y + btnExit.height) {
          btnExit.frameX = 1;
          btnExit.textY += 10;
        } 
        break;
      case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
        if( btnPlay.frameX != 0 ) {
          btnPlay.frameX = 0;
          btnPlay.textY -= 10;
          done = true;
          gameStatus = PROLOGUE;
        } 

        if( btnExit.frameX != 0 ) {
          btnExit.frameX = 0;
          btnExit.textY -= 10;
          done = true;
          gameStatus = EXIT;
        } 
        break;
      
      default:
        break;
      }
      
    }

    if( draw ) {
      draw = false;
      al_clear_to_color(al_map_rgb(0,0,0));
      al_draw_bitmap(menu, 0, 0, 0);

      al_draw_bitmap_region(btnPlay.image, btnPlay.width * btnPlay.frameX, 0, btnPlay.width, btnPlay.height, btnPlay.x, btnPlay.y, 0); 
      al_draw_text(allegro->font[0], al_map_rgb(0,0,0), btnPlay.textX, btnPlay.textY, 0, btnPlay.text);

      al_draw_bitmap_region(btnExit.image, btnExit.width * btnExit.frameX, 0, btnExit.width, btnExit.height, btnExit.x, btnExit.y, 0); 
      al_draw_text(allegro->font[0], al_map_rgb(0,0,0), btnExit.textX, btnExit.textY, 0, btnExit.text);

      al_flip_display();
    }
  } while(!done);

  al_destroy_bitmap(menu);  
  al_destroy_bitmap(btnPlay.image);
  al_destroy_bitmap(btnExit.image);

  return gameStatus;
}
