#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "crc.h"

const size_t bytes = 5;
uint8_t data[5] = {0x0B, 0x0F, 0x02, 0x00, 0x80};

void main (void){    
    uint16_t result_crc;
    uint16_t verif;
    uint8_t verif_array[7] = {0x29, 0xC0, 0x0B, 0x0F, 0x02, 0x00, 0x80};
    
    
    printf ("Calcucando CRC \n");
    result_crc = calculate_crc16(&data[0], bytes, 0);
   
    printf ("-------------------------------\n");
    
    printf ("Verificando o CRC calculado \n");
    verif = calculate_crc16(&verif_array[0], bytes + 2, 1);
}