CC = mpicc
CFLAGS = -I.
DEPS = myhead.h
OBJ = bcastmain.o common.o bcast.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm *.o

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
