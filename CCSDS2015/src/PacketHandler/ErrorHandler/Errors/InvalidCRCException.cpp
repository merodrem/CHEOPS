#include "InvalidCRCException.h"


const char* InvalidCRCException::what() const throw(){
    return message.c_str();
  }
