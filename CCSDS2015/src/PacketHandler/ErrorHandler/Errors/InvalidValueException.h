#ifndef INVALID_VALUE_EXCEPTION_H
#define INVALID_VALUE_EXCEPTION_H

#include "PacketException.h"

class InvalidValueException: public Packet_Exception {
  public:
  InvalidValueException(const char* m) : Packet_Exception(m){

  }

  virtual const char* what() const throw();

};

#endif

