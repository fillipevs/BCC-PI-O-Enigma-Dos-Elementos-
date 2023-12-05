#include "funcoes.h"

void grass(Allegro* allegro, GameStatus* gameStatus, Interface* interface, Barreira* barreira) {
  bool draw = false;
  bool done = false;
  bool pause = false;
  bool talkAboutElement = false;
  float heroCrystalDistance = 0.0f;
  float heroBobOmbDistance = 0.0f;


  int enemyAmount = barreira->chumbo ? 14 : 0;
  Personagem bobOmb[14];
  if( barreira->chumbo )
    createEnemies(bobOmb, enemyAmount, START, gameStatus);

  MapSquare square1 = {900, 1030, 288, 453};
  MapSquare square2 = {210, 1010, 100, 720};
  MapSquare square3 = {95, 300, 115, 330};
  MapSquare square4 = {95, 300, 390, 720};
  MapSquare square5 = {170, 300, 115, 720};

  Crystal crystal;
  crystal.name = ACIDO_CLORIDRICO;
  crystal.posX = 155;
  crystal.posY = 350;

  ALLEGRO_BITMAP* planta = al_load_bitmap("./assets/mapa/planta.bmp");
  heroi.sprite = al_load_bitmap("./assets/heroi/andando.png");
  heroi.face = al_load_bitmap("./assets/heroi/face.png");
  heroi.posX = 980;
  heroi.posY = 350;
  heroi.frameAtualY = 48.5;

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
          if( heroi.posX >= 920 && heroi.posY+heroi.altura >= 288 && heroi.posY+heroi.altura <= 453) {
            mapCollision(&heroi, &square1); 
          } else if( heroi.posX >= 220 && heroi.posX+heroi.largura <= 1010 && heroi.posY+heroi.altura >= 100 && heroi.posY+heroi.altura <= 720) {
            mapCollision(&heroi, &square2);
          } else if( heroi.posX >= 95 && heroi.posX+heroi.largura <= 300 && heroi.posY+heroi.altura >= 115 && heroi.posY+heroi.altura <= 330) {
            mapCollision(&heroi, &square3); 
          } else if( heroi.posX >= 95 && heroi.posX+heroi.largura <= 300 && heroi.posY+heroi.altura >= 390 && heroi.posY+heroi.altura <= 720) {
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
            if( heroi.alive && heroi.posX >= 970 && heroi.posY+heroi.altura >= 288 && heroi.posY+heroi.altura <= 453) {
              gameStatus->going = LOBBY;
              gameStatus->coming = GRASS;
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
      al_draw_bitmap(planta, 0, 0, 0);

      al_draw_bitmap_region(heroi.sprite, heroi.largura * (int)heroi.frame, heroi.frameAtualY, heroi.largura, heroi.altura, heroi.posX, heroi.posY, 0); 

      heroCrystalDistance = sqrt( pow(heroi.posX+heroi.largura / 2 - crystal.posX, 2) + pow(heroi.posY+heroi.altura / 2 - crystal.posY, 2) );

      if( 
        (heroi.posX >= 970 && heroi.posY+heroi.altura >= 288 && heroi.posY+heroi.altura <= 453) || 
        (heroCrystalDistance < 50)
       ) {
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

          if( heroi.tiros[i].posX+heroi.tiros[i].largura/2 >= 920 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 >= 288 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 <= 453) {
            shotCollision(&heroi.tiros[i], &square1); 
          } else if( heroi.tiros[i].posX+heroi.tiros[i].largura/2 >= 220 && heroi.tiros[i].posX+heroi.tiros[i].largura/2 <= 1010 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 >= 100 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 <= 720) {
            shotCollision(&heroi.tiros[i], &square2);
          } else if( heroi.tiros[i].posX+heroi.tiros[i].largura/2 >= 95 && heroi.tiros[i].posX+heroi.tiros[i].largura/2 <= 300 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 >= 115 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 <= 330) {
            shotCollision(&heroi.tiros[i], &square3); 
          } else if( heroi.tiros[i].posX+heroi.tiros[i].largura/2 >= 95 && heroi.tiros[i].posX+heroi.tiros[i].largura/2 <= 300 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 >= 390 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 <= 720) {
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

        dialogBox(allegro, "Ácido clorídrico (HCl)", &heroi);
        dialogBox(allegro, "O ácido clorídrico se forma naturalmente pela reação do cloreto de sódio com sulfatos ácidos nas águas dos oceanos ou na atmosfera.", &heroi);
        dialogBox(allegro, "Vou preparar uma poção com esse reagente para dissolver a barreira", &heroi);
        dialogBox(allegro, "Pronto!!, Acredito que jogando isso na barreira ela ira se quebrar", &heroi);
        if( barreira->chumbo )
          createEnemies(bobOmb, enemyAmount, TAKE_ELEMENT, gameStatus);
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

  al_destroy_bitmap(planta);  
  al_destroy_bitmap(heroi.sprite); 
  al_destroy_bitmap(heroi.face); 
  destroyEnemies(bobOmb, enemyAmount);
  destroyShots(heroi.tiros);
} 
