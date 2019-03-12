//include statements and conditional compilation for linux vs. windows
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#if defined (_WIN32)
#define PLATFORM_NAME "windows" //define windows libraries
#include <winsock2.h>
#include <winsock.h>
#pragma comment(lib, "ws2_32.lib")
#elif defined(__linux__)
#define PLATFORM_NAME "linux" //define windows libraries
#endif