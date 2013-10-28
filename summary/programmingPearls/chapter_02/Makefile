OBJ=cycleShift findNotExisitNumber bianWeiCi
CPPFLAGS:=-I../baseLib/include -L../baseLib/lib -lbaseLib -g
.PHONY: all clean

bianWeiCi:bianWeiCi.cpp
	g++ -o bianWeiCi bianWeiCi.cpp $(CPPFLAGS)
cycleShift:cycleShift.cpp
	g++  -o cycleShift cycleShift.cpp $(CPPFLAGS)

findNotExisitNumber:findNotExisitNumber.o
	gcc -o findNotExisitNumber findNotExisitNumber.c $(CPPFLAGS)

clean:
	rm -rf $(OBJ) *.o
