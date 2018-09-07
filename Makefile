all: ex1.o psk31_dec.o

%.o: %.c
	cc -o $@ $<

clean:
	rm *.o
	rm *.txt || true
