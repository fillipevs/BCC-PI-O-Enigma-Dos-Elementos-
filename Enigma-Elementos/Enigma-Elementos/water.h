#include "funcoes.h"

void water(Allegro* allegro, GameStatus* gameStatus, Interface* interface, Barreira* barreira) {
  bool draw = false;
  bool done = false;
  bool pause = false;
  bool talkAboutElement = false;
  float heroCrystalDistance = 0.0f;
  float heroBobOmbDistance = 0.0f;


  int enemyAmount = barreira->mercurio ? 14 : 0;
  Personagem bobOmb[14];
  if( barreira->mercurio )
    createEnemies(bobOmb, enemyAmount, START, gameStatus);

  MapSquare square1 = {430, 658, 0, 80};
  MapSquare square2 = {72, 790, 36, 136};
  MapSquare square3 = {108, 950, 70, 397};
  MapSquare square4 = {870, 1010, 70, 136};
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
          if( heroi.posX >= 430 && heroi.posX <= 658 && heroi.posY+heroi.altura >= 40 && heroi.posY+heroi.altura <= 70) {
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

          for( int i = 0; i < enemyAmount; i++ ) {
            if( heroi.alive && bobOmb[i].alive ) {
              enemyMove(&bobOmb[i]); // movimentacao dos bob-ombs
            }
          }

          if( heroi.alive && (heroi.indoCima || heroi.indoDireita || heroi.indoBaixo || heroi.indoEsquerda) ) {
            movimentacao(&heroi); // movimentação do herói
          } else if(heroi.alive) {
            heroi.frame = 1;
          }

          if( heroi.alive && (heroi.estaAtacando.fireball || heroi.estaAtacando.element) ) {
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
            heroi.vel = 2.0;
          } else if( event.keyboard.keycode == ALLEGRO_KEY_E ) {
            if( heroi.alive && heroCrystalDistance < 50 ) {
              takeElement(interface, &crystal);
              talkAboutElement = true;
            }
            if( heroi.alive && heroi.posX >= 430 && heroi.posX <= 658 && heroi.posY+heroi.altura >= 40 && heroi.posY+heroi.altura <= 70) {
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
            heroi.vel = 1.3;
          }
          if( event.keyboard.keycode == ALLEGRO_KEY_ESCAPE ) {
            pause = true;
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

      if( heroi.posX >= 430 && heroi.posX <= 658 && heroi.posY+heroi.altura >= 40 && heroi.posY+heroi.altura <= 70 ) {
        al_draw_bitmap(interface->interactBtnImg, heroi.posX+heroi.largura/2.5, heroi.posY+heroi.altura+10, 0);
      } else if( heroCrystalDistance < 50 ) {
        al_draw_bitmap(interface->interactBtnImg, heroi.posX+heroi.largura/2.5, heroi.posY-20, 0);
      }

      if( heroi.lifes == 0 ) {
        morrendo(&heroi, &done, gameStatus); 
      }

      for( int i = 0; i < enemyAmount; i++ ) {
        if( bobOmb[i].exploding ) 
          enemyExplosion(&bobOmb[i]);
        if( bobOmb[i].alive ) {
          al_draw_bitmap_region(bobOmb[i].sprite, bobOmb[i].largura * (int)bobOmb[i].frame, bobOmb[i].frameAtualY, bobOmb[i].largura, bobOmb[i].altura, bobOmb[i].posX, bobOmb[i].posY, 0); 
          heroBobOmbDistance = sqrt( pow( (heroi.posX+heroi.largura/2) - (bobOmb[i].posX+bobOmb[i].largura/2), 2) + pow( (heroi.posY+heroi.altura/2) - (bobOmb[i].posY+bobOmb[i].altura/2), 2) );
          if(heroBobOmbDistance < 30 && !bobOmb[i].exploding) {
            bobOmb[i].exploding = true;
            heroi.lifes--;
          }
        }
      }

      for(int i = 0; i < 5; i++) {
        if( heroi.tiros[i].isExploding ) {
          shotExploding(&heroi.tiros[i]);
        }

        if( heroi.tiros[i].ativo ) {
          al_draw_bitmap_region(heroi.tiros[i].image, heroi.tiros[i].largura * (int)heroi.tiros[i].frame, 0, heroi.tiros[i].largura, heroi.tiros[i].altura, heroi.tiros[i].posX, heroi.tiros[i].posY, 0);

          if( !heroi.tiros[i].isExploding ) {
            heroi.tiros[i].posX += 6 * cos(heroi.tiros[i].angulo);
            heroi.tiros[i].posY += 6 * sin(heroi.tiros[i].angulo);
          }
          
          if( heroi.tiros[i].posX+heroi.tiros[i].largura/2 >= 430 && heroi.tiros[i].posX+heroi.tiros[i].largura/2 <= 658 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 >= 0 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 <= 70) {
            shotCollision(&heroi.tiros[i], &square1);
          } else if( heroi.tiros[i].posX+heroi.tiros[i].largura/2 >= 72 && heroi.tiros[i].posX+heroi.tiros[i].largura/2 <= 760 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 >= 36 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 <= 136 ) {
            shotCollision(&heroi.tiros[i], &square2);
          } else if( heroi.tiros[i].posX+heroi.tiros[i].largura/2 >= 108 && heroi.tiros[i].posX+heroi.tiros[i].largura/2 <= 950 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 >= 70 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 <= 397 ) {
            shotCollision(&heroi.tiros[i], &square3);
          } else if( heroi.tiros[i].posX+heroi.tiros[i].largura/2 >= 900 && heroi.tiros[i].posX+heroi.tiros[i].largura/2 <= 1010 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 >= 70 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 <= 136 ) {
            shotCollision(&heroi.tiros[i], &square4);
          } else {
            shotCollision(&heroi.tiros[i], &square5);
          }

          for( int j = 0; j < enemyAmount; j++ ) {
            if( bobOmb[j].alive && !bobOmb[j].exploding )
              enemyHit(&heroi.tiros[i], &bobOmb[j]);
          }
        }
      }
      
      showInterface(interface);

      if( talkAboutElement ) {
        talkAboutElement = false;

        if( barreira->mercurio )
         dialogBox(allegro, "Hidróxido de amônio (NH4OH)", &heroi);
        dialogBox(allegro, "O Hidróxido de Amônio (NH4OH) é uma substância obtida naturalmente a partir da reação entre Amônia Anidra (NH3) e Água, sob pressão e temperatura controladas.", &heroi);
        dialogBox(allegro, "Vou preparar a poção com esse reagente!!", &heroi);
      }

      if( pause ) {
        pause = false;
        pauseGame(allegro, gameStatus);
        if( gameStatus->going == MENU )
          done = true;
      }

      al_flip_display();
    }
  } while(!done);

  al_destroy_bitmap(agua);  
  al_destroy_bitmap(heroi.sprite);  
  al_destroy_bitmap(heroi.face);  
  destroyEnemies(bobOmb, enemyAmount);
  destroyShots(heroi.tiros);  
} 
