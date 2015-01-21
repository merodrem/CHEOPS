#include "CRC.h"

unsigned CRC::get_CRC(unsigned char Data, unsigned Syndrome){
    int i;
    for (i=0; i<8; i++) {
        if ((Data & 0x80) ^ ((Syndrome & 0x8000) >> 8)) {
             Syndrome = ((Syndrome << 1) ^ 0x1021) & 0xFFFF;
        }
        else {
            Syndrome = (Syndrome << 1) & 0xFFFF;
         }
         Data = Data << 1;
    }
    return (Syndrome);
}
