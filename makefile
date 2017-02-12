ALL: Compile
Compile:schadal1_p2.c
		gcc schadal1_p2.c -o submission
run:
	./submission input.txt output.txt
clear:
	rm -f submission
