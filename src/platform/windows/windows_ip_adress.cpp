#include <bakanet/core/ip_address.h>
#include <string.h>

namespace Bk::Net {
    struct in_addr IpAddress::get_data() 
    {
        struct in_addr addr;
        if (!str.length()) {
            addr.s_addr = INADDR_ANY;
            return addr;
        }
        else if (InetPton(AF_INET, (PWSTR)str.c_str(), &addr) <= 0) perror("Bad IP");
        return addr; 
    }
}