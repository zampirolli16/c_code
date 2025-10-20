#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint16_t calculate_crc16(const uint8_t* data, size_t len) {
    uint16_t crc = 0xFFFF;
    const uint16_t poly = 0xF005;
    uint8_t data_func[len];
    
    for (size_t h = 0; h < len; h++){
        data_func[h] = data[h];
    }

    for (size_t i = 0; i < len; i++) {
        printf("------------------------------------\n Byte %ld\n", i);
        crc ^= (uint16_t)data[i] << 8;
        printf ("crc: 0x%X\n", crc);
        for (int j = 0; j < 8; j++) {
            printf("bit %d: \n", j);
            if (crc & 0x8000) {
                crc = (crc << 1) ^ poly;
            } else {
                crc <<= 1;
            }
            printf ("->crc: 0x%X\n", crc);
        }
    }

    //printf ("CRC calculado: 0X%X\n", crc);
    return crc;
}

void main (void){
    size_t bytes = 5;    
    uint8_t data[5] = {0xD0, 0xF0, 0x40, 0x00, 0x01};
    uint16_t result_crc;

    // printf("------------------------------------\n");
    // printf("Data dentro da main(): \n");
    // for (int i = 0; i < bytes; i++){
    //     printf ("byte %d: 0x%X \n", i, data [i]);
    // } 

    result_crc = calculate_crc16(&data[0], bytes);
    printf("fim2\n");
}

uint16_t calculate_crc16(const uint8_t* data, size_t len);

