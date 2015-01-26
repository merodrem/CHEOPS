#ifndef CRC_H
#define CRC_H


/*!
 * \file CRC.h
 * \brief This file contains the definition of the CRC class, providing methods to check the Cyclic Redundancy Check of a provided checksum.
 * \author Julien Graisse
 * \version 0.9
 */


/*! \class CRC
   * \brief class providing methods to check the Cyclic Redundancy Check of a provided checksum. NOT USABLE FOR THE MOMENT. NO CRC ON MARSIS PACKETS
   */
class CRC{

    static unsigned get_CRC(unsigned char Data, unsigned Syndrome);
};

#endif
