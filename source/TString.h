#include <string>
#include <fstream>

#ifndef UNICODE
typedef std::ifstream TIfStream;
typedef std::string TString;
#define to_TString std::to_string
#else
typedef std::wifstream TIfStream;
typedef std::wstring TString;
#define to_TString std::to_wstring
#endif