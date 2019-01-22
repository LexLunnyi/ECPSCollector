#include "functions.h"



namespace ecps {
    
    
string to_string(int i) {
    std::stringstream ss;
    ss << i;
    return ss.str();
}


string to_hexstring(uint16_t val) {
    char data[17];
    sprintf(data, "%x", val);
    data[16] = 0;
    string res(data);
    return res;
}


}