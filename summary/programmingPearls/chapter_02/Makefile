OBJ=cycleShift findNotExisitNumber bianWeiCi prime
CPPFLAGS:=-I../baseLib/include -L../baseLib/lib -lbaseLib -g
CFLAGS:=-I../baseLib/include -L../baseLib/lib -lbaseLib -g
.PHONY: all clean

bianWeiCi:bianWeiCi.cpp
	g++ -o bianWeiCi bianWeiCi.cpp $(CPPFLAGS)
cycleShift:cycleShift.cpp
	g++  -o cycleShift cycleShift.cpp $(CPPFLAGS)

prime:prime.c
	gcc -o prime prime.c -lm $(CFLAGS)

findNotExisitNumber:findNotExisitNumber.o
	gcc -o findNotExisitNumber findNotExisitNumber.c $(CFLAGS)

clean:
	rm -rf $(OBJ) *.o
