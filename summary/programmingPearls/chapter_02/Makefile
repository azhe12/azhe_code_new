OBJ=cycleShift findNotExisitNumber bianWeiCi
CPPFLAGS:=-I../baseLib/include -L../baseLib/lib -lbaseLib -g
.PHONY: all clean

bianWeiCi:bianWeiCi.cpp
	g++ -o bianWeiCi bianWeiCi.cpp $(CPPFLAGS)
cycleShift:cycleShift.o
	gcc  -o cycleShift cycleShift.c $(CPPFLAGS)

findNotExisitNumber:findNotExisitNumber.o
	gcc -o findNotExisitNumber findNotExisitNumber.c $(CPPFLAGS)

clean:
	rm -rf $(OBJ) *.o
