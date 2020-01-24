#include <iostream>

#include <boost/asio.hpp>

#include "async_server.h"

using namespace std;
namespace ba = boost::asio;
using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
    try
    {
        if (argc < 2)
        {
            std::cerr << "Usage: bulk_server <port> <bulksize>\n";
            return 1;
        }

        ba::io_service io_context;

        tcp::endpoint endpoint(tcp::v4(), stol(argv[1]));
        size_t bulk_size = stol(argv[2]);
        BulkAsyncServer server(io_context, endpoint, bulk_size);

        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
