#include "base64.h"
using namespace std;

char* base64_decode(char *s) {
    char *unit = s, *e, *r, *_ret;
    int len = strlen(s);
    unsigned char i;
    e = s + len;
    len = len / 4 * 3 + 1;
    r = _ret = new char[len];

    while (unit < e) {

        for (i = 0; unit[0] != Alp[i] && i < 64; i++)
            ;
        if (i == 64)
        {
            unit[0] = 0;
        }
        else
        {
            unit[0] = i;
        }

        for (i = 0; unit[1] != Alp[i] && i < 64; i++)
            ;
        if (i == 64)
        {
            unit[1] = 0;
        }
        else
        {
            unit[1] = i;
        }

        for (i = 0; unit[2] != Alp[i] && i < 64; i++)
            ;
        if (i == 64)
        {
            unit[2] = 0;
        }
        else
        {
            unit[2] = i;
        }

        for (i = 0; unit[3] != Alp[i] && i < 64; i++)
            ;
        if (i == 64)
        {
            unit[3] = 0;
        }
        else
        {
            unit[3] = i;
        }

        *r++ = (unit[0] << 2) | (unit[1] >> 4);
        *r++ = (unit[1] << 4) | (unit[2] >> 2);
        *r++ = (unit[2] << 6) | unit[3];
        unit += 4;
    }
    *r = 0;

    return _ret;
}



char* base64_encode(char *s) {
    char *unit = s, *e, *r, *_ret;
    int len = strlen(s);
    unsigned char i;
    e = s + len;
    if (len % 3 == 0)
    {
        len = len / 3 * 4;
        r = _ret = new char[len];

        while (unit < e) {
            *r++ = Alp[unit[0] / 4];
            *r++ = Alp[(unit[0] % 4) * 16 + (unit[1]) / 16];
            *r++ = Alp[(unit[1] % 16) * 4 + unit[2] / 64];
            *r++ = Alp[unit[2] % 64];
            unit += 3;
        }
        *r = 0;
        return _ret;

    }
    else if (len % 3 == 1)
    {
        len = (len / 3 + 1) * 4 + 1;
        r = _ret = new char[len];
        while (unit < e) {
            if ((unit + 3) < e)
            {
                *r++ = Alp[unit[0] / 4];
                *r++ = Alp[(unit[0] % 4) * 16 + (unit[1]) / 16];
                *r++ = Alp[(unit[1] % 16) * 4 + unit[2] / 64];
                *r++ = Alp[unit[2] % 64];

            }
            else
            {
                *r++ = Alp[unit[0] / 4];
                *r++ = Alp[(unit[0] % 4) * 16];
                *r++ = '=';
                *r++ = '=';
            }
            unit += 3;
        }
        *r = 0;
        return _ret;


    }
    else if (len % 3 == 2)
    {
        len = (len / 3 + 1) * 4 + 1;
        r = _ret = new char[len];
        while (unit < e) {
            if ((unit + 3) < e)
            {
                *r++ = Alp[unit[0] / 4];
                *r++ = Alp[(unit[0] % 4) * 16 + (unit[1]) / 16];
                *r++ = Alp[(unit[1] % 16) * 4 + unit[2] / 64];
                *r++ = Alp[unit[2] % 64];
            }
            else
            {
                *r++ = Alp[unit[0] / 4];
                *r++ = Alp[(unit[0] % 4) * 16 + (unit[1]) / 16];
                *r++ = Alp[(unit[1] % 16) * 4];
                *r++ = '=';
            }
            unit += 3;
        }
        *r = 0;
        return _ret;
    }

}

void outputImage(string filename)
{
	ifstream in(filename + "\\image.txt");
    ofstream out(filename+"\\"+"image.png", ios::binary);
    char *read_ = new char[4];
    char *write_ = new char[3];
    in >> read_[0] >> read_[1] >> read_[2] >> read_[3];
    while (!in.eof())
    {
        write_ = base64_decode(read_);
        out << write_[0] << write_[1] << write_[2];
        in >> read_[0] >> read_[1] >> read_[2] >> read_[3];
    }
    in.close();
    out.close();
}

string std_base64_decode(string str)
{
	char* c_str = const_cast<char *>(str.c_str());
	char* c_decodedStr = base64_decode(c_str);
	string decodeStr = c_decodedStr;
	return decodeStr;
}