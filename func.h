#ifndef FUNC
#define FUNC

#include <string>
#include <fstream>
#include <iostream>
#include <WinSock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "base64.h"
#include "user.h"

const std::string DEFAULT_MAIL_PATH = "\\mail";

enum Command {HELO = 1, EHLO, MAIL, AUTH,RCPT, DATA, RSET, NOOP, QUIT};
int parseCommand(std::string commandString);


std::string get_image_base64_code(std::string &mail_content);

std::string get_subject(std::string mail_content);

std::string readFile(std::string filename);

#endif