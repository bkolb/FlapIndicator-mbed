#include "UARTStateExchange.h"

#include "Callback.h"
#include "SerialBase.h"


void UARTStateSender::sendCmd(Msg* msg) {
    uart->write(msg->msgBuffer,msg->pos);
}

UARTStateSender::UARTStateSender(PinName tx) : 
    uart(new mbed::BufferedSerial(tx, NC)){
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

UARTStateReceiver::UARTStateReceiver(PinName rx) : 
    uart(new mbed::UnbufferedSerial(NC, rx)) {
       
    uart->baud(9600);
    uart->format(
        /* bits */ 8,
        /* parity */ mbed::SerialBase::None,
        /* stop bit */ 1
    );

    currentMsg= mail_box.try_calloc();
    currentMsg->msgBuffer[0]=BeginOfCommand;
    currentMsg->msgBuffer[1]='V';
    currentMsg->msgBuffer[2]=EndOfCommand;
    mail_box.put(currentMsg);
    currentMsg = NULL;

    uart->attach(mbed::callback(this, &UARTStateReceiver::doReceive), mbed::SerialBase::RxIrq);
}

UARTStateReceiver::~UARTStateReceiver(){
    delete uart;
}

void UARTStateReceiver::doReceive(){
    char c;

    if (uart->read(&c, 1)) {
        if(c == BeginOfCommand) {
            if(currentMsg!=NULL) {
                // broken state. Discard the old command and start over
                mail_box.free(currentMsg);
                currentMsg=NULL;
            }

            currentMsg= mail_box.try_calloc();
            if(currentMsg== nullptr) {
                //allocation failed
                return;
            }
            currentMsg->pos=0;
        }
        if(currentMsg!=NULL) {
            if(currentMsg->pos==BUFFER_SIZE) {
                // we have some broken state. Discard the command and wait for the next beginn
                mail_box.free(currentMsg);
                currentMsg = NULL;
                return;
            } else {
                currentMsg->msgBuffer[currentMsg->pos++]=c;

                if(c == EndOfCommand) {
                    // enqueue the message. It will be freed after processing
                    mail_box.put(currentMsg);
                    currentMsg = NULL;
                }
            }
        }
        
    }
}

void UARTStateReceiver::run(){
    while(true) {
        Msg* msg = mail_box.try_get_for(Kernel::wait_for_u32_forever);
        if (msg != nullptr) {
            for (uint8_t i = 0; i < cmdParserSize; i++) {
                AbstractCmdParser* possibleParser = cmdsParsers[i];
                bool processed = possibleParser->parseAndHandleMsg(msg);
                if(processed){
                    break;
                }
            }
            mail_box.free(msg);
        }
    }
}