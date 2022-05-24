// Sends a WebSocket message and prints the response
#include "thread"
#include "client.h"
int main(int argc, char** argv)
{
     Client my_client_ws;
     my_client_ws.init("192.168.30.51", "9002");

     my_client_ws.make_connect();

    unsigned char byte_to_send[] = {0xa1,0xa2,0xff,0xb1,0xdd};
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        my_client_ws.sendBinaryMessage(byte_to_send);
    }
     
}