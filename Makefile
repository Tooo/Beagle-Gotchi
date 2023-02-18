OUTFILE = beagle_gotchi
# NOTE: please leave your paths as comments, since we might not have the same ones
#OUTDIR = $(HOME)/github/cmpt433/public/bin# Gabe S
OUTDIR = $(HOME)/cmpt433/public/myApps

CROSS_COMPILE = arm-linux-gnueabihf-
CC_C = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror -Wshadow -Wextra
CFILES = main.c shutdown.c
LIBS = -pthread

all: beagle_gotchi test_ledMatrix ledMatrixTest2

beagle_gotchi:
	$(CC_C) $(CFLAGS) $(LIBS) $(CFILES) -o $(OUTDIR)/$(OUTFILE)

test_ledMatrix:
	$(CC_C) $(CFLAGS) -pthread -lpthread tests/test_ledMatrix.c -o $(OUTDIR)/test_ledMatrix

ledMatrixTest2:
	$(CC_C) $(CFLAGS) -pthread -lpthread utils.c ledMatrix.c tests/ledMatrixTest2.c -o $(OUTDIR)/ledMatrixTest2

clean:
	rm $(OUTDIR)/$(OUTFILE)

