CFLAGS = -Wall -Wextra -g -std=c99 -lportmidi -lporttime -lpthread
LDFLAGS = -lportmidi -lporttime -lpthread
EXEC=boucle

.PHONY: all
	all: ${EXEC}

boucle: boucle.o midi.o ihm.o
	gcc ${LDFLAGS} -o $@ $^

%.o: %.c
	gcc ${CFLAGS} -o $@ -c $<

.PHONY: clean
clean:
	rm *.o ${EXEC}

.PHONY: indent
indent:
	indent -linux *.c *.h

