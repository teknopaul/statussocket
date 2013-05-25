statusemake: ulisten.c usend.c
	gcc -Wall -Os -o ulisten ulisten.c
	gcc -Wall -Os -o usend usend.c


.PHONY: clean install uninstall

clean:
	rm ulisten usend

install:
	cp ulisten usend /usr/bin

uninstall:
	rm -f /usr/bin/ulisten /usr/bin/usend
