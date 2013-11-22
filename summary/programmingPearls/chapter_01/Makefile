OBJ=sort random
CFLAGS:=-I../baseLib/include -L../baseLib/lib -lbaseLib -g
CPPFLAGS:=-I../baseLib/include -L../baseLib/lib -lbaseLib -g
.PHONY: all clean

sort:sort.c
	gcc -o sort sort.c $(CFLAGS)

random:random.c
	gcc -o random random.c $(CFLAGS)
clean:
	rm -rf $(OBJ) *.o
