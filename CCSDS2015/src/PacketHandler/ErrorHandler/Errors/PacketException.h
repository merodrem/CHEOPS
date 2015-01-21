#ifndef PACKET_EXCEPTION_H
#define PACKET_EXCEPTION_H

#include <exception>
#include <string>

class Packet_Exception: public std::exception {
  public:
  explicit Packet_Exception(const char* m);
  virtual const char* what() const throw();
  virtual ~Packet_Exception() throw();

protected:
  std::string message;
};

#endif
