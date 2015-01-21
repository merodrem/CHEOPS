#include "InvalidValueException.h"


const char* InvalidValueException::what() const throw(){
    return message.c_str();
  }
