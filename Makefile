all: bitwise

bitwise: bitwise.c
	gcc -o $@ -Wall $^

clean:
	rm -f bitwise out

check: all
	@./bitwise > out
	@diff -u out gold-master && echo "OK!"
