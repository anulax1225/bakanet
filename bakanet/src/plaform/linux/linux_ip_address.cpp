#include <bakanet/sock_layer/ip_address.h>
#include <string.h>

namespace Bk::Net {
    struct in_addr IpAddress::get_data() 
    {
        struct in_addr addr;
        if (!str.length()) {
            addr.s_addr = INADDR_ANY;
            return addr;
        }
        else if (inet_pton(AF_INET, str.c_str(), &addr) <= 0) perror("Bad IP");
        return addr; 
    }
}