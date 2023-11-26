#include "funcoes.h"

void water(Allegro* allegro, GameStatus* gameStatus, Interface* interface) {
  bool draw = false;
  bool done = false;
  bool talkAboutElement = false;
  float heroCrystalDistance = 0.0f;

  MapSquare square1 = {430, 658, 45, 80};
  MapSquare square2 = {72, 790, 66, 136};
  MapSquare square3 = {108, 950, 100, 397};
  MapSquare square4 = {870, 1010, 100, 136};
  MapSquare square5 = {133, 950, 393, 467};

  Crystal crystal;
  crystal.name = HIDROXIDO_AMONIO;
  crystal.posX = 128;
  crystal.posY = 419;

  ALLEGRO_BITMAP* agua = al_load_bitmap("./assets/mapa/agua.bmp");
  heroi.sprite = al_load_bitmap("./assets/heroi/andando.png");
  heroi.face = al_load_bitmap("./assets/heroi/face.png");
  heroi.posX = 500;
  heroi.posY = 0;
  heroi.frameAtualY = 0;

  do {
    while(!al_is_event_queue_empty(allegro->eventQueue)) {
      ALLEGRO_EVENT event; 
      al_wait_for_event(allegro->eventQueue, &event);

      switch(event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE: 
          done = true;
          gameStatus->going = EXIT;
          break;

        case ALLEGRO_EVENT_TIMER:
          draw = true;
          al_get_mouse_state(&allegro->mouse);
        // colisão do herói com o mapa
          if( heroi.posX >= 430 && heroi.posX <= 658 && heroi.posY+heroi.altura >= 45 && heroi.posY+heroi.altura <= 70) {
            mapCollision(&heroi, &square1);
          } else if( heroi.posX >= 72 && heroi.posX <= 740 && heroi.posY+heroi.altura >= 66 && heroi.posY+heroi.altura <= 136 ) {
            mapCollision(&heroi, &square2);
          } else if( heroi.posX >= 108 && heroi.posX <= 900 && heroi.posY+heroi.altura >= 100 && heroi.posY+heroi.altura <= 397 ) {
            mapCollision(&heroi, &square3);
          } else if( heroi.posX >= 900 && heroi.posX <= 1010 && heroi.posY+heroi.altura >= 100 && heroi.posY+heroi.altura <= 136 ) {
            mapCollision(&heroi, &square4);
          } else {
            mapCollision(&heroi, &square5);
          }

          for( int i = 0; i < 10; i++ ) {
            if( bobOmb[i].alive ) {
              enemyMove(&bobOmb[i]); // movimentacao dos bob-ombs
            }
          }

          if( heroi.indoCima || heroi.indoDireita || heroi.indoBaixo || heroi.indoEsquerda ) {
            movimentacao(&heroi); // movimentação do herói
          } else {
            heroi.frame = 1;
          }

          if( heroi.estaAtacando.fireball || heroi.estaAtacando.element ) {
            atacar(allegro->mouse.x, allegro->mouse.y, interface);
          }
          if( heroi.tempoAtacar > -1 )
            heroi.tempoAtacar -= 0.1;
          break;

        case ALLEGRO_EVENT_KEY_DOWN:
          if ( event.keyboard.keycode == ALLEGRO_KEY_RIGHT || event.keyboard.keycode == ALLEGRO_KEY_D ) {
            heroi.indoDireita = true;
          }
          else if ( event.keyboard.keycode == ALLEGRO_KEY_LEFT || event.keyboard.keycode == ALLEGRO_KEY_A ) {
            heroi.indoEsquerda = true;
          }
          else if ( event.keyboard.keycode == ALLEGRO_KEY_DOWN || event.keyboard.keycode == ALLEGRO_KEY_S ) {
            heroi.indoBaixo = true;
          }
          else if ( event.keyboard.keycode == ALLEGRO_KEY_UP || event.keyboard.keycode == ALLEGRO_KEY_W ) {
            heroi.indoCima = true;
          }
          else if ( event.keyboard.keycode == ALLEGRO_KEY_LSHIFT ) {
            heroi.vel += 0.7;
          } else if( event.keyboard.keycode == ALLEGRO_KEY_E ) {
            if( heroCrystalDistance < 50 ) {
              takeElement(interface, &crystal);
              talkAboutElement = true;
            }
            if( heroi.posX >= 430 && heroi.posX <= 658 && heroi.posY+heroi.altura >= 45 && heroi.posY+heroi.altura <= 70) {
              gameStatus->going = LOBBY;
              gameStatus->coming = WATER;
              done = true;
            }
          }
          break;

        case ALLEGRO_EVENT_KEY_UP:
          if ( event.keyboard.keycode == ALLEGRO_KEY_RIGHT || event.keyboard.keycode == ALLEGRO_KEY_D ) {
            heroi.indoDireita = false;
          }
          if ( event.keyboard.keycode == ALLEGRO_KEY_LEFT || event.keyboard.keycode == ALLEGRO_KEY_A ) {
            heroi.indoEsquerda = false;
          }
          if ( event.keyboard.keycode == ALLEGRO_KEY_DOWN || event.keyboard.keycode == ALLEGRO_KEY_S ) {
            heroi.indoBaixo = false;
          }
          if ( event.keyboard.keycode == ALLEGRO_KEY_UP || event.keyboard.keycode == ALLEGRO_KEY_W ) {
            heroi.indoCima = false;
          } 
          if ( event.keyboard.keycode == ALLEGRO_KEY_LSHIFT ) {
            heroi.vel -= 0.7;
          }
          break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
          if( event.mouse.button == 1 ) {
            heroi.estaAtacando.fireball = true;
          } else if( event.mouse.button == 2 ) {
            heroi.estaAtacando.element = true;
          }
          break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
          if( event.mouse.button == 1 ) {
            heroi.estaAtacando.fireball = false;
          } else if( event.mouse.button == 2 ) {
            heroi.estaAtacando.element = false;
          }
          break;
        
        default: 
          break;
      }
    }

    if( draw ) {
      draw = false;
      al_clear_to_color(al_map_rgb(0 ,0 ,0 ));
      al_draw_bitmap(agua, 0, 0, 0);

      al_draw_bitmap_region(heroi.sprite, heroi.largura * (int)heroi.frame, heroi.frameAtualY, heroi.largura, heroi.altura, heroi.posX, heroi.posY, 0); 

      heroCrystalDistance = sqrt( pow(heroi.posX+heroi.largura / 2 - crystal.posX, 2) + pow(heroi.posY+heroi.altura / 2 - crystal.posY, 2) );

      if( heroi.posX >= 430 && heroi.posX <= 658 && heroi.posY+heroi.altura >= 45 && heroi.posY+heroi.altura <= 70 ) {
        al_draw_bitmap(interface->interactBtnImg, heroi.posX+heroi.largura/2.5, heroi.posY+heroi.altura+10, 0);
      } else if( heroCrystalDistance < 50 ) {
        al_draw_bitmap(interface->interactBtnImg, heroi.posX+heroi.largura/2.5, heroi.posY-20, 0);
      }

      for( int i = 0; i < 10; i++ ) {
        if( bobOmb[i].exploding ) 
          enemyExplosion(&bobOmb[i]);
        if( bobOmb[i].alive ) {
          al_draw_bitmap_region(bobOmb[i].sprite, bobOmb[i].largura * (int)bobOmb[i].frame, bobOmb[i].frameAtualY, bobOmb[i].largura, bobOmb[i].altura, bobOmb[i].posX, bobOmb[i].posY, 0); 
          if(characterCollision(&bobOmb[i], &heroi)) {
            bobOmb[i].exploding = true;
            heroi.lifes--;
          }
        }
      }

      for(int i = 0; i < 5; i++) {
        if( heroi.tiros[i].ativo && (heroi.tiros[i].posX > JANELA_LARGURA || heroi.tiros[i].posX < 0 || heroi.tiros[i].posY > JANELA_ALTURA || heroi.tiros[i].posY < 0) ) {
          heroi.tiros[i].ativo = false;
          al_destroy_bitmap(heroi.tiros[i].image);
        }

        if( heroi.tiros[i].ativo ) {
          heroi.tiros[i].posX += 6 * cos(heroi.tiros[i].angulo);
          heroi.tiros[i].posY += 6 * sin(heroi.tiros[i].angulo);
          al_draw_bitmap(heroi.tiros[i].image, heroi.tiros[i].posX, heroi.tiros[i].posY, 0);
          for( int j = 0; j < 10; j++ ) {
            if( bobOmb[j].alive && !bobOmb[j].exploding )
              enemyHit(&heroi.tiros[i], &bobOmb[j]);
          }
        }
      }
      
      showInterface(interface);

      if( talkAboutElement ) {
        talkAboutElement = false;
        dialogBox(allegro, "Hidróxido de amônio, Ufaa!!", &heroi);
      }

      al_flip_display();
    }
  } while(!done);

  al_destroy_bitmap(agua);  
  al_destroy_bitmap(heroi.sprite);  
  al_destroy_bitmap(heroi.face);  
  for(int i = 0; i < 5; i++) {
    if( !heroi.tiros[i].ativo )
      break;
    al_destroy_bitmap(heroi.tiros[i].image);
    heroi.tiros[i].ativo = false;
  }
} 
