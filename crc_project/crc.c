#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const size_t bytes = 5;
uint8_t data[5] = {0x0B, 0x0F, 0x02, 0x00, 0x80};

uint16_t calculate_crc16(const uint8_t* data, size_t len) {
    uint16_t crc = 0xFFFF;
    const uint16_t poly = 0xF005;
    uint8_t data_func[len];
    uint8_t data_stream[len];

    //inicializando os vetores
    for (size_t h = 0; h < len; h++){
        data_func[h] = data[h];
        data_stream[h] = 0x00;
    }

    //Definindo vetor em ordem data stream (calculando byte por byte) {funciona}
    for (size_t h = 0; h < len; h++){

        //laço para inverter a ordem dos bits de cada byte (data stream)
        uint8_t interm = 0x00;  //vetor que receberá os bits invertidos em cada iteração
        uint8_t um_low = 0x01; //Seleção dos bits inferiores do vetor orininal a serem invertidos (b0 -> b3)
        uint8_t um_high = 0x80; //Seleção dos bits superiores do vetor original a serem invertidos (b7 -> b4)
        for (size_t k = 0; k < 4; k++){
            interm += (data[h] & um_low) << (7-2*k); //Selecionando o bit inferior e colocando ele na nova posição dentro do intermediário
            interm += (data[h] & um_high) >> (7-2*k); //Selecionando o bit superior e colocando ele na nova posição dentro do intermediário 

            //Atualizando os bits que serão selecionados na próxima iteração
            um_high >>= 1;
            um_low <<= 1;
        }
        data_stream[h] = interm; //alocando o byte invertido no vetor final
    }

    //XOR entre 0XFFFF e os dois bytes mais significativos do vetor de dados 
    data_stream[len-1] ^= 0xFF;
    data_stream[len-2] ^= 0xFF; 

    //cálculo do CRC {trocar para o vetor data_stream e ver o resultado}

    for (size_t i = 0; i < len; i++) {
        printf("------------------------------------\n Byte %ld\n", i);
        crc ^= (uint16_t)data_stream[i] << 8;
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

