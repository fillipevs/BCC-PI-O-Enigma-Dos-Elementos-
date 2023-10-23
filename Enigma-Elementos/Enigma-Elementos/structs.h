typedef struct {
  ALLEGRO_DISPLAY* display;
  ALLEGRO_TIMER* timer;
  ALLEGRO_EVENT_QUEUE* eventQueue;
  ALLEGRO_FONT* font[2];
  ALLEGRO_MOUSE_STATE mouse;
  bool close;
} Allegro;

typedef struct {
  ALLEGRO_BITMAP* image;
  int x;
  int y;
  int width;
  int height;
  int frameX;
  bool isActive;
  float textX;
  float textY;
  char text[30];
} Button;

typedef struct {
  int posX;
  int posY;
  double angulo;
  int altura;
  int largura;
  ALLEGRO_BITMAP* image;
  bool ativo;
} Tiro;

typedef struct {
  float posX;
  float posY;
  float largura;
  float altura;
  float vel;
  bool indoCima;
  bool indoDireita;
  bool indoBaixo;
  bool indoEsquerda;
  float frame;
  int frameMax;
  int frameAtualY;
  ALLEGRO_BITMAP* sprite; 
  ALLEGRO_BITMAP* face;
  bool estaAtacando;
  float tempoAtacar;
  Tiro tiros[5];
} Personagem;

Personagem heroi = {
  635, // posição x
  170, // posição y
  47, // largura
  48.5, // altura
  1.3, // velocidade
  false, // cima
  false, // direita
  false, // baixo
  false, // esquerda
  0.f, // frame
  3, // frame máximo
  145, // frame atual y
  NULL, // sprite -> 141 / 3 = 47 -> largura; 194 / 4 = 48.5 -> altura;
  NULL, // face
  false, // está atacando
  0 // tempo para atacar
};

Personagem earl = {
  530, // posição x
  800, // posição y
  48.3, // largura
  48, // altura
  1.3, // velocidade
  false, // cima
  false, // direita
  false, // baixo
  false, // esquerda
  0.f, // frame 
  3, // frame máximo
  144, // frame atual y
  NULL, // sprite -> 37.5 -> largura; 41.42 -> altura;
  NULL, // face
  false, // está atacando
  0 // tempo para atacar
};

Personagem king = {
  970, // posição x
  80, // posição y
  48.3, // largura
  48, // altura
  1.3, // velocidade
  false, // cima
  false, // direita
  false, // baixo
  false, // esquerda
  1, // frame 
  3, // frame máximo
  48, // frame atual y
  NULL, // sprite -> 37.5 -> largura; 41.42 -> altura;
  NULL, // face
  false, // está atacando
  0 // tempo para atacar
};

Personagem bobOmb = {
  400, // posição x
  600, // posição y
  50, // largura
  38, // altura
  1, // velocidade
  false, // cima
  false, // direita
  false, // baixo
  false, // esquerda
  0.f, // frame -> 37.5 -> largura; 41.42 -> altura;
  4, // frame máximo
  0, // frame atual y
  NULL, // sprite
  NULL, // face
  false, // está atacando
  0 // tempo para atacar
};
