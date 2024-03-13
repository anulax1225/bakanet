#include <commun.h>

#include "http_parser.h"

using namespace Bk::Net;
void http_server();
std::string http_handler(Socket& sock, Connection conn);