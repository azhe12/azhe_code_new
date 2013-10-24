OBJ=cycleShift findNotExisitNumber bianWeiCi
CFLAGS:=-I../baseLib/include -L../baseLib/lib -lbaseLib -g
.PHONY: all clean

bianWeiCi:bianWeiCi.cpp
	g++ -o bianWeiCi bianWeiCi.cpp $(CPPFLAGS)
cycleShift:cycleShift.o
	gcc  -o cycleShift cycleShift.c $(CFLAGS)

findNotExisitNumber:findNotExisitNumber.o
	gcc -o findNotExisitNumber findNotExisitNumber.c $(CFLAGS)

clean:
	rm -rf $(OBJ) *.o
