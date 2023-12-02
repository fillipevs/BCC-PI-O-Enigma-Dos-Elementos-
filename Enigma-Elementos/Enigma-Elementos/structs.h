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
  float textX;
  float textY;
  char text[30];
} Button;

typedef struct {
  ALLEGRO_BITMAP* attack1Img;
  ALLEGRO_BITMAP* attack2Img;
  ALLEGRO_BITMAP* heart;
  ALLEGRO_BITMAP* interactBtnImg;
  ALLEGRO_BITMAP* mouseBtnLeftImg;
  ALLEGRO_BITMAP* mouseBtnRightImg;
  SlotType attack1SlotType;
  SlotType attack2SlotType;
} Interface;

typedef struct {
  GAME_STATUS_TYPE coming;
  GAME_STATUS_TYPE going;
} GameStatus;

typedef struct {
  int posX;
  int posY;
  SlotType name;
} Crystal;

typedef struct {
  bool chumbo;
  bool prata;
  bool mercurio;
  bool verificar;
} Barreira;

typedef struct {
  int x0;
  int x1;
  int y0;
  int y1;
} MapSquare;

typedef struct {
  bool fireball;
  bool element;
} AttackType;

typedef struct {
  int posX;
  int posY;
  double angulo;
  int altura;
  int largura;
  float vel;
  ALLEGRO_BITMAP* image;
  bool ativo;
  AttackType type;
  float frame;
  int frameMax;
  bool isExploding;
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
  AttackType estaAtacando;
  float tempoAtacar;
  bool alive;
  bool exploding;
  int lifes;
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
  {false, false}, // está atacando
  0, // tempo para atacar
  true, // está vivo
  false, // está explodindo
  5, // qtd de vidas
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
  {false, false}, // está atacando
  0, // tempo para atacar
  true, // está vivo
  false // está explodindo
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
  {false, false}, // está atacando
  0, // tempo para atacar
  true, // está vivo
  false // está explodindo
};

Personagem princess = {
  55, // posição x
  70, // posição y
  48.3, // largura
  48, // altura
  1.3, // velocidade
  false, // cima
  false, // direita
  false, // baixo
  false, // esquerda
  0, // frame 
  3, // frame máximo
  96, // frame atual y
  NULL, // sprite -> 37.5 -> largura; 41.42 -> altura;
  NULL, // face
  {false, false}, // está atacando
  0, // tempo para atacar
  true, // está vivo
  false // está explodindo
};
