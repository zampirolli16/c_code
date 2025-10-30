#ifndef CRC_H
#define CRC_H

void shift_left_array(uint8_t* vetor, size_t tamanho);
void bit_stream (const uint8_t* data, uint8_t* data_out, size_t len);
uint16_t calculate_crc16(const uint8_t* data, size_t len, bool flag_verif);

#endif 
