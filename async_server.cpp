#include "async_server.h"

#include <iostream>

using namespace std;
using boost::asio::ip::tcp;

void RequestHandler::start()
{
    do_read();
}

void RequestHandler::do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(
            ba::buffer(data_),
            [this, self](boost::system::error_code ec, std::size_t length)
            {
                if (!ec)
                {
                    cout << "Read " << length << "bytes: "
                         << string(data_.begin(), data_.begin() + length)
                         << endl;
                    async::receive(handle_, data_.data(), length);
                    do_read();
                } else {
                    async::disconnect(handle_);
                }
            }
    );
}


void BulkAsyncServer::do_accept() {
    acceptor_.async_accept(
            [this](boost::system::error_code ec, ba::ip::tcp::socket socket)
            {
                if (!ec)
                {
                    std::make_shared<RequestHandler>(std::move(socket), bulk_size_)->start();
                }

                do_accept();
            }
    );
}


