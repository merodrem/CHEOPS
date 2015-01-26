#include "ErrorHandler.h"

#define MAX_PACKET_LENGTH 4112
#define VERSION_NUMBER 0
#define TYPE 0
#define HF 1
#define MIN_PROC_ID 77
#define MAX_PROC_ID 80
#define PACK_CAT 12
#define SEGMENT_FLAGS 0b11
#define MIN_SOURCE_SEQUENCE_COUNT 0
#define MAX_SOURCE_SEQUENCE_COUNT 16383
#define PUS 0
#define CHCK_FLAG 0
#define SPARE 0
#define PACK_TYPE 20
#define PACKET_SUBTYPE 3
#define PAD 0


//PUBLIC
void ErrorHandler::verifyPacket(const TM_Packet &packet){
    try{
        checkByteLength(packet);
        checkCRC(packet);
        checkSemantic(packet);


    }

    catch(const PacketException &e){

        throw e;

    }
}




//PRIVATE

void ErrorHandler::checkByteLength(const TM_Packet &packet){

    if((sizeof(packet) > MAX_PACKET_LENGTH)){
        throw InvalidLengthException("The length of the packet number isn't CCSDS-compliant");
    }
}

void ErrorHandler::checkCRC(const TM_Packet &packet){
    /*
     * NO CRC WITH MARSIS, IMPLEMENTATION FOR CHEOPS
     */
}

void ErrorHandler::checkSemantic(const TM_Packet &packet){

    if(packet.header.ID.version_number!= VERSION_NUMBER){
        throw InvalidValueException("Wrong version number");
    }
    else if(packet.header.ID.type != TYPE){
        throw InvalidValueException("Wrong type");
    }
    else if(packet.header.ID.DFHF != HF){
        throw InvalidValueException(" wrong data field header flag");
    }
    else if(packet.header.ID.ProcID > MAX_PROC_ID || packet.header.ID.ProcID < MIN_PROC_ID){
        throw InvalidValueException("Process ID out of possible values");
    }

//and so on with all exceptions...

}
