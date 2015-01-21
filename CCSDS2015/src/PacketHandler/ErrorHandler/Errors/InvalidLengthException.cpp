#include "InvalidLengthException.h"


const char* InvalidLengthException::what() const throw(){
    return message.c_str();
  }
