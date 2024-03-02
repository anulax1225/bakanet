#pragma once

#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include <netdb.h>
#include <arpa/inet.h>

#include "ip_version.h"

namespace Bk::Net {
	std::vector<std::string> dns_lookup(const std::string &host_name, IpVersion ipv);
}