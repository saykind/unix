all:	a.out	b.out
	@echo "Run a.out (sender) and b.out (receiver)."
	@echo "Firstly give sender's pid to receiver. (From a to b)."

a.out:	a_talker.c
	gcc -Wall -g a_talker.c -o a.out

b.out:	b_talker.c
	gcc -Wall -g b_talker.c -o b.out

clean:
	rm *~
	rm a.out
	rm b.out
