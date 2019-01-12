all:
	gcc -o bitwise -Wall bitwise.c

clean:
	rm -f bitwise out

check: all
	@./bitwise > out
	@diff -u out gold-master && echo "OK!"
