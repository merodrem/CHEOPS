#ifndef INVALID_LENGTH_EXCEPTION_H
#define INVALID_LENGTH_EXCEPTION_H



/*!
 * \file InvalidLengthException.h
 * \brief This file contains the definition of the InvalidLengthException class, invoked when a packet's length exceeds CCSDS standard's max size
 * \author Julien Graisse
 * \version 0.9
 */

#include "PacketException.h"

/*! \class InvalidLengthException
   * \brief invoked when a packet's length exceeds CCSDS standard's max size
   */
class InvalidLengthException: public PacketException {
    public:
    /*!
    *  \brief constructor
    *  \param m : the value to give to the error message string
    */
    InvalidLengthException(const char* m) : PacketException(m){

    }

  virtual const char* what() const throw();


};

#endif

