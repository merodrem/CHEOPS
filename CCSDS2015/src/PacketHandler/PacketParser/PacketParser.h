#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H


#include <fstream>
#include <iostream>
#include <cstring>
#include <exception>
#include "Packet.h"

using namespace std;

class PacketParser{
   public:
    PacketParser(const char *filepath);
    ~PacketParser();

    TM_Packet nextPacket(char* scientific_data);
    bool hasnext();

private:
    ifstream* file;
    int packet_counter;
};

#endif
