OUTFILE = beagle_gotchi
# NOTE: please leave your paths as comments, since we might not have the same ones
OUTDIR = $(HOME)/cmpt433/public/myApps
#OUTDIR = $(HOME)/github/cmpt433/public/bin# Gabe S


CROSS_COMPILE = arm-linux-gnueabihf-

CC_C = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror -Wshadow -Wextra

CFILES = main.c pet/*.c utils/*.c menu/*.c games/*.c hardware/*.c ledMatrix/*.c
LIBS = -pthread
LFLAGS = -L$(HOME)/cmpt433/public/asound_lib_BBB
#LFLAGS = -L$(HOME)/github/cmpt433/public/asound_lib_BBG#Gabe S

PROJECT_NAME = beagle-gotchi
SERVER_DIR = webserver
WAVES_FILES = waves/*
DEPLOY_PATH= $(OUTDIR)/$(PROJECT_NAME)-copy

all: beagle_gotchi wav node #test

beagle_gotchi:
	cd $(OUTDIR) && mkdir -p beagle-gotchi-states && chmod 777 ./beagle-gotchi-states
	$(CC_C) $(CFLAGS) $(LIBS) $(CFILES) -o $(OUTDIR)/$(OUTFILE) $(LFLAGS) -lasound

wav:
	mkdir -p $(OUTDIR)/beagle-gotchi-waves/ 
	cp -R $(WAVES_FILES) $(OUTDIR)/beagle-gotchi-waves/ 

node:
	mkdir -p $(DEPLOY_PATH)
	cp -R $(SERVER_DIR)/* $(DEPLOY_PATH)
	cd $(DEPLOY_PATH) && npm install

test:
	@make --directory=tests

clean:
	rm -f $(OUTDIR)/$(OUTFILE)
	@make --directory=tests clean
