#pragma once

#include <string>

int clientSend(char* serverIp, int port, std::string query);
char* serverRead(int port);