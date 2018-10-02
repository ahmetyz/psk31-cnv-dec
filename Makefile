P=psk31_dec
OBJECTS=
CFLAGS=-g -Wall -O3
LDLIBS=
CC=gcc

$(P): $(OBJECTS)

test: psk31_dec
	printf "03210010111311022130\n"  | ./psk31_dec.o # 0 errors
	printf "03200010111311022130\n"  | ./psk31_dec.o # 1 errors
	printf "03200010101311022130\n"  | ./psk31_dec.o # 2 errors non-adjacent
	printf "03201010101311022130\n"  | ./psk31_dec.o # 2 errors adjacent

clean:
	rm $(P)
	rm -rf $(P).dSYM
	rm *.txt || true
