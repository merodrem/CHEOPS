#ifndef PACKET_H
#define PACKET_H


/*!
 * \file Packet.h
 * \brief This file contains definitions of all fields and subfields composing a telemmetry packet
 * \author Julien Graisse
 * \version 0.9
 */


#include <stdint.h>


/*******************
*TELEMETRY HEADER  *
********************/


/*!
 * \struct Packet_ID
 * \brief PACKET ID data field of a telemetry packet
 *
 * Subfield of TM_Header
 */
struct Packet_ID
{
   uint16_t pack_cat   :4;
   uint16_t ProcID     :7;
   uint16_t DFHF     :1;
   uint16_t type  :1;
   uint16_t version_number   :3;
} __attribute__ ((__packed__));


/*!
 * \struct Packet_Sequence_Control
 * \brief PACKET SEQUENCE CONTROL data field of a telemetry packet
 *
 * Subfield of TM_Header
 */
struct Packet_Sequence_Control{
    uint16_t source_seq_count :14;
    uint16_t seq_flags : 2;

} __attribute__ ((__packed__));


/*!
 * \struct TM_Header
 * \brief SOURCE PACKET HEADER data field of a telemetry packet
 *
 * Subfield of TM_Packet
 */
struct TM_Header{
  uint16_t length;
 Packet_Sequence_Control psc;
 Packet_ID ID;
} __attribute__ ((__packed__));


/**********************
*TELEMETRY DATA FIELD *
***********************/

/*!
 * \struct Data_Field_header
 * \brief DATA FIELD HEADER data field of a telemetry packet
 *
 * Subfield of Packet_Data_Field
 */
struct Data_Field_header{
    uint16_t pad :8;
    uint16_t subtype :8;
    uint16_t type :8;
    uint16_t spare :4;
    uint16_t check_flag : 1;
    uint16_t PUS :3;
    uint64_t SCET_time :48;
} __attribute__ ((__packed__));


/*!
 * \struct Scientific_Data_Packet_ID
 * \brief Scientific Data Packet ID data field of a telemetry packet
 *
 * Subfield of Ancillary_Data_Header
 */
struct Scientific_Data_Packet_ID {
    uint16_t frame_ID;
    uint32_t OST_line2;
    uint64_t OST_line1;
    uint16_t OST_lines;
    uint64_t SCET :48;
} __attribute__ ((__packed__));


/*!
 * \struct Ancillary_Data_Header
 * \brief ANCILLARY DATA HEADER data field of a telemetry packet
 *
 * Subfield of Ancillary_Data
 */
struct Ancillary_Data_Header{
    uint32_t spare :30;
    uint16_t seqm_flags :2;
    uint16_t source_seq_count :14;
    uint16_t data_type :2;
    Scientific_Data_Packet_ID sdpID;
} __attribute__ ((__packed__));

/*!
 * \struct Ancillary_Data
 * \brief ANCILLAY DATA data field of a telemetry packet
 *
 * Subfield of Source_Data
 */
struct Ancillary_Data{
    uint8_t aux_data[228];
    Ancillary_Data_Header adh;
} __attribute__ ((__packed__));

/*!
 * \struct Source_Data
 * \brief SOURCE DATA data field of a telemetry packet
 *
 * Subfield of Packet_Data_Field
 */
struct Source_Data{
    Ancillary_Data ancillary;
    int scientific_length;
    char* scientific;
}__attribute__ ((__packed__));


/*!
 * \struct Packet_Data_Field
 * \brief PACKET DATA FIELD data field of a telemetry packet
 *
 * Subfield of TM_Packet
 */
struct Packet_Data_Field{
    Source_Data source_data;
    Data_Field_header header;
}__attribute__ ((__packed__));


/*****************
*TELEMETRY PACKET*
*****************/

/*!
 * \struct TM_Packet
 * \brief telemetry packet
 *
 *
 */
struct TM_Packet{
    TM_Header header;
    Packet_Data_Field data;
}__attribute__ ((__packed__));


#endif

