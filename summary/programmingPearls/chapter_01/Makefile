OBJ=mergeSort mergeSort_char
CFLAGS:=-I../baseLib/include -L../baseLib/lib -lbaseLib -g
CPPFLAGS:=-I../baseLib/include -L../baseLib/lib -lbaseLib -g
.PHONY: all clean

mergeSort_char:mergeSort_char.o
	g++ -o mergeSort_char mergeSort_char.cpp $(CPPFLAGS)
b:b.o
	g++ -o b b.cpp $(CPPFLAGS)
clean:
	rm -rf $(OBJ) *.o
