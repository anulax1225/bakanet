#include "ip_address.h"
#include <string.h>

namespace Bk::Net {
    IpAddress::IpAddress(const char* ip, IpVersion ipv)
    : str(ip), version(ipv)
    {
        if (inet_pton(AF_INET, str, &bytes) <= 0) perror("Bad IP");
    }
}