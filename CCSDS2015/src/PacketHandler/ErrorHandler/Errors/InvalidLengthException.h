#ifndef INVALID_LENGTH_EXCEPTION_H
#define INVALID_LENGTH_EXCEPTION_H

#include "PacketException.h"


class InvalidLengthException: public Packet_Exception {
    public:
    InvalidLengthException(const char* m) : Packet_Exception(m){

    }

  virtual const char* what() const throw();


};

#endif

