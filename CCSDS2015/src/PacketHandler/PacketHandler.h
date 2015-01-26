#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

/*!
 * \file PacketHandler.h
 * \brief This file contains definition of the class PacketHandler managing incoming packets.
 * \author Julien Graisse
 * \version 0.9
 */




#include <fstream>
#include <string>
#include "PacketParser/PacketParser.h"
#include "ErrorHandler/ErrorHandler.h"

using namespace std;


/*! \class PacketParser
   * \brief module managing incoming packets
   */
class PacketHandler{
    public:
    /*!
     *  \brief Constructor of the class PacketHandler
     *  \param The path to the input file
     */
     PacketHandler(const char*file);
     /*!
      *  \brief extracts all packets from the input and read their content.
      * testing-purposed method.
      */
     void readWholeFile();
     /*!
      *  \brief Destructor of the class PacketHandler
      */
     ~PacketHandler();
    private:
     PacketParser packet_parser; /*!< The tool returning packet structures from the input file*/
     ErrorHandler error_handler;/*!< The error detector*/
     ofstream* log; /*!< The log file where errors are stored*/

};


#endif
