OUTFILE = beagle_gotchi
# NOTE: please leave your paths as comments, since we might not have the same ones
#OUTDIR = $(HOME)/github/cmpt433/public/bin# Gabe S
OUTDIR = $(HOME)/cmpt433/public/myApps

CROSS_COMPILE = arm-linux-gnueabihf-

CC_C = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror -Wshadow -Wextra

CFILES = main.c shutdown.c menu.c buttons.c utils.c stateSaver.c pet.c terminal.c petScreen.c
LIBS = -pthread

all: beagle_gotchi test_ledMatrix test_ledMatrix2 test_waterSensor test_stateSaver

beagle_gotchi:
	cd $(OUTDIR) && mkdir -p beagle-gotchi-states
	$(CC_C) $(CFLAGS) $(LIBS) $(CFILES) -o $(OUTDIR)/$(OUTFILE)

test_ledMatrix:
	$(CC_C) $(CFLAGS) -pthread -lpthread tests/test_ledMatrix.c -o $(OUTDIR)/test_ledMatrix

test_ledMatrix2:
	$(CC_C) $(CFLAGS) -pthread -lpthread utils.c ledMatrix.c tests/test_ledMatrix2.c -o $(OUTDIR)/test_ledMatrix2

test_stateSaver:
	$(CC_C) $(CFLAGS) -pthread -lpthread stateSaver.c tests/test_stateSaver.c -o $(OUTDIR)/test_stateSaver

WATER_SENSOR_FILES = utils.c a2d.c waterSensor.c tests/test_waterSensor.c
test_waterSensor:
	$(CC_C) $(CFLAGS) $(WATER_SENSOR_FILES) -o $(OUTDIR)/test_waterSensor

clean:
	rm $(OUTDIR)/$(OUTFILE)

