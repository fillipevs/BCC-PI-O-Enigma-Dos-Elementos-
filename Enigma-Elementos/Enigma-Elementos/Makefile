TARGET=a.out
CC=gcc
DEBUG=-g
OPT=-O0
WARN=-Wall
ALLEGRO=-lallegro -lallegro_main -lallegro_audio -lallegro_dialog -lallegro_ttf -lallegro_image -lallegro_color -lallegro_memfile -lallegro_acodec -lallegro_primitives -lallegro_font -lm
CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(ALLEGRO)
LD=gcc
OBJS= main.o
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(CCFLAGS)
	@rm *.o
	@./$(TARGET)

main.o: Main.c
	$(CC) -c $(CCFLAGS) Main.c -o main.o
