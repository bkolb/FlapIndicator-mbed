#include "UARTStateExchange.h"



void UARTStateExchange::sendString(Msg msg) {
    uart->write(msg.msgBuffer,msg.size);
    //printf(msg.msgBuffer);
 //   printf(" size: %u", msg.size);
}

UARTStateExchange::UARTStateExchange(PinName tx, PinName rx) : 
    uart(new mbed::BufferedSerial(tx, rx)){
    uart->set_baud(9600);
    uart->set_format(
        /* bits */ 8,
        /* parity */ mbed::BufferedSerial::None,
        /* stop bit */ 1
    );
}

UARTStateExchange::~UARTStateExchange(){
    delete uart;
}