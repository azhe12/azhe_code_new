OBJ=cycleShift findNotExisitNumber bianWeiCi prime hash
CPPFLAGS:=-I../baseLib/include -L../baseLib/lib -lbaseLib -g
CFLAGS:=-I../baseLib/include -L../baseLib/lib -lbaseLib -g
.PHONY: all clean

bianWeiCi:bianWeiCi.cpp
	g++ -o bianWeiCi bianWeiCi.cpp $(CPPFLAGS)
cycleShift:cycleShift.cpp
	g++  -o cycleShift cycleShift.cpp $(CPPFLAGS)

prime:prime.c
	gcc -o prime prime.c -lm $(CFLAGS)

findNotExisitNumber:findNotExisitNumber.c
	gcc -o findNotExisitNumber findNotExisitNumber.c $(CFLAGS)

hash:hash.c
	gcc -o hash hash.c $(CFLAGS)
clean:
	rm -rf $(OBJ) *.o
