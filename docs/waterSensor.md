# Adafruit Water sensor
https://www.adafruit.com/product/4965

# Setup
- make a circuit connecting the water sensor (pin marked with S) to ain6, while also connecting the water sensor to ground and 3.3V of power, using a 10k ohm resistor (resistor between ground & sensor). gpio kinda has infinite resistance (except not really), so we don't need to worry about it.
- (S) pin -> p9_35 (AIN6)
- (+) pin -> p9_32
- (-) pin -> p9_1 (or any other ground) (resistor probably not neccesary, but it works!) 

# Notes
- this water sensor is really bad, we would probably want a better one
- the following datasheet https://curtocircuito.com.br/datasheet/sensor/nivel_de_agua_analogico.pdf describes a sensor that appears to be identical in design
- looks like the pcb might have a 1k resistor attached to it, so we might not need to attach our own.