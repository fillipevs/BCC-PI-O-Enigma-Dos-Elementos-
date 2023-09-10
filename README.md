# DOCs

## includes
- <allegro5/allegro.h> --> biblioteca padrão do Allegro
- <allegro5/allegro_font.h> --> biblioteca para adicionar fontes
- <allegro5/allegro_ttf.h> --> biblioteca para adicionar as nossas fontes
- <allegro5/allegro_image.h> --> biblioteca para adicionar nossas imagens
- <allegro5/keyboard.h> --> biblioteca para usar o teclado

## tipos
- `ALLEGRO_DISPLAY* janela;` --> para declarar a janela de exibição do seu jogo
- `ALLEGRO_FONT* fonte;` --> para declarar a fonte que você vai usar no seu jogo
- `ALLEGRO_TIMER* timer;` --> para declarar o FPS(frames per second) que seu jogo vai ter
- `ALLEGRO_BITMAP* imagem` --> para declarar uma imagem;
- `ALLEGRO_EVENT_QUEUE* fila_eventos` --> para declarar a fila de eventos do seu jogo
- `ALLEGRO_EVENT event;` --> para declarar os eventos que vão ocorrer no seu jogo

## funções
### instalação e inicialização
- `al_init();` --> para iniciar o Allegro
- `al_init_font_addon();` --> para iniciar o adicionador de fontes
- `al_init_ttf_addon();` --> para iniciar o adicionador das nossas fontes
- `al_init_image_addon();` --> para iniciar o adicionador das nossas imagens
- `al_install_keyboard();` --> para instalar o teclado no game
- `al_install_mouse();` --> para instalar o mouse no game

### geral
- janela = `al_create_display(1280,720);` --> cria a janela de exibição do seu jogo com as dimensões passadas
- `al_set_window_position(display, 200, 200);` --> define as coordenadas onde a tela do seu jogo vai aparecer
- `al_set_window_title(display, "Here Be Dragons!");` --> define o título da janela do seu jogo
- `al_load_font("./font.ttf", 25, 0);` --> carrega o arquivo da sua fonte e define o tamanho das fonte
- timer = `al_create_timer(1.0 / 30.0);`  --> define a quantidade de FPS que seu jogo vai rodar
- imagem = `al_load_bitmap("./bg.png");` --> carrega o arquivo da imagem que você vai usar
- fila_eventos = `al_create_event_queue();` --> cria a fila de eventos
- `al_register_event_source(fila_eventos, al_get_display_event_source(janela));` --> adicionamos o evento da janela de exibição dentro da nossa lista de eventos
- `al_register_event_source(fila_eventos, al_get_timer_event_source(timer));` --> adicionamos o evento do timer/FPS dentro da nossa lista de eventos
- `al_register_event_source(fila_eventos, al_get_keyboard_event_source());` --> adicionamos os eventos do teclado dentro da nossa lista de eventos
- `al_start_timer(timer);` --> inicia o timer/FPS do seu jogo para poder gerar os eventos do seu jogo
- `al_wait_for_event(fila_eventos, &event);` --> aguarda um evento acontecer na sua fila de eventos
- `al_clear_to_color(al_map_rgb(255,255,255));` --> pinta a tela com a cor passada a cada frame
- `al_draw_bitmap(imagem, 0, 0, 0);` -> desenha uma imagem na tela, passando suas coordenadas
- `al_draw_bitmap_region(imagem, img_regiao_x, img_regiao_y, largura, altura, x, y, 0);` --> recorta uma região da imagem e desenha essa região na tela, passando suas coordenadas
- `al_draw_text(fonte, al_map_rgb(0, 0, 0), x, y, 0, "SCORE: DRAGONS");` --> desenha um texto na tela passando sua fonte, cor, x, y e o texto a ser exibido
- `al_flip_display();` --> no final do seu while() para ficar atualizando a tela da frente e a de trás, dando a impressão do movimento na tela

## frees
- `al_destroy_bitmap(imagem);` --> para liberar o espaço de memória que foi alocado para guardar a sua imagem, necessário fazer para cada imagem
- `al_destroy_font(font);` --> para liberar o espaço de memória que foi alocado para guardar a sua fonte, necessário fazer para cada fonte
- `al_destroy_display(display);` --> para liberar o espaço de memória que foi alocado para guardar a sua tela de exibição
- `al_destroy_event_queue(event_queue);` --> para liberar o espaço de memória que foi alocado para guardar a sua fila de eventos

## outros
- `event.type == ALLEGRO_EVENT_DISPLAY_CLOSE` --> verifica se o X da janela foi clicado
- `event.keyboard.keycode == ALLEGRO_KEY_ALGUMA-TECLA` --> verifica se alguma tecla especifica do teclado foi clicada
