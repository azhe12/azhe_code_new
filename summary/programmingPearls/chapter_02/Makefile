OBJ=cycleShift
CFLAGS:=-I../baseLib/include -L../baseLib/lib -lbaseLib -g
.PHONY: all clean

cycleShift:cycleShift.o
	gcc  -o cycleShift cycleShift.c $(CFLAGS)

clean:
	rm -rf $(OBJ) *.o

#gcc -o cycleShift cycleShift.c -I../baseLib/include -L../baseLib/lib -lbaseLib
