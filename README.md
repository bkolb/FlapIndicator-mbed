# Flap Indicator

![Build state](https://github.com/bkolb/FlapIndicator-mbed/actions/workflows/build.yml/badge.svg?event=push)



Template based on https://github.com/ladislas/mbed-cmake-template/
# Flap Indicator

## Software
We use http://mbed.org/. Due to flashing issues we use version 6.5.0. Basic setup is describes in [Template-Readme](Template-Readme.md)

To setup run
```
make config TARGET_BOARD=NUCLEO_L432KC BUILD_TYPE=Debug
```
then
```
make
```
to flash
```
make flashBack
make flashFront
```

### Calibration
run 
```
make flashADCPrint
```

The Serial Interface defaults to a 9600 baud standard serial connection (8 bits, 1 stop bit, no parity)
Connect with mbed Studio to read values from embedded terminal.
Alternatively:
`ls /dev/tty.usbmodem*` to find the device. Then `screen /dev/<devicename>`

## Hardware

We use the following Board: https://os.mbed.com/platforms/ST-Nucleo-L432KC/

Datasheet: https://www.st.com/resource/en/datasheet/stm32l432kc.pdf


### Back
#### Pins
* LED
  * D10 -> L-1
  * D9 -> L-2
  * D6 -> L-3
  * D5 -> L-4
  * D4 -> L-5
  * D3 -> L-L 
* A0 -> AD (+ GND & 3V3)
* A7 -> UART_TX
* A3 -> Button

### Front
#### Pins
* LED
  * D10 -> L-1
  * D9 -> L-2
  * D6 -> L-3
  * D5 -> L-4
  * D4 -> L-5
  * D3 -> L-L 
* D0 -> UART_RX
* D11 -> LX-Vario/SF
