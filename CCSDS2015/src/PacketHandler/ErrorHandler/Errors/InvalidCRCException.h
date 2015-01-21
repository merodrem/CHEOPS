#ifndef INVALID_CRC_EXCEPTION_H
#define INVALID_CRC_EXCEPTION_H

#include "PacketException.h"

class InvalidCRCException: public Packet_Exception {
    public:
    InvalidCRCException(const char* m) : Packet_Exception(m){

    }

  virtual const char* what() const throw();
};

#endif

