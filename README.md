# Beagle-Gotchi
Our system is a prototype for “Beagle-Gotchi”, a custom version of a Tamagotchi with various additional sensors. We aim to solve all the same software problems a released Tamagotchi would also run into, put together as a hardware prototype. Our plan was to make the project as complicated as possible, so we’d run into sufficiently challenging architecture problems.

## The Narrative
A Beagle-Gotchi is a cheap, waterproof game device. Players press the power button to turn it on, interact with it via its 5 buttons & water sensor, and see a response via its 4 leds (one of which has multiple colours), the 32x16 pixel 7 color display, and its buzzer. In addition, players can connect to their Beagle-Gotchi from a web-browser to gain secret information about their pet! The goal of the game is to keep this virtual pet happy and well fed. The player can do this by petting, feeding, and playing games with their pet

## Pre-requisite
### LED Matrix
- https://www.adafruit.com/product/420
- Refer to [LedMatrix.md](docs/ledMatrix.md)

### Water Sensor
- https://www.adafruit.com/product/4965
- Refer to [waterSensor.md](docs/waterSensor.md)

### Audio
- Install libasound and add to asound_lib_BBB folder

## Installation
1. Make excutable file on the host
```bash
(host)$ make
```

2. Run excutable on the BeagleBone
```bash
(bbg)$ cd /mnt/remote/myApps/
(bbg)$ ./beagle_gotchi
```

3. Run web server
```bash
(bbg)$ cd /mnt/remote/myApps/beagle-gotchi-copy
(bbg)$ node server.js
```

## Features
- Display menu and pet animations on LED Matrix
- Feed, Pet, Play (and Slap) the pet
- Play multiple minigames like high low and rock paper scissors 
- Save and reload pet after playing
- Locate secret stats in the web server
