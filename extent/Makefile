CC = mpicc
CFLAGS = -I.
DEPS = myhead.h
OBJ = main.o common.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

run: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
