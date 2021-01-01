#include "UARTStateExchange.h"



void UARTStateExchange::sendString(Msg msg) {
    uart->write(msg.msgBuffer,msg.size);
}

UARTStateExchange::UARTStateExchange(PinName tx, PinName rx) : 
    uart(new mbed::BufferedSerial(tx, rx))
{}

UARTStateExchange::~UARTStateExchange(){
    delete uart;
}