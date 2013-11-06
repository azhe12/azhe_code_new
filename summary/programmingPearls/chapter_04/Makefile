OBJ=blackWhiteBall
CPPFLAGS:=-I../baseLib/include -L../baseLib/lib -lbaseLib -g
CFLAGS:=-I../baseLib/include -L../baseLib/lib -lbaseLib -g
.PHONY: all clean

blackWhiteBall:blackWhiteBall.c
	gcc -o blackWhiteBall blackWhiteBall.c $(CFLAGS)
clean:
	rm -rf $(OBJ) *.o
