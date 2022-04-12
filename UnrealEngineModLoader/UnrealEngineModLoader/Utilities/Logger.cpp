#include "Logger.h"

std::mutex Log::mtx;
std::vector<std::string> Log::LogArray;