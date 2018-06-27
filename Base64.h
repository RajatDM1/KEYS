#ifndef BASE64_H
#define BASE64_H

#include <vector>
#include <string>

namespace Base64
{
    //const::string & - constant reference to a string
    std::string base64_encode(const std::string &);
    const std::string &SALT1 = "nit";
    const std::string &SALT2 = "iiit";
    const std::string &SALT3 = "hamirpur";

    std::string EncryptB64(std::string s)
    {
        s = s+ SALT1+SALT2+SALT3;
        s = base64_encode(s);
        s.insert(7, SALT3);
        s += SALT1;
        s = base64_encode(s);
        s = SALT2+SALT3+SALT1;
        s = base64_encode(s);
        s.insert(1,"R");
        s.insert(1,"D");
        return s;
    }

    const std::string &BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string base64_encode(const std::string &s)
    {
        //the output string which we'll fill with encoded characters
        std::string ret;
        int val = 0;
        int bits = -6;//number of bits in a subgroup
        const unsigned int b63= 0x3F;

        for(const auto &c : s)
        {
            val = (val << 8) + c;//shifting left by 8 places, like val = val*2^8;
            bits+= 8;
            while(bits>=0)
            {
                //first shift by 'bits' then do the binary AND then push back
                ret.push_back(BASE64_CODES[(val>>bits) & b63]);
                bits-=6;//as we are grouping by 6 in base 64
            }
        }

        if(bits > -6)
        ret.push_back(BASE64_CODES[((val<<8)>>(bits+8)) & b63]);

        while(ret.size()%4)
            ret.push_back('=');

        return ret;
    }
}

#endif // BASE64_H
