#ifndef PACKET_H
#define PACKET_H
#include <stdint.h>


/*******************
*TELEMETRY HEADER  *
********************/
struct Packet_ID
{
   uint16_t pack_cat   :4;
   uint16_t ProcID     :7;
   uint16_t DFHF     :1;
   uint16_t type  :1;
   uint16_t version_number   :3;
} __attribute__ ((__packed__));

struct Packet_Sequence_Control{
    uint16_t source_seq_count :14;
    uint16_t seq_flags : 2;

} __attribute__ ((__packed__));


struct TM_Header{
  uint16_t length;
 Packet_Sequence_Control psc;
 Packet_ID ID;
} __attribute__ ((__packed__));


/**********************
*TELEMETRY DATA FIELD *
***********************/

struct Data_Field_header{
    uint16_t pad :8;
    uint16_t subtype :8;
    uint16_t type :8;
    uint16_t spare :4;
    uint16_t check_flag : 1;
    uint16_t PUS :3;
    uint64_t SCET_time :48;
} __attribute__ ((__packed__));

struct Scientific_Data_Packet_ID {
    uint16_t frame_ID;
    uint32_t OST_line2;
    uint64_t OST_line1;
    uint16_t OST_lines;
    uint64_t SCET :48;
} __attribute__ ((__packed__));

struct Ancillary_Data_Header{
    uint32_t spare :30;
    uint16_t seqm_flags :2;
    uint16_t source_seq_count :14;
    uint16_t data_type :2;
    Scientific_Data_Packet_ID sdpID;
} __attribute__ ((__packed__));

struct Ancillary_Data{
    uint8_t aux_data[228];
    Ancillary_Data_Header adh;
} __attribute__ ((__packed__));

struct Source_Data{
    Ancillary_Data ancillary;
    int scientific_length;
    char* scientific;
}__attribute__ ((__packed__));

struct Packet_Data_Field{
    Source_Data source_data;
    Data_Field_header header;
}__attribute__ ((__packed__));


/**********************
*TELEMETRY DATA FIELD *
***********************/
struct TM_Packet{
    TM_Header header;
    Packet_Data_Field data;
}__attribute__ ((__packed__));


#endif

