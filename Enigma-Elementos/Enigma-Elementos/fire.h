#include "funcoes.h"

void fire(Allegro* allegro, GameStatus* gameStatus, Interface* interface, Barreira* barreira) {
  bool draw = false;
  bool done = false;
  bool talkAboutElement = false;
  float heroCrystalDistance = 0.0f;
  float heroBobOmbDistance = 0.0f;

  int enemyAmount = barreira->verificar ? 18 : 0;
  Personagem bobOmb[18];
  if( barreira->verificar )
    createEnemies(bobOmb, enemyAmount, START, gameStatus);

  MapSquare square1 = {-10, 190, 230, 670};
  MapSquare square2 = {139, 830, 230, 710};
  MapSquare square3 = {397, 730, 158, 245};

  Crystal crystal;
  crystal.name = VERIFICATION;
  crystal.posX = 767;
  crystal.posY = 192;

  ALLEGRO_BITMAP* fogo = al_load_bitmap("./assets/mapa/fogo.bmp");
  heroi.sprite = al_load_bitmap("./assets/heroi/andando.png");
  heroi.face = al_load_bitmap("./assets/heroi/face.png");
  heroi.posX = 0;
  heroi.posY = 550;
  heroi.frameAtualY = 97;

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
          if( heroi.posX >= -10 && heroi.posX+heroi.largura <= 190 && heroi.posY+heroi.altura >= 230 && heroi.posY+heroi.altura <= 670) {
            mapCollision(&heroi, &square1);
          } else if( heroi.posX >= 139 && heroi.posX+heroi.largura <= 830 && heroi.posY+heroi.altura >= 230 && heroi.posY+heroi.altura <= 710) { 
            mapCollision(&heroi, &square2);
          } else {
            mapCollision(&heroi, &square3);
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
            if( heroi.alive && heroCrystalDistance < 30 ) {
              takeElement(interface, &crystal);
              talkAboutElement = true;
            }
            if( heroi.alive && heroi.posX >= -10 && heroi.posX <= 5 && heroi.posY+heroi.altura >= 230 && heroi.posY+heroi.altura <= 670) {
              gameStatus->going = LOBBY;
              gameStatus->coming = FIRE;
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
      al_draw_bitmap(fogo, 0, 0, 0);

      al_draw_bitmap_region(heroi.sprite, heroi.largura * (int)heroi.frame, heroi.frameAtualY, heroi.largura, heroi.altura, heroi.posX, heroi.posY, 0); 

      heroCrystalDistance = sqrt( pow(heroi.posX+heroi.largura / 2 - crystal.posX, 2) + pow(heroi.posY+heroi.altura / 2 - crystal.posY, 2) );

      if( 
        (heroi.posX >= -10 && heroi.posX <= 5 && heroi.posY+heroi.altura >= 230 && heroi.posY+heroi.altura <= 670) ||
        (heroCrystalDistance < 30)
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

          if( heroi.tiros[i].posX+heroi.tiros[i].largura/2 >= 0 && heroi.tiros[i].posX+heroi.tiros[i].largura/2 <= 190 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 >= 230 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 <= 670) {
            shotCollision(&heroi.tiros[i], &square1);
          } else if( heroi.tiros[i].posX+heroi.tiros[i].largura/2 >= 139 && heroi.tiros[i].posX+heroi.tiros[i].largura/2 <= 830 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 >= 230 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 <= 710) { 
            shotCollision(&heroi.tiros[i], &square2);
          } else {
            shotCollision(&heroi.tiros[i], &square3);
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
        dialogBox(allegro, "Ácido nítrico, Cromato de potássio e Amônia. Os últimos que faltavam!!", &heroi);
        if( barreira->verificar )
          createEnemies(bobOmb, enemyAmount, TAKE_ELEMENT, gameStatus);
      }

      al_flip_display();
    }
  } while(!done);

  al_destroy_bitmap(fogo);  
  al_destroy_bitmap(heroi.sprite);
  al_destroy_bitmap(heroi.face);
  destroyEnemies(bobOmb, enemyAmount);
  destroyShots(heroi.tiros);
} 
