CC=gcc
CFLAGS=-Wall -Wextra
LDFLAGS=
SOURCES=main.c


ccalc: $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^


clean:
	rm ccalc
