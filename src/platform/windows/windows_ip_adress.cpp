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
        int result = InetPtonW(AF_INET, std::wstring(str.begin(), str.end()).c_str(), &addr);
        if (result <= 0) BK_CORE_ERROR("Bad IP {0}", result);
        return addr; 
    }
}