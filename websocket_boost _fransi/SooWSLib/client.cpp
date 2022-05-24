#include "client.h"

Client::Client(): resolver(tcp::resolver{ioc})
{
    std::cout << "starting app client" << std::endl;
}

void Client::init(std::string host, std::string port)
{   
    //set connection configuration
    setConnectionConfig(host, port);
    
    setWSConfig();

}

void Client::make_connect()
{
    connect();
    handshake();
}


void Client::setWSConfig()
{

    resolver = tcp::resolver{ioc};
    ws = new websocket::stream<tcp::socket> {ioc};

    // Look up the domain name
    results = resolver.resolve(connection_config.host, 
                               connection_config.port);
                                 
}

void Client::setConnectionConfig(std::string host, std::string port)
{
    this->connection_config.host = host;
    this->connection_config.port = port;
    std::cout << "host, port to the server " 
              << this->connection_config.host
              << ", " 
              << this->connection_config.port 
              <<std::endl;
}

void Client::connect()
{
    std::cout << "trying to make connection to server" << std::endl;
    endpoint = net::connect(ws->next_layer(), results);
    std::cout << "connection stablished!!" << std::endl;

}

void Client::handshake()
{
    std::string host_modif;
    host_modif = connection_config.host + ':' 
               + std::to_string(endpoint.port());

        // Set a decorator to change the User-Agent of the handshake
        ws->set_option(websocket::stream_base::decorator(
            [](websocket::request_type& req)
            {
                req.set(http::field::user_agent,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-client-coro");
            }));

    std::cout << "trying to handshake to server" << std::endl;
    ws->handshake(host_modif, "/");
    std::cout << "handshake done!!" << std::endl;
    std::cout << "We are ready to send and receive messages..." << std::endl;
}


void Client::sendMessage(bool isBinary, std::string message_text)
{
    if (isBinary)
    {
        ws->binary(true);
        std::vector<char> vector_char_to_send = convertStringToVectorChar(message_text);

        ws->write(net::buffer(vector_char_to_send,2 ));
        std::cout << "message send: " << message_text <<std::endl;
    }
    else
    {
        ws->binary(false);
        std::cout << "No websocket send implementation. TODO" << std::endl;
        return;
    }
}

void Client::sendBinaryMessage(unsigned char message_bytes[])
{
    ws->binary(true);
    size_t number_bytes = strlen( (const char *)(message_bytes));
    ws->write(net::buffer( message_bytes, number_bytes ));
    std::cout << "message bytes send: " << message_bytes << " ,number bytes: " << number_bytes <<std::endl;
}

std::vector<char> Client::convertStringToVectorChar(std::string text)
{
    std::vector<char> result(text.begin(), text.end());
    return result;
}