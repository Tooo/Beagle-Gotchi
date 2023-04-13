# NOTE: please leave your paths as comments, since we might not have the same ones
OUTDIR = $(HOME)/cmpt433/public/myApps/tests
#OUTDIR = $(HOME)/github/cmpt433/public/bin

CROSS_COMPILE = arm-linux-gnueabihf-

CC_C = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror -Wshadow -Wextra
LIBS = -pthread -lpthread

LFLAGS = -L$(HOME)/cmpt433/public/asound_lib_BBB
#LFLAGS = -L$(HOME)/github/cmpt433/public/asound_lib_BBG

PROJECT_NAME = beagle-gotchi
SERVER_DIR = ../webserver
WAVES_FILES = ../waves/*
DEPLOY_PATH = $(OUTDIR)/$(PROJECT_NAME)-copy

HARDWARE_PATH = ../hardware
LEDMATRIX_PATH = ../ledMatrix
MENU_PATH = ../menu
PET_PATH = ../pet
UTILS_PATH = ../utils

UTILS_FILE = $(UTILS_PATH)/utils.c

all: test test_folder states wav node

TESTS = test_ledMatrix test_ledMatrix2 test_ledAnimation test_waterSensor test_stateSaver test_menu 
TESTS += test_joystick test_digitDisplay test_petScreen test_led test_zenLed test_buzzer test_website test_audio
test: test_folder $(TESTS)

test_folder:
	mkdir -p $(OUTDIR)

node:
	mkdir -p $(DEPLOY_PATH)
	cp -R $(SERVER_DIR)/* $(DEPLOY_PATH)
	cd $(DEPLOY_PATH) && npm install

states:
	cd $(OUTDIR) && mkdir -p beagle-gotchi-states && chmod 777 ./beagle-gotchi-states

wav:
	mkdir -p $(OUTDIR)/beagle-gotchi-waves/ 
	cp -R $(WAVES_FILES) $(OUTDIR)/beagle-gotchi-waves/ 

TEST_LED_MATRIX_FILES = test_ledMatrix.c
test_ledMatrix:
	$(CC_C) $(CFLAGS) $(LIBS) $(TEST_LED_MATRIX_FILES) -o $(OUTDIR)/test_ledMatrix

TEST_LED_MATRIX2_FILES = $(UTILS_FILE) $(LEDMATRIX_PATH)/ledMatrix.c $(LEDMATRIX_PATH)/sprites.c test_ledMatrix2.c
test_ledMatrix2:
	$(CC_C) $(CFLAGS) $(LIBS) $(TEST_LED_MATRIX2_FILES) -o $(OUTDIR)/test_ledMatrix2

TEST_LED_ANIMATION_FILES = $(UTILS_FILE) $(LEDMATRIX_PATH)/ledMatrix.c $(LEDMATRIX_PATH)/sprites.c test_ledAnimation.c 
test_ledAnimation:
	$(CC_C) $(CFLAGS) $(LIBS) $(TEST_LED_ANIMATION_FILES) -o $(OUTDIR)/test_ledAnimation

TEST_STATE_SAVER_FILES = $(UTILS_PATH)/stateSaver.c test_stateSaver.c
test_stateSaver: states
	$(CC_C) $(CFLAGS) $(LIBS) $(TEST_STATE_SAVER_FILES) -o $(OUTDIR)/test_stateSaver

TEST_WATER_SENSOR_FILES = $(UTILS_FILE) $(HARDWARE_PATH)/a2d.c $(HARDWARE_PATH)/waterSensor.c test_waterSensor.c
test_waterSensor:
	$(CC_C) $(CFLAGS) $(LIBS) $(TEST_WATER_SENSOR_FILES) -o $(OUTDIR)/test_waterSensor

TEST_MENU_FILES = $(UTILS_FILE) $(MENU_PATH)/menu.c $(MENU_PATH)/menuReader.c $(HARDWARE_PATH)/joystick.c $(HARDWARE_PATH)/led.c $(HARDWARE_PATH)/buzzer.c $(LEDMATRIX_PATH)/ledMatrix.c $(LEDMATRIX_PATH)/sprites.c test_menu.c $(UTILS_PATH)/networking.c $(PET_PATH)/pet.c $(UTILS_PATH)/stateSaver.c $(UTILS_PATH)/terminal.c $(PET_PATH)/petInteract.c $(LEDMATRIX_PATH)/animations.c $(HARDWARE_PATH)/audio.c $(HARDWARE_PATH)/waterSensor.c $(HARDWARE_PATH)/a2d.c
test_menu:
	$(CC_C) $(CFLAGS) $(LIBS) $(TEST_MENU_FILES) -o $(OUTDIR)/test_menu $(LFLAGS) -lasound

TEST_JOYSTICK_FILES = $(UTILS_FILE) $(HARDWARE_PATH)/joystick.c test_joystick.c
test_joystick:
	$(CC_C) $(CFLAGS) $(LIBS) -lpthread $(TEST_JOYSTICK_FILES) -o $(OUTDIR)/test_joystick

TEST_DIGIT_DISPLAY_FILES = $(UTILS_FILE) $(HARDWARE_PATH)/digitDisplay.c test_digitDisplay.c
test_digitDisplay:
	$(CC_C) $(CFLAGS) $(LIBS) -lpthread $(TEST_DIGIT_DISPLAY_FILES) -o $(OUTDIR)/test_digitDisplay

TEST_WEBSITE_FILES = $(UTILS_FILE) test_networking.c $(UTILS_PATH)/networking.c $(PET_PATH)/pet.c $(UTILS_PATH)/stateSaver.c $(UTILS_PATH)/terminal.c $(PET_PATH)/petInteract.c $(LEDMATRIX_PATH)/ledMatrix.c $(LEDMATRIX_PATH)/animations.c $(LEDMATRIX_PATH)/sprites.c $(HARDWARE_PATH)/joystick.c $(HARDWARE_PATH)/audio.c $(HARDWARE_PATH)/waterSensor.c $(HARDWARE_PATH)/a2d.c $(HARDWARE_PATH)/buzzer.c
test_website: node
	$(CC_C) $(CFLAGS) $(LIBS) $(TEST_WEBSITE_FILES) -o $(OUTDIR)/test_website $(LFLAGS) -lasound

TEST_PET_SCREEN_FILES = $(UTILS_FILE) $(PET_PATH)/pet.c $(PET_PATH)/petScreen.c $(UTILS_PATH)/stateSaver.c $(UTILS_PATH)/terminal.c test_petScreen.c $(LEDMATRIX_PATH)/ledMatrix.c $(LEDMATRIX_PATH)/sprites.c $(HARDWARE_PATH)/joystick.c $(HARDWARE_PATH)/buzzer.c $(UTILS_PATH)/networking.c $(PET_PATH)/petInteract.c $(LEDMATRIX_PATH)/animations.c $(HARDWARE_PATH)/audio.c $(HARDWARE_PATH)/waterSensor.c $(HARDWARE_PATH)/a2d.c
test_petScreen:
	$(CC_C) $(CFLAGS) $(LIBS) $(TEST_PET_SCREEN_FILES) -o $(OUTDIR)/test_petScreen $(LFLAGS) -lasound

TEST_LED_FILES = $(UTILS_FILE) $(HARDWARE_PATH)/led.c test_led.c
test_led:
	$(CC_C) $(CFLAGS) $(LIBS) $(TEST_LED_FILES) -o $(OUTDIR)/test_led

TEST_ZEN_LED_FILES = $(UTILS_FILE) $(HARDWARE_PATH)/zenLed.c test_zenLed.c
test_zenLed:
	$(CC_C) $(CFLAGS) $(LIBS) $(TEST_ZEN_LED_FILES) -o $(OUTDIR)/test_zenLed

TEST_AUDIO_FILES = $(UTILS_FILE) $(HARDWARE_PATH)/audio.c test_audio.c
test_audio: wav
	$(CC_C) $(CFLAGS) $(LIBS) $(TEST_AUDIO_FILES) -o $(OUTDIR)/test_audio $(LFLAGS) -lasound

TEST_BUZZER_FILES = $(UTILS_FILE) $(HARDWARE_PATH)/buzzer.c test_buzzer.c
test_buzzer:
	$(CC_C) $(CFLAGS) $(LIBS) $(TEST_BUZZER_FILES) -o $(OUTDIR)/test_buzzer

clean:
	rm -f $(OUTDIR)/$(OUTFILE)
	cd $(OUTDIR) && rm -f $(TESTS)
