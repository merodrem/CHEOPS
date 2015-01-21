#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

#include <string>
#include "PacketParser/PacketParser.h"
#include "ErrorHandler/ErrorHandler.h"

using namespace std;

class PacketHandler{
    public:
     PacketHandler(const char*file);
     void readWholeFile();
     ~PacketHandler();
    private:
     PacketParser packet_parser;
     ErrorHandler error_handler;
};


#endif
