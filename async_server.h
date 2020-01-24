#pragma once

#include <memory>
#include <algorithm>

#include <boost/asio.hpp>

#include "async.h"

namespace ba = boost::asio;

class RequestHandler : public std::enable_shared_from_this<RequestHandler> {
public:
    explicit RequestHandler(ba::ip::tcp::socket socket, std::size_t bulk_size)
        : socket_(std::move(socket)), handle_(async::connect(bulk_size))
    {
        std::fill(data_.begin(), data_.end(), 0);
    }

    void start();

private:
    ba::ip::tcp::socket socket_;
    std::array<char, 1024> data_;
    async::handle_t handle_;

    // methods
    void do_read();
};

class BulkAsyncServer {
public:
    BulkAsyncServer(ba::io_service& io_context, const ba::ip::tcp::endpoint& endpoint,
            std::size_t bulk_size)
        : acceptor_(io_context, endpoint), bulk_size_(bulk_size)
    {
        do_accept();
    }

private:

    void do_accept();

    boost::asio::ip::tcp::acceptor acceptor_;
    std::size_t bulk_size_ = 0;
};