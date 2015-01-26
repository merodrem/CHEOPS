#include"PacketException.h"

PacketException::PacketException(const char *m) : message(m) {

}

const char* PacketException::what() const throw(){
    return message.c_str();
  }

 PacketException::~PacketException() throw(){

}
