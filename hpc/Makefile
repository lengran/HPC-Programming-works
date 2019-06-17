CC = mpicc
CFLAGS = -I.
DEPS = myhead.h
OBJ = main.o common.o matrmul.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
