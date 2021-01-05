#include "UARTStateExchange.h"


void UARTStateSender::sendCmd(Msg* msg) {
    uart->write(msg->msgBuffer,msg->size);
}

UARTStateSender::UARTStateSender(PinName tx, PinName rx) : 
    uart(new mbed::BufferedSerial(tx, rx)){
    uart->set_baud(9600);
    uart->set_format(
        /* bits */ 8,
        /* parity */ mbed::BufferedSerial::None,
        /* stop bit */ 1
    );
}

UARTStateSender::~UARTStateSender(){
    delete uart;
}