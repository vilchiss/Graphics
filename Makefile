BIBLIOTECAS = -lGL -lGLU -lglut -lm

CC = cc

CODIGO = rubik.cpp
EJECUTABLE = rubik

$(EJECUTABLE): $(CODIGO)
	$(CC) $(CODIGO) $(BIBLIOTECAS) -o $(EJECUTABLE)


.PHONY: clean run

run:
	make
	./$(EJECUTABLE)

clean:
	-rm $(EJECUTABLE)

