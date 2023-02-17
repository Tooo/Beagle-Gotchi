# adafruit rgb led Matrix

### setup
- use a guide from here https://opencoursehub.cs.sfu.ca/bfraser/grav-cms/cmpt433/links to figure out where to plug in the cables
- run `make test_ledMatrix`

### notes
- The ledMatrix test file is broken in how it exports things
- Sometimes (but only sometimes??) plugging the led display in stopped my bbg from booting. I guess just be careful...
- The display will flicker. In order to remove this (from context switches in linux), we need to drive the gpio from the PRU. (TODO: later)
