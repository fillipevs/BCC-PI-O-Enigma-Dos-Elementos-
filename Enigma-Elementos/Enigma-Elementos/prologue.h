#include "funcoes.h"

void earlGoToHero(int counter, bool *alreadyTalked);
void earlAndHeroGoToKing(int counter, bool *alreadyTalked);

void prologue(Allegro* allegro, GameStatus* gameStatus) {
  bool draw = false;
  bool done = false;
  bool pause = false;
  bool alreadyTalked = true;

  heroi.lifes = 5;
  heroi.vel = 1.3;
  heroi.posX = 635;
  heroi.posY = 170;
  heroi.frameAtualY = heroi.altura * 3;
  king.posX = 970;
  king.posY = 70;
  king.frameAtualY = king.altura * 1;
  princess.posX = 55;
  princess.posY = 70;
  princess.frameAtualY = king.altura * 2;
  earl.posX = 530;
  earl.posY = 800;

  ALLEGRO_BITMAP* home = al_load_bitmap("./assets/mapa/home.bmp");
  ALLEGRO_BITMAP* lobby = al_load_bitmap("./assets/mapa/lobby.bmp");
  heroi.sprite = al_load_bitmap("./assets/heroi/andando.png");
  earl.sprite = al_load_bitmap("./assets/npc/earl.png");
  king.sprite = al_load_bitmap("./assets/npc/king.png");
  princess.sprite = al_load_bitmap("./assets/npc/princess.png");
  heroi.face = al_load_bitmap("./assets/heroi/face.png");
  earl.face = al_load_bitmap("./assets/npc/earl-face.png");
  king.face = al_load_bitmap("./assets/npc/king-face.png");

  int counter = 0;

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
          if( heroi.indoCima || heroi.indoDireita || heroi.indoBaixo || heroi.indoEsquerda ) {
            movimentacao(&heroi); // movimentação do player por enquanto
          } else {
            heroi.frame = 1;
          }

          if( earl.indoCima || earl.indoDireita || earl.indoBaixo || earl.indoEsquerda ) {
            movimentacao(&earl); // movimentação do player por enquanto
          } else {
            earl.frame = 1;
          }
          break;
        case ALLEGRO_EVENT_KEY_UP:
          if( event.keyboard.keycode == ALLEGRO_KEY_ESCAPE ) {
            pause = true;
          }
          break;
        
        default: 
          break;
      }
    }

    if( draw ) {
      draw = false;
      al_clear_to_color(al_map_rgb(0 ,0 ,0 ));
      if( counter <= 1250 )
        al_draw_bitmap(home, 0, 0, 0);
      else {
        al_draw_bitmap(lobby, 0, 0, 0);
        al_draw_ellipse(80, 113, 45, 35, al_map_rgb(70,130,180), 5);
        al_draw_ellipse(80, 113, 50, 40, al_map_rgb(79,79,79), 5);
        al_draw_ellipse(80, 113, 55, 45, al_map_rgb(192,192,192), 5);
        al_draw_bitmap_region(princess.sprite, princess.largura * (int)princess.frame, princess.frameAtualY, princess.largura, princess.altura, princess.posX, princess.posY, 0); 
        al_draw_bitmap_region(king.sprite, king.largura * (int)king.frame, king.frameAtualY, king.largura, king.altura, king.posX, king.posY, 0); 
      }

      al_draw_bitmap_region(heroi.sprite, heroi.largura * (int)heroi.frame, heroi.frameAtualY, heroi.largura, heroi.altura, heroi.posX, heroi.posY, 0); 
      if( counter < 2162 )
        al_draw_bitmap_region(earl.sprite, earl.largura * (int)earl.frame, earl.frameAtualY, earl.largura, earl.altura, earl.posX, earl.posY, 0); 

      if( counter <= 631 )
        earlGoToHero(counter, &alreadyTalked);
      else if( counter <= 2161 )
        earlAndHeroGoToKing(counter, &alreadyTalked); 
      else {
        done = true; 
        gameStatus->going = LOBBY;
        gameStatus->coming = PROLOGUE;
      }

      // Earl talking to Hero
      if( !alreadyTalked && counter <= 631 ) {
        alreadyTalked = true;
        dialogBox(allegro, "Senhor Alex, urgência! A Princesa foi aprisionada e o Rei precisa da sua ajuda!", &earl);
        dialogBox(allegro, "O quê? Como isso aconteceu, vamos rapido onde ela está?", &heroi);
        dialogBox(allegro, "No antigo cemitério, vamos o mais rápido possível.", &earl);
        dialogBox(allegro, "Vamos!! Pode contar comigo.", &heroi);
      }  
      // King talking to Earl and Hero
      else if( !alreadyTalked && counter <= 2161 ) {
        dialogBox(allegro, "Sua Majestade, aqui está o jovem Alex, conforme solicitado.", &earl);
        dialogBox(allegro, "Que bom que você chegou! Eu e minha filha estavámos visitando o túmulo da minha falecida esposa e a Princesa foi capturada por uma armadilha mágica.", &king);
        dialogBox(allegro, "Precisamos tirar a princesa daquela armadilha urgente!!", &king);
      } 
      // King talking to Hero
      else if( !alreadyTalked && counter > 2161 && counter <= 2162 ) {
        dialogBox(allegro, "Sua Majestade, antes de tudo, preciso examinar essa armadilha para determinar como poderemos quebrá-la.", &heroi);
        dialogBox(allegro, "Por favor, faça o que for necessário, Alex. Minha filha precisa ser liberta dessa prisão.", &king);
      }

      if( pause ) {
        pause = false;
        pauseGame(allegro, gameStatus);
        if( gameStatus->going == LOBBY )
          done = true;
      }

      al_flip_display();
      counter++;
    }
    
  } while(!done);

  al_destroy_bitmap(heroi.sprite);  
  al_destroy_bitmap(earl.sprite);  
  al_destroy_bitmap(king.sprite);  
  al_destroy_bitmap(heroi.face);  
  al_destroy_bitmap(earl.face);  
  al_destroy_bitmap(king.face);  
  al_destroy_bitmap(princess.sprite);  
  al_destroy_bitmap(home);  
  al_destroy_bitmap(lobby);  
}

void earlGoToHero(int counter, bool *alreadyTalked) {
  // earl moviment
  if( counter <= 250 ) {
    earl.indoCima = true;
  } 
  else if( counter <= 300 ) {
    earl.indoCima = false;
    earl.indoEsquerda = true;
  }
  else if( counter <= 535 ) {
    earl.indoEsquerda = false;
    earl.indoCima = true;
  }
  else if( counter <= 630 ) {
    earl.indoCima = false;
    earl.indoDireita = true;
  } 
  else if( counter <= 631 ) {
    earl.indoDireita = false;
    heroi.frameAtualY = 48.5;
    *alreadyTalked = false;
    earl.frame = 1;
  }
}

void earlAndHeroGoToKing(int counter, bool *alreadyTalked) {
  // hero moviment
  if( counter <= 750 ) {
    heroi.indoEsquerda = true;
  } 
  else if( counter <= 930 ) {
    heroi.indoEsquerda = false;
    heroi.indoBaixo = true;
  } 
  else if( counter <= 980) {
    heroi.indoBaixo = false;
    heroi.indoDireita = true;
  } 
  else if( counter <= 1260) {
    heroi.indoDireita = false;
    heroi.indoBaixo = true;
  } 
  else if( counter <= 1560 ) {
    heroi.indoBaixo = false;
    heroi.indoCima = true;
  }
  else if( counter <= 1620 ) {
    heroi.indoCima = false;
    heroi.indoEsquerda= true;
  }
  else if( counter <= 1830 ) {
    heroi.indoEsquerda= false;
    heroi.indoCima = true;
  }
  else if( counter <= 2160 ) {
    heroi.indoCima = false;
    heroi.indoDireita= true;
  } else {
    heroi.frame = 1;
    heroi.indoDireita= false;
    *alreadyTalked = false;
  }

  // earl moviment
  if( counter <= 700 ) {
    earl.indoEsquerda = true;
  } else if( counter <= 900 ) {
    earl.indoEsquerda = false;
    earl.indoBaixo = true;
  } 
  else if( counter <= 930) {
    earl.indoBaixo = false;
    earl.indoDireita = true;
  } 
  else if( counter <= 1200) {
    earl.indoDireita = false;
    earl.indoBaixo = true;
  } 
  else if( counter <= 1500 ) {
    earl.indoBaixo = false;
    earl.indoCima = true;
  } 
  else if( counter <= 1560 ) {
    earl.indoCima = false;
    earl.indoEsquerda = true;
  } 
  else if( counter <= 1820 ) {
    earl.indoEsquerda = false;
    earl.indoCima = true;
  } 
  else if( counter <= 2160 ) {
    earl.indoCima = false;
    earl.indoDireita = true;
  } else {
    earl.indoDireita = false;
    earl.frame = 1;
  }

}
