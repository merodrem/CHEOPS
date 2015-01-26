#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H

/*!
 * \file PacketParser.h
 * \brief This file contains the definition of the PacketParser class, reading incoming bitstreams and converting them into packets structures.
 * \author Julien Graisse
 * \version 0.9
 */

#include <fstream>
#include <iostream>
#include <cstring>
#include <exception>
#include "Packet.h"

using namespace std;

/*! \class PacketParser
   * \brief module reading incoming bitstreams and converting them into packets structures.
   */
class PacketParser{
   public:
    /*!
    *  \brief constructor
    *  \param filepath : the path to the input file.
    */
    PacketParser(const char *filepath);
    /*!
    *  \brief destructor
    */
    ~PacketParser();


    /*!
    *  \brief reads the next packet from the input file
    *  \param scientific_data : a referrence to the pointer where the scientific data must be dynamically allocated. It is the responsability of the programmer to free the memory afterwards.
    *  \return The generated packet
    */
    TM_Packet nextPacket(char *&scientific_data);


    /*!
    *  \brief checks if the input file still has data to be read
    *  \return false if the end of the input file is reached, true otherwise
    */
    bool hasnext();

private:
    ifstream* file;/*!< the input file from which packets are read*/
    int packet_counter; /*!< counter labelling the packets read*/
};

#endif
