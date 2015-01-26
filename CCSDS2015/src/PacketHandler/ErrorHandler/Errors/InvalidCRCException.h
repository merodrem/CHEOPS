#ifndef INVALID_CRC_EXCEPTION_H
#define INVALID_CRC_EXCEPTION_H



/*!
 * \file InvalidCRCException.h
 * \brief This file contains the definition of the InvalidCRCException class, invoked when a checksum contained in a packet does not match the CRC computed.
 * \author Julien Graisse
 * \version 0.9
 */

#include "PacketException.h"

/*! \class InvalidCRCException
   * \brief invoked when a checksum contained in a packet does not match the CRC computed.
   */
class InvalidCRCException: public PacketException {
    public:
    /*!
    *  \brief constructor
    *  \param m : the value to give to the error message string
    */
    InvalidCRCException(const char* m) : PacketException(m){

    }

  virtual const char* what() const throw();
};

#endif

