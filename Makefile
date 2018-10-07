P=psk31_dec
OBJECTS=
CFLAGS=-g -Wall -O3 -DDEBUG_PRINT
LDLIBS=
CC=gcc

$(P): $(OBJECTS)

test: psk31_dec
	@# 0 errors
	@printf "03210010111311022130\n" | ./psk31_dec | grep -q "01011100101000100000"
	@# 1 errors
	@printf "03200010111311022130\n" | ./psk31_dec | grep -q "01011100101000100000"
	@# 2 errors non-adjacent
	@printf "03200010101311022130\n" | ./psk31_dec | grep -q "01011100101000100000"
	@# 2 errors adjacent
	@printf "03201010101311022130\n" | ./psk31_dec | grep -q "01011100101000100000"
	@# multiple errors
	@printf "03311010131310023120\n" | ./psk31_dec | grep -q "01011100101000100000"

clean:
	rm $(P)
	rm -rf $(P).dSYM
	rm *.txt || true
