# Adafruit RGB LED Matrix
https://www.adafruit.com/product/420

### Setup
- use a guide from here https://opencoursehub.cs.sfu.ca/bfraser/grav-cms/cmpt433/links to figure out where to plug in the cables
- run `make test_ledMatrix2`

### Notes
- The ledMatrix test file is broken in how it exports things
- If the led matrix not attached to power, but attached to the bbg, it will stop the bbg from booting. **You must plug in the led matrix before booting the bbg** (I suspect this is some form of short circuiting. Not good!)
- The display will flicker. In order to remove this (from context switches in linux), we need to drive the gpio from the PRU. (TODO: later)
- NOTE: don't run `test_ledMatrix`, it sucks
- 
