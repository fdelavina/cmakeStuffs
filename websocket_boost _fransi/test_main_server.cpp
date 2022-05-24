// Start ws server

#include "server.h"
#include <iostream>

void getBuffer(Server* my_server_ws)
{ 
     while(true)
     {
          std::this_thread::sleep_for(std::chrono::milliseconds(1000));
          beast::flat_buffer buffer = my_server_ws->getBufferReceived();

          std::cout<<"read from thread :" << beast::make_printable(buffer.data()) <<std::endl;     
     }
}

int main(int argc, char** argv)
{
     //Server my_server_ws("127.0.0.1", 1234);
     Server* my_server_ws = new Server{"127.0.0.1", 1235};
     //my_server_ws.startServer();

     std::thread t1(&Server::startServer, my_server_ws);

     std::thread t2(getBuffer, std::ref(my_server_ws));
     
     t1.join();
     t2.join();
}