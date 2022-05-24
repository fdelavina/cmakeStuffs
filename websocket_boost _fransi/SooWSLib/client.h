#ifndef ClientWS        
#define ClientWS

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>

#include <iostream>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

struct ConnectionConfig
{
    std::string host;
    std::string port;

};

struct WSData
{
    //WSData();
    ConnectionConfig connection_config;

    net::io_context ioc;
    tcp::resolver resolver;
    websocket::stream<tcp::socket>* ws;
    boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp> results;
    boost::asio::ip::tcp::endpoint endpoint;
    
};

class Client
{
public:
    Client();

    void makeHandShake();
    void sendMessage(bool isBinary, std::string message_text);
    void sendBinaryMessage(unsigned char mybyte[]);
    void init(std::string host, std::string port);
    void make_connect();
private:
    void setWSConfig();
    void setConnectionConfig(std::string host, std::string port);

    void connect();
    void handshake();

    std::vector<char> convertStringToVectorChar(std::string message_text);

    //attributes
    //WSData m_ws_data;

    ConnectionConfig connection_config;

    net::io_context ioc;
    tcp::resolver resolver;
    websocket::stream<tcp::socket>* ws;
    boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp> results;
    boost::asio::ip::tcp::endpoint endpoint;
    
};


#endif