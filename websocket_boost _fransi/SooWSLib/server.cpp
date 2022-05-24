#include "server.h"

Server::Server(std::string host, int port) 
                 
{
    std::cout << "starting app..." << std::endl;
    ioc = new net::io_context{1};
    address = net::ip::make_address(host);

    acceptor = new tcp::acceptor{*ioc, {address, static_cast<unsigned short>(port)}};

    socket = new tcp::socket{*ioc};

    std::cout << "tcp socket created" << std::endl;
}

void Server::init(std::string host, const std::string _port)
{
    // address = net::ip::make_address(host);
    // port = static_cast<unsigned short>(std::atoi(_port.c_str()));


    // acceptor = boost::asio::ip::tcp::acceptor{ioc, {address, port}};

    // socket = tcp::socket{ioc};
}

void Server::startServer()
{
    std::cout << "starting server" << std::endl;
    for(;;)
    {
        // This will receive the new connection
        tcp::socket socket{*ioc};

        std::cout << "waiting for new conection from client" << std::endl;
        // Block until we get a connection
        acceptor->accept(socket);
        std::cout << "get new connection from: " << socket.remote_endpoint().address().to_string() <<std::endl;

        // Launch the session, transferring ownership of the socket
        // std::thread(
        //     &Server::do_session,
        //     std::move(socket)).detach();
        do_session(socket);
    }
}

void Server::do_session(tcp::socket &socket)
{
    try
    {
        // Construct the stream by moving in the socket
        websocket::stream<tcp::socket> ws{std::move(socket)};

        // Set a decorator to change the Server of the handshake
        ws.set_option(websocket::stream_base::decorator(
            [](websocket::response_type& res)
            {
                res.set(http::field::server,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-server-sync");
            }));

        // Accept the websocket handshake
        ws.accept();
        std::cout<< "handshake accepted" <<std::endl;
        ws.binary(true);
        for(;;)
        {
            // This buffer will hold the incoming message
            beast::flat_buffer buffer;
            buffer.clear();
            // Read a message
            ws.read(buffer);
            m_buffer=buffer; //it a need to set first a local variable because other threads could read a wrong value
            std::cout<<beast::make_printable(m_buffer.data()) <<std::endl;

            // Echo the message back
            //ws.text(ws.got_text());
            //ws.write(buffer.data());
        }
    }
    catch(beast::system_error const& se)
    {
        // This indicates that the session was closed
        if(se.code() != websocket::error::closed)
            std::cerr << "session close: " << se.code().message() << std::endl;
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}


beast::flat_buffer Server::getBufferReceived() const
{
    return m_buffer;
}