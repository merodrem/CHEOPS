#include "PacketParser.h"

#define BYTE (8u)
#define HEADER_LENGTH (6u)
#define ANCILLARY_DATA_HEADER_LENGTH (256u)
#define DATA_HEADER_LENGTH (10u)
#define ESOC_HEADER_LENGTH (18u)

PacketParser::PacketParser(const char* filepath){
    packet_counter = 0;
    file = new ifstream(filepath, ios::in|ios::binary);
    if (!file->is_open()){
        delete file;
        throw ifstream::failure("The file couldn't be opened.");
    }


}

PacketParser::~PacketParser(){
    if (file->is_open()){
        file->close();
    }
    delete file;
}


//TODO: add parameter for info level, origin of message
TM_Packet PacketParser::nextPacket(char* &scientific_data){
    if(!file->eof()){
        packet_counter++;
        cout << "++++++++++PACKET " << packet_counter << " ++++++++++" << endl;

        char esoc_header[ESOC_HEADER_LENGTH];
        file->read(esoc_header, ESOC_HEADER_LENGTH);


        uint8_t byteArray[HEADER_LENGTH];

        file->read((char*)byteArray, HEADER_LENGTH);
/*
        for(int i = 0 ; i < HEADER_LENGTH; i++){
            printf("%X \n", byteArray[i]);
        }*/

        TM_Header header;


         header.ID.version_number = (byteArray[0] >> 5 ) & 0x07;
         header.ID.type = (byteArray[0] >> 4 ) & 0x01;
         header.ID.DFHF = (byteArray[0] >> 3 ) & 0x01;
         header.ID.ProcID =  (byteArray[0] & 0x07) << 4 | (byteArray[1] >> 4) ;
         header.ID.pack_cat = byteArray[1] & 0x0f;
         header.psc.seq_flags = (byteArray[2] >> 6 );
         header.psc.source_seq_count = (byteArray[2] & 0x3f) << BYTE | byteArray[3] ;
         header.length = byteArray[4] << BYTE | byteArray[5];


        cout << "Version number: " << header.ID.version_number << endl;
        cout << "Type: "<< header.ID.type << endl;
        cout << "data field header flag: "<< header.ID.DFHF << endl;
        cout << "Process ID: "<< header.ID.ProcID << endl;
        cout << "Packet cat. : "<< header.ID.pack_cat << endl;
        cout << "Segmentation flags: "<< header.psc.seq_flags << endl;
        cout << "Source sequence count: "<<header.psc.source_seq_count << endl;
        cout << "Length: "<<header.length << endl;


        char* data = new char[ DATA_HEADER_LENGTH + sizeof(Ancillary_Data)];
        file->read(data, DATA_HEADER_LENGTH + sizeof(Ancillary_Data));

        Data_Field_header data_header;

        data_header.SCET_time = data[0] << 5*BYTE | data[1] << 4*BYTE | data[2] << 3*BYTE | data[3] <<  2*BYTE | data[4] << BYTE | data[0];
        data_header.PUS = data[6] >> 5;
        data_header.check_flag = data[6] >> 4 & 0x01;
        data_header.spare = data[6] & 0x0f;
        data_header.type = data[7];
        data_header.subtype = data[8];
        data_header.pad = data[9];


        Scientific_Data_Packet_ID sc_data_packet_id;
        sc_data_packet_id.SCET = data[10] << 5*BYTE | data[11] << 4*BYTE | data[12] << 3*BYTE | data[13] <<  2*BYTE | data[14] << BYTE | data[15];
        sc_data_packet_id.OST_lines = data[16] << BYTE | data[17];
        sc_data_packet_id.OST_line1 = data[18] << 7*BYTE | data[19] << 6*BYTE | data[20] << 5*BYTE | data[21] << 4*BYTE | data[22] << 3*BYTE | data[23] <<  2*BYTE | data[24] << BYTE | data[25];
        sc_data_packet_id.OST_line2 =  data[26] << BYTE | data[27];
        sc_data_packet_id.frame_ID = data[28] << BYTE | data[29];

        Ancillary_Data_Header ancillary_data_header;
        ancillary_data_header.sdpID = sc_data_packet_id;
        ancillary_data_header.data_type = (data[30] >> 6 );
        ancillary_data_header.source_seq_count = (data[30] & 0x3f) << BYTE | data[31] ;
        ancillary_data_header.seqm_flags =(data[32] >> 6 );
        ancillary_data_header.spare = (data[32] & 0x3f) << 3*BYTE | data[33] << 2*BYTE |data[34] <<BYTE | data[35];

        Ancillary_Data anc_data;
        anc_data.adh = ancillary_data_header;
        int i;
        for(i = 36 ; i < 264 ; i++)
            anc_data.aux_data[i-36] = data[i];

        Source_Data sd;
        sd.ancillary = anc_data;
        const int size_temp = header.length + 1 - DATA_HEADER_LENGTH -sizeof(Ancillary_Data);
        sd.scientific_length = size_temp;
        scientific_data = new char[size_temp];
        file->read(scientific_data, size_temp);
        sd.scientific = scientific_data;


        Packet_Data_Field data_field;
        data_field.header = data_header;
        data_field.source_data = sd;
        TM_Packet packet;
        packet.header = header;
        packet.data = data_field;
        delete[] data;
        return packet;

    }
    else {
        throw ifstream::failure("End of file reached. No more packet can be read.");
    }
}

bool PacketParser::hasnext(){
    return !(file->eof());
}
