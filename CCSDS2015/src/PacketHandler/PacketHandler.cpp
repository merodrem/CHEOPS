
#include "PacketHandler.h"


PacketHandler::PacketHandler(const char *file) : packet_parser(file) {
    log = new ofstream("log.txt");
}

PacketHandler::~PacketHandler() {
    if(log->is_open())
       log->close();

    delete log;

}

void PacketHandler::readWholeFile(){

    while(packet_parser.hasnext()){
        char* d = NULL;
        TM_Packet temp = packet_parser.nextPacket(d);
      //  cout<< "SCET_time: " << temp.data.header.SCET_time<< endl;
        try{
         error_handler.verifyPacket(temp);
        }
        catch(exception e){
            string message(e.what());
            (*log) << message;
        }
        delete[] d;
    }



}


int main(int argc, char* argv[])
{

    PacketHandler ph(argv[1]);
    ph.readWholeFile();


    return 0;
}

