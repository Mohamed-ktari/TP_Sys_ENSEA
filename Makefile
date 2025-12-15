CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC = src/main.c src/ex1.c src/ex2.c src/ex3.c src/ex4.c src/ex5.c src/ex6.c src/ex7.c src/ex8.c


OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))


TARGET = bin/enseash


$(shell mkdir -p obj bin)


all: $(TARGET)


$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)


obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f obj/*.o bin/enseash
