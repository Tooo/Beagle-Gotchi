OUTFILE = beagle_gotchi
OUTDIR = $(HOME)/cmpt433/public/myApps

CROSS_COMPILE = arm-linux-gnueabihf-
CC_C = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror -Wshadow -pthread
CFILES = main.c shutdown.c

all: beagle_gotchi 

beagle_gotchi:
	$(CC_C) $(CFLAGS) $(CFILES) -o $(OUTDIR)/$(OUTFILE)

clean:
	rm $(OUTDIR)/$(OUTFILE)

