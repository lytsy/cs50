CC ?= clang
CFLAGS ?= -fsanitize=integer -fsanitize=undefined -ggdb3 -O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wshadow
LDLIBS ?= -lcs50 -lm

.PHONY: all
all: notes synthesize

notes: ../../vendor/cs50.c ../../vendor/cs50.h helpers.c helpers.h notes.c wav.c wav.h
	$(CC) $(CFLAGS) -o notes ../../vendor/cs50.c helpers.c notes.c wav.c $(LDLIBS)

synthesize: ../../vendor/cs50.c ../../vendor/cs50.h synthesize.c wav.c wav.h helpers.c helpers.h
	$(CC) $(CFLAGS) -o synthesize ../../vendor/cs50.c helpers.c synthesize.c wav.c $(LDLIBS)

notes_gcc:
	gcc ../../vendor/cs50.c helpers.c helpers.h notes.c wav.c wav.h -o notes

synthesize_gcc:
	gcc ../../vendor/cs50.c synthesize.c wav.c wav.h helpers.c helpers.h -o synthesize

.PHONY: clean
clean:
	rm -f notes synthesize *.wav
