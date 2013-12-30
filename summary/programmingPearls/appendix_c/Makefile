OBJ=measure
CFLAGS="-lm"
.PHONY:all clean
all:$(OBJ)

measure:measure.c
	gcc -o measure measure.c $(CFLAGS)
clean:
	rm -rf $(OBJ) *.o
