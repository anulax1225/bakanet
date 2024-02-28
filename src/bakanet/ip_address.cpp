#include "ip_address.h"

namespace Bk::Net {
    IpAddress::IpAddress(const char* ip)
    : str(ip)
    {
        if (inet_pton(AF_INET, str, &bytes) <= 0) perror("Bad IP");
    }

    void IpAddress::from_dns(char* dns) 
    {

    }
}