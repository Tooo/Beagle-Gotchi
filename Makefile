OUTFILE = beagle_gotchi
# NOTE: please leave your paths as comments, since we might not have the same ones
#OUTDIR = $(HOME)/github/cmpt433/public/bin# Gabe S
OUTDIR = $(HOME)/cmpt433/public/myApps

CROSS_COMPILE = arm-linux-gnueabihf-

CC_C = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror -Wshadow -Wextra

CFILES = main.c shutdown.c menu.c utils.c stateSaver.c pet.c terminal.c petScreen.c petInteract.c joystick.c digitDisplay.c
LIBS = -pthread

PROJECT_NAME=beagle-gotchi
SERVER_DIR=webserver
DEPLOY_PATH= $(OUTDIR)/$(PROJECT_NAME)-copy


all: beagle_gotchi test deploy node_install

TESTS = test_ledMatrix test_ledMatrix2 test_waterSensor test_stateSaver test_menu test_joystick test_digitDisplay
test: $(TESTS)

beagle_gotchi:
	cd $(OUTDIR) && mkdir -p beagle-gotchi-states
	$(CC_C) $(CFLAGS) $(LIBS) $(CFILES) -o $(OUTDIR)/$(OUTFILE)

TEST_LED_MATRIX_FILES = tests/test_ledMatrix.c
test_ledMatrix:
	$(CC_C) $(CFLAGS) -pthread -lpthread $(TEST_LED_MATRIX_FILES) -o $(OUTDIR)/test_ledMatrix

TEST_LED_MATRIX2_FILES = utils.c ledMatrix.c tests/test_ledMatrix2.c
test_ledMatrix2:
	$(CC_C) $(CFLAGS) -pthread -lpthread $(TEST_LED_MATRIX2_FILES) -o $(OUTDIR)/test_ledMatrix2

TEST_STATE_SAVER_FILES = stateSaver.c tests/test_stateSaver.c
test_stateSaver:
	$(CC_C) $(CFLAGS) -pthread -lpthread $(TEST_STATE_SAVER_FILES) -o $(OUTDIR)/test_stateSaver

TEST_WATER_SENSOR_FILES = utils.c a2d.c waterSensor.c tests/test_waterSensor.c
test_waterSensor:
	$(CC_C) $(CFLAGS) $(TEST_WATER_SENSOR_FILES) -o $(OUTDIR)/test_waterSensor

TEST_MENU_FILES = utils.c menu.c menuReader.c joystick.c tests/test_menu.c
test_menu:
	$(CC_C) $(CFLAGS) -pthread -lpthread $(TEST_MENU_FILES) -o $(OUTDIR)/test_menu

TEST_JOYSTICK_FILES = utils.c joystick.c tests/test_joystick.c
test_joystick:
	$(CC_C) $(CFLAGS) -pthread -lpthread $(TEST_JOYSTICK_FILES) -o $(OUTDIR)/test_joystick

TEST_DIGIT_DISPLAY_FILES = utils.c digitDisplay.c tests/test_digitDisplay.c
test_digitDisplay:
	$(CC_C) $(CFLAGS) -pthread -lpthread $(TEST_DIGIT_DISPLAY_FILES) -o $(OUTDIR)/test_digitDisplay

TEST_WEBSITE_FILES = utils.c tests/test_networking.c networking.c
test_website: node
	$(CC_C) $(CFLAGS) -pthread -lpthread $(TEST_WEBSITE_FILES) -o $(OUTDIR)/test_website

node:
	mkdir -p $(DEPLOY_PATH)
	cp -R $(SERVER_DIR)/* $(DEPLOY_PATH)
	cd $(DEPLOY_PATH) && npm install

clean:
	rm -f $(OUTDIR)/$(OUTFILE)
	cd $(OUTDIR) && rm -f $(TESTS)
