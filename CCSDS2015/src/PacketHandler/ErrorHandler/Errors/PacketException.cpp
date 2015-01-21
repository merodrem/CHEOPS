#include"PacketException.h"

Packet_Exception::Packet_Exception(const char *m) : message(m) {

}

const char* Packet_Exception::what() const throw(){
    return message.c_str();
  }

 Packet_Exception::~Packet_Exception() throw(){

}
