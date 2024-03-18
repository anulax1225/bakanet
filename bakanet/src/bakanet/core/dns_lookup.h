#pragma once

#include <bakanetpch.h>
#include "ip_version.h"
#include "ip_address.h"

namespace Bk::Net {
	std::vector<std::string> dns_lookup(const std::string& host_name, IpVersion ipv);
}