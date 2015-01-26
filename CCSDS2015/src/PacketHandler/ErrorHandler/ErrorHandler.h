#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H



/*!
 * \file ErrorHandler.h
 * \brief This file contains the definition of the ErrorHandler class, checking the concistency of provided packets
 * \author Julien Graisse
 * \version 0.9
 */

#include "CRC.h"
#include "Errors/InvalidCRCException.h"
#include "Errors/InvalidLengthException.h"
#include "Errors/InvalidValueException.h"
#include "Errors/PacketException.h"
#include "Packet.h"

/*! \class ErrorHandler
   * \brief module checking the concistency of provided packets
   */
class ErrorHandler{
  
public:
    /*!
    *  \brief constructor
    */
  ErrorHandler(){}

  /*!
  *  \brief Verifies wether or not the provided packet is faulty. Throws the corresponding exception if it is.
  *  \param packet : a constant referrence to the packet to check
  */
  void verifyPacket(const TM_Packet &packet);


private:

  /*!
  *  \brief Verifies the checksum of the provided packet. Throws InvalidCRCException if it does not match the computed CRC.
  *  \param packet : a constant referrence to the packet to check
  */
  void checkCRC(const TM_Packet &packet);


  /*!
  *  \brief Verifies the length of the provided packet. Throws InvalidLengthException if it outbounds the maximal size of a CCSDS compliant packet.
  *  \param packet : a constant referrence to the packet to check
  */
  void checkByteLength(const TM_Packet &packet);

  /*!
  *  \brief Verifies wether or not data contained in the provided packet is consistent. Throws InvalidValueException if it isn't.
  *  \param packet : a constant referrence to the packet to check
  */
  void checkSemantic(const TM_Packet &packet);
  
};


#endif

