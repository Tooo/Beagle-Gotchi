# Beagle Gotchi Tests
These tests are made to ensure the hardware and utils work properly

## Installation
Make in the tests folder to make all the tests
```bash
make
```

## Tests
| Test | Description |
| :--- | :---------- |
| test_audio | Test audio and plays different pet sounds |
| test_buzzer | Test buzzer and play different notes |
| test_digitDisplay | Test digit display and display 0-99 |
| test_joystick | Test joystick and display current direction |
| test_led | Test LEDs and lights each LED |
| test_ledAnimation | Test LED Animation on LED Matrix |
| test_ledMatrix | Test LED Matrix (3rd party test) |
| test_ledMatrix2 | Test LED Matrix and display animation|
| test_menu | Test menu and display options in terminal |
| test_networking | Test website and display pet infomation |
| test_petScreen | Test pet screen and display pet life cycle |
| test_stateSaver | Test state saver and load/unload modules |
| test_waterSensor | Test water sensor and displaying submerged or not |
| test_zenLed | Test Zen Cape LEDs and Lights up each colour |

### Other Tests
| Test | Description |
| :--- | :---------- |
| OpenCVTest | Testing for OpenCV (doesn't work) |