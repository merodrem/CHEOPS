#ifndef PACKET_EXCEPTION_H
#define PACKET_EXCEPTION_H


/*!
 * \file PacketException.h
 * \brief This file contains the definition of the mother class PacketException for all kinds of exceptions
 * \author Julien Graisse
 * \version 0.9
 */

#include <exception>
#include <string>


/*! \class PacketException
   * \brief base-class for the implementation of all possible exceptions on a telemetry packet
   */
class PacketException: public std::exception {
  public:

    /*!
    *  \brief constructor
    *  \param m : the value to give to the error message string
    */
  explicit PacketException(const char* m);

  virtual const char* what() const throw();
  virtual ~PacketException() throw();

protected:
  std::string message; /*!< The error message*/
};

#endif
