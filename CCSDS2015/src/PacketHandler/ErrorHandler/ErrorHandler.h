#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H


#include "CRC.h"
#include "Errors/InvalidCRCException.h"
#include "Errors/InvalidLengthException.h"
#include "Errors/InvalidValueException.h"
#include "Errors/PacketException.h"
#include "Packet.h"



class ErrorHandler{
  
public:
  ErrorHandler(){}
  void verifyPacket(const TM_Packet* packet);
private:
  void checkByteLength(const TM_Packet* packet);
  void checkCRC(const TM_Packet* packet);
  void checkSemantic(const TM_Packet* packet);
  
};


#endif

