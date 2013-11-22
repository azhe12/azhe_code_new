OBJ=mergeSort mergeSort_char mergeSort_int
CFLAGS:=-I../baseLib/include -L../baseLib/lib -lbaseLib -g
CPPFLAGS:=-I../baseLib/include -L../baseLib/lib -lbaseLib -g
.PHONY: all clean

megeSort:mergeSort.c
	gcc -o mergeSort mergeSort.c $(CFLAGS)

random:random.c
	gcc -o random random.c $(CFLAGS)
clean:
	rm -rf $(OBJ) *.o
