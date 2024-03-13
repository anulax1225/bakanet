#include <bakanet/sock_layer/ip_address.h>
#include <string.h>

namespace Bk::Net {
    std::unique_ptr<void*> IpAddress::get_data() 
    {
        struct in_addr addr;
        if (inet_pton(AF_INET, str.c_str(), &addr) <= 0) perror("Bad IP");
        return std::make_unique<void*>(&addr); 
    }
}