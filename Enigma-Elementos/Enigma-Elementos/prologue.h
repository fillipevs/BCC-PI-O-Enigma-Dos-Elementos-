#include "funcoes.h"

void earlGoToHero(int counter, bool *alreadyTalked);
void earlAndHeroGoToKing(int counter, bool *alreadyTalked);

GAME_STATUS prologue(Allegro* allegro) {
  GAME_STATUS gameStatus = PROLOGUE;
  bool draw = false;
  bool done = false;
  bool alreadyTalked = true;

  ALLEGRO_BITMAP* home = al_load_bitmap("./assets/mapa/home.bmp");
  ALLEGRO_BITMAP* lobby = al_load_bitmap("./assets/mapa/lobby.bmp");
  heroi.sprite = al_load_bitmap("./assets/heroi/andando.png");
  heroi.face = al_load_bitmap("./assets/heroi/face.png");
  earl.sprite = al_load_bitmap("./assets/npc/earl.png");
  earl.face = al_load_bitmap("./assets/npc/earl-face.png");
  king.sprite = al_load_bitmap("./assets/npc/king.png");
  king.face = al_load_bitmap("./assets/npc/king-face.png");

  int counter = 0;

  do {
    while(!al_is_event_queue_empty(allegro->eventQueue)) {
      ALLEGRO_EVENT event; 
      al_wait_for_event(allegro->eventQueue, &event);

      switch(event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE: 
          done = true;
          gameStatus = EXIT;
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

        case ALLEGRO_EVENT_KEY_DOWN:
          break;

        case ALLEGRO_EVENT_KEY_UP:
          break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
          break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
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
        gameStatus = LOBBY;
      }

      // Earl talking to Hero
      if( !alreadyTalked && counter <= 631 ) {
        alreadyTalked = true;
        dialogBox(allegro, "Senhor Alex, o Rei deseja vê-lo imediatamente. Há assuntos de extrema importância a serem discutidos.", &earl);
        dialogBox(allegro, "O Rei deseja me ver? O que está acontecendo, Conde?", &heroi);
        dialogBox(allegro, "Na noite passada, Sua Majestade recebeu notícias perturbadoras. A Princesa desapareceu misteriosamente de seus aposentos. O Rei acredita que você pode ser a chave para desvendar esse enigma.", &earl);
        dialogBox(allegro, "Desapareceu? Como isso pode ter acontecido? Estou à disposição do Rei, é claro. Onde ele deseja que eu me encontre com ele?", &heroi);
        dialogBox(allegro, "Sua Majestade o aguarda no Salão do Trono. Ele acredita que você pode lançar luz sobre esse mistério. Por favor, siga-me.", &earl);
        dialogBox(allegro, "O Rei confia em sua habilidade, Senhor Alex. Vamos, não há tempo a perder.", &earl);
        dialogBox(allegro, "Eu irei imediatamente.", &heroi);
      }  
      // King talking to Earl and Hero
      else if( !alreadyTalked && counter <= 2161 ) {
        dialogBox(allegro, "Conde, Alex, agradeço por terem vindo. Temos um assunto de extrema urgência para tratar.", &king);
        dialogBox(allegro, "Sua Majestade, aqui está o jovem Alex, conforme solicitado.", &earl);
        dialogBox(allegro, "Sua Majestade, estou à disposição para ajudar a resolver o desaparecimento da Princesa. É um mistério que precisamos resolver rapidamente.", &heroi);
        dialogBox(allegro, "Eu estou ciente disso, Alex. A Princesa é a minha filha, e seu sumiço é um golpe em meu coração. Conde, você acha que ele pode ser útil nesta investigação?", &king);
        dialogBox(allegro, "Sim, Sua Majestade, Alex é uma pessoa de confiança e habilidosa. Tenho certeza de que ele pode lançar luz sobre o que aconteceu.", &earl);
        dialogBox(allegro, "Sua Majestade, farei o meu melhor para encontrá-la. Por favor, me conte tudo o que você sabe sobre a noite do desaparecimento.", &heroi);
        dialogBox(allegro, "Conde, por favor, nos dê um momento de privacidade. Há assuntos que devo discutir com Alex a sós.", &king);
        dialogBox(allegro, "Claro, Sua Majestade.", &earl);
      }
      // King talking to Hero
      else if( !alreadyTalked && counter > 2161 && counter <= 2162 ) {
        dialogBox(allegro, "Alex, há coisas que não posso compartilhar com todos na corte. O que aconteceu é mais grave do que todos imaginam.", &king);
        dialogBox(allegro, "Sua Majestade, estou pronto para ouvir. Por favor, me conte o que aconteceu com a Princesa.", &heroi);
        dialogBox(allegro, "A Princesa não foi simplesmente desaparecida, Alex. Ela foi sequestrada por forças sombrias que desejam poder sobre nossos reinos. Eles exigem os três Cristais Elementais em troca de sua vida.", &king);
        dialogBox(allegro, "Entendo, Sua Majestade. O que devo fazer para trazer a Princesa de volta?", &heroi);
        dialogBox(allegro, "Você deve partir imediatamente em busca dos três Cristais Elementais: Fogo, Água e Planta. Cada um deles é guardado por um Guardião. Eles são poderosos e protegem os cristais com todas as suas forças.", &king);
        dialogBox(allegro, "Eu farei isso, Sua Majestade. Onde posso encontrar os Guardiões e os cristais?", &heroi);
        dialogBox(allegro, "Os Guardiões estão nos Reinos do Fogo, da Água e da Planta.", &king);
        dialogBox(allegro, "O primeiro é o Guardião do Fogo, no vulcão a leste. O segundo é o Guardião da Água, nas profundezas do lago a oeste. E o terceiro é o Guardião da Planta, na floresta ao sul.", &king);
        dialogBox(allegro, "Você precisará enfrentá-los e trazer os cristais de volta a mim.", &king);
        dialogBox(allegro, "Entendi, Sua Majestade. Não vou falhar. Eu juro trazer a Princesa de volta e recuperar os cristais.", &heroi);
        dialogBox(allegro, "Muito bem, Alex. Este é um fardo pesado, mas tenho confiança em suas habilidades. Que a sorte esteja com você. Agora, vá e comece sua jornada imediatamente.", &king);
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
  al_destroy_bitmap(home);  
  al_destroy_bitmap(lobby);  

  return gameStatus;
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
