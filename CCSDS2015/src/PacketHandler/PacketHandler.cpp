
#include "PacketHandler.h"


PacketHandler::PacketHandler(const char *file) : packet_parser(file) {

}

PacketHandler::~PacketHandler() {

}

void PacketHandler::readWholeFile(){
    char* d;
    while(packet_parser.hasnext()){
     packet_parser.nextPacket(d);

    }
    delete[] d;

}


int main(int argc, char* argv[])
{

    PacketHandler ph(argv[1]);
    ph.readWholeFile();


    return 0;
}

