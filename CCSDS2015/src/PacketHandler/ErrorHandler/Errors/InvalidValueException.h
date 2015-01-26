
#ifndef INVALID_VALUE_EXCEPTION_H
#define INVALID_VALUE_EXCEPTION_H


/*!
 * \file InvalidValueException.h
 * \brief This file contains the definition of the InvalidValueException class, invoked when a packet returns inconsistent values
 * \author Julien Graisse
 * \version 0.9
 */


#include "PacketException.h"

/*! \class InvalidValueException
   * \brief invoked when a packet returns inconsistent values
   */
class InvalidValueException: public PacketException {
  public:
    /*!
    *  \brief constructor
    *  \param m : the value to give to the error message string
    */
  InvalidValueException(const char* m) : PacketException(m){

  }

  virtual const char* what() const throw();

};

#endif

