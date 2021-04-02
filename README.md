# Flap Indicator





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