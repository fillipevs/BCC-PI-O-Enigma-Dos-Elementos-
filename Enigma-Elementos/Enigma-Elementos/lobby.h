#include "funcoes.h"

void lobby(Allegro* allegro, GameStatus* gameStatus, Interface* interface, Barreira* barreira) {
  bool draw = false;
  bool done = false;
  bool pause = false;
  bool heroNearBarreira = false;
  bool talkWithBarreira = false;
  bool talkWithKing = false;
  float heroKingDistance = 0.0f;

  switch (gameStatus->coming)
  {
  case WATER:
    heroi.posX = 450;
    heroi.posY = 660;
    heroi.frameAtualY = 145.5;
    break;
  case FIRE:
    heroi.posX = 950;
    heroi.posY = 580;
    heroi.frameAtualY = 48.5;
    break;
  case GRASS:
    heroi.posX = 20;
    heroi.posY = 475;
    heroi.frameAtualY = 97;
    break;
  default:
    heroi.posX = 896;
    heroi.posY = 105;
    heroi.frameAtualY = 97;
    break;
  }

  MapSquare square1 = {120, 975, 70, 170};
  MapSquare square2 = {440, 520, 70, 380};
  MapSquare square3 = {20, 1000, 325, 718};

  MapSquare chumbo = {31, 131, 50, 150};
  MapSquare prataMercurio = {35, 125, 40, 130};
  MapSquare verificar = {31, 131, 50, 150};

  ALLEGRO_BITMAP* lobby = al_load_bitmap("./assets/mapa/lobby.bmp");
  heroi.sprite = al_load_bitmap("./assets/heroi/andando.png");
  king.sprite = al_load_bitmap("./assets/npc/king.png");
  princess.sprite = al_load_bitmap("./assets/npc/princess.png");
  heroi.face = al_load_bitmap("./assets/heroi/face.png");
  king.face = al_load_bitmap("./assets/npc/king-face.png");

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
          characterCollision(&king, &heroi);
          characterCollision(&princess, &heroi);

        // colisão do herói com o mapa
          if( heroi.posX >= 440 && heroi.posX <= 520 && heroi.posY+heroi.altura <= 325 && heroi.posY+heroi.altura >= 170) {
            mapCollision(&heroi, &square2);
          } else if( heroi.posY+heroi.altura >= 190 ) {
            mapCollision(&heroi, &square3);
          } else {
            mapCollision(&heroi, &square1);
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
          } else if( event.keyboard.keycode == ALLEGRO_KEY_E ) { // Interagindo
            if( heroi.posX <= 22 && heroi.posY+heroi.altura >= 490 && heroi.posY+heroi.altura <= 548 ) {
              gameStatus->going = GRASS;
              gameStatus->coming = LOBBY;
              done = true;
            } else if( heroi.posX >= 950 && heroi.posY+heroi.altura >= 583 && heroi.posY+heroi.altura <= 641 && !barreira->chumbo && !barreira->mercurio && !barreira->prata ) {
              gameStatus->going = FIRE;
              gameStatus->coming = LOBBY;
              done = true;
            } else if( heroi.posX >= 395 && heroi.posX <= 490 && heroi.posY+heroi.altura >= 716 && !barreira->chumbo ) {
              gameStatus->going = WATER;
              gameStatus->coming = LOBBY;
              done = true;
            } else if( heroNearBarreira ) {
              talkWithBarreira = true;
            } else if( heroKingDistance < 55 ) {
              talkWithKing = true;
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
      al_draw_bitmap(lobby, 0, 0, 0);

      if( barreira->verificar ) {
        al_draw_ellipse(80, 113, 50, 40, al_map_rgb(255,255,51), 15);
      }
      if( barreira->chumbo ) {
        al_draw_ellipse(80, 113, 55, 45, al_map_rgb(192,192,192), 5);
      } 
      if( barreira->mercurio ) {
        al_draw_ellipse(80, 113, 45, 35, al_map_rgb(70,130,180), 5);
      }
      if( barreira->prata ) {
        al_draw_ellipse(80, 113, 50, 40, al_map_rgb(79,79,79), 5);
      }

      if( barreira->chumbo ) {
        heroNearBarreira = (heroi.posX <= chumbo.x1 && heroi.posY >= chumbo.y0 && heroi.posY <= chumbo.y1 );
      } else if( barreira->mercurio || barreira->prata ) {
        heroNearBarreira = (heroi.posX <= prataMercurio.x1 && heroi.posY >= prataMercurio.y0 && heroi.posY <= prataMercurio.y1 );
      } else if( barreira->verificar ) {
        heroNearBarreira = (heroi.posX <= verificar.x1 && heroi.posY >= verificar.y0 && heroi.posY <= verificar.y1 );
      }

      al_draw_bitmap_region(heroi.sprite, heroi.largura * (int)heroi.frame, heroi.frameAtualY, heroi.largura, heroi.altura, heroi.posX, heroi.posY, 0); 
      al_draw_bitmap_region(king.sprite, king.largura * (int)king.frame, king.frameAtualY, king.largura, king.altura, king.posX, king.posY, 0); 
      al_draw_bitmap_region(princess.sprite, princess.largura * (int)princess.frame, princess.frameAtualY, princess.largura, princess.altura, princess.posX, princess.posY, 0); 

      heroKingDistance = sqrt( pow((heroi.posX+heroi.largura/2) - (king.posX+king.largura/2), 2) + pow((heroi.posY+heroi.altura/2) - (king.posY+king.altura/2), 2) );

      if( 
        (heroi.posX <= 22 && heroi.posY+heroi.altura >= 490 && heroi.posY+heroi.altura <= 548) ||
        (heroi.posX >= 950 && heroi.posY+heroi.altura >= 583 && heroi.posY+heroi.altura <= 641 && !barreira->chumbo && !barreira->mercurio && !barreira->prata ) ||
        (heroi.posX >= 395 && heroi.posX <= 490 && heroi.posY+heroi.altura >= 716 && !barreira->chumbo ) || 
        (heroNearBarreira) || 
        (heroKingDistance < 55)
       ) {
        al_draw_bitmap(interface->interactBtnImg, heroi.posX+heroi.largura/2.5, heroi.posY-20, 0);
      }

      if( heroi.lifes == 0 ) {
        morrendo(&heroi, &done, gameStatus); 
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
          
          if( heroi.tiros[i].posX+heroi.tiros[i].largura/2 >= 440 && heroi.tiros[i].posX+heroi.tiros[i].largura/2 <= 520 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 <= 325 && heroi.tiros[i].posY+heroi.tiros[i].altura/2 >= 170) {
            shotCollision(&heroi.tiros[i], &square2);
          } else if( heroi.tiros[i].posY+heroi.tiros[i].altura/2 >= 190 ) {
            shotCollision(&heroi.tiros[i], &square3);
          } else {
            shotCollision(&heroi.tiros[i], &square1);
          }
        }

        if( barreira->chumbo && barreiraHit(&heroi.tiros[i], &chumbo)) {
          barreira->chumbo = !(interface->attack2SlotType == ACIDO_CLORIDRICO);
        } else if( (barreira->mercurio || barreira->prata) && barreiraHit(&heroi.tiros[i], &prataMercurio) ) {
          barreira->mercurio = !(interface->attack2SlotType == HIDROXIDO_AMONIO);
          barreira->prata = barreira->mercurio;
        } else if( !barreira->chumbo && !barreira->mercurio && !barreira->prata && barreira->verificar && barreiraHit(&heroi.tiros[i], &verificar)) {
          barreira->verificar = !(interface->attack2SlotType == VERIFICATION);
        }
      }
      
      showInterface(interface);

      if( talkWithBarreira ) {
        talkWithBarreira = false;
        if( barreira->chumbo ) {
          dialogBox(allegro, "Essa barreira... é de Chumbo. Impenetrável e resistente. Precisarei encontrar ácido clorídrico para desfazê-la.", &heroi);
          dialogBox(allegro, "Se não me engano esse elemento fica no reino da planta, do lado esquerdo. Só preciso tomar cuidado com os inimigos que andam por lá!", &heroi);
        } else if( barreira->prata || barreira->mercurio ) {
          dialogBox(allegro, "Essa duas barreiras... é de Prata e Mercúrio... A solução química para desfazer ambas as barreiras é hidróxido de amônio.", &heroi);
          dialogBox(allegro, "Certeza que consigo um pouco no reino da água. Só descer o caminho de pedra e eu chego lá.", &heroi);
        } else if( barreira->verificar ) {
          dialogBox(allegro, "As barreiras cairam!! Mas como usamos elementos químicos, essa área pode estar contaminada, precisamos verificar!", &heroi);
          dialogBox(allegro, "Para fazer a verificação preciso pegar Ácido nítrico, Cromato de potássio e Amônia no reino de fogo, do lado direito.", &heroi);
          dialogBox(allegro, "Se essa cor amarelada sumir, significa que a princesa pode sair com segurança.", &heroi);
        }
      }

      if( talkWithKing ) {
        talkWithKing = false;
        dialogBox(allegro, "Por favor, tira minha filha daquela barreira.", &king);
      }

      if( !barreira->chumbo && !barreira->mercurio && !barreira->prata && !barreira->verificar ) {
        done = true;
        gameStatus->coming = LOBBY;
        gameStatus->going = END;
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

  al_destroy_bitmap(lobby);  
  al_destroy_bitmap(heroi.sprite);  
  al_destroy_bitmap(king.sprite);  
  al_destroy_bitmap(heroi.face);  
  al_destroy_bitmap(king.face);  
  al_destroy_bitmap(princess.sprite);  
  destroyShots(heroi.tiros);
} 
