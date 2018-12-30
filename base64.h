#ifndef BASE_64
#define BASE_64

#include <string>
#include <fstream>
static const char Alp[64] = {
    'A','B','C','D','E','F','G',
    'H','I','J','K','L','M','N',
    'O','P','Q','R','S','T',
    'U','V','W','X','Y','Z',
    'a','b','c','d','e','f','g',
    'h','i','j','k','l','m','n',
    'o','p','q','r','s','t',
    'u','v','w','x','y','z',
    '0','1','2','3','4','5','6',
    '7','8','9','+','/'
};

char *base64_decode(char *s);
char *base64_encode(char *s);

std::string std_base64_decode(std::string);

void outputImage(std::string filename);

#endif