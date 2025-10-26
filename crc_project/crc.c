#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

const size_t bytes = 5;
uint8_t data[5] = {0x0B, 0x0F, 0x02, 0x00, 0x80};

void shift_left_array(uint8_t* vetor, size_t tamanho) {
    uint8_t carry_out = 0x00; // O bit de transporte que "sai" de um byte
    // O 'carry_in' inicial se torna o 'carry' para o primeiro elemento (vetor[0])
    uint8_t carry = 0x00; 

    for (size_t i = 0; i < tamanho; i++) {
        // 1. Guarda o MSB do byte atual. Ele será o 'carry' para o *próximo* byte.
        //    (vetor[i] & 0x80) -> 0x80 se o MSB for 1, 0x00 se for 0
        //    >> 7             -> 1 se o MSB for 1, 0 se for 0
        carry_out = (vetor[i] & 0x80) >> 7;

        // 2. Desloca o byte atual 1 bit para a esquerda
        vetor[i] <<= 1;

        // 3. Aplica o 'carry' (vindo do byte anterior) no LSB do byte atual
        vetor[i] |= carry;

        // 4. Prepara o 'carry' para a *próxima* iteração
        carry = carry_out;
    }

    // O último 'carry' (MSB do último byte) é o bit que "saiu" do vetor
}

void bit_stream (const uint8_t* data, uint8_t* data_out, size_t len){ 

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
        data_out[h] = interm; //alocando o byte invertido no vetor final
    }
}

uint16_t calculate_crc16(const uint8_t* data, size_t len, bool flag_verif) {
    uint16_t crc = 0x0000;
    const uint8_t poly[3] = {0x80, 0x02, 0xC0}; //armazena o polinômio (0xC002 [0b1000 0000]) em um vetor de 3 bytes
    uint8_t data_func[len]; //Não precisa dessa variável, depois de terminar a função, deletar
    uint8_t data_stream[len];
    size_t len_data;

    if (flag_verif){
        len_data = len - 2;
    }
    else{
        len_data = len;
    }

    //inicializando os vetores
    for (size_t h = 0; h < len; h++){
        data_func[h] = data[h];
    }

    //Definindo vetor em ordem bit stream (calculando byte por byte) {funciona}
    bit_stream(&data[0], &data_stream[0], len);

    //XOR entre 0XFFFF e os dois bytes mais significativos do vetor de dados 
    data_stream[len-1] ^= 0xFF;
    data_stream[len-2] ^= 0xFF; 

    //cálculo do CRC 
    
    for (size_t i = 0; i < 8*len_data; i++){
        //caso o bit mais significativo seja 1
        if (data_stream[len-1] & 0x80){
            //xor com o polinômio (byte a byte)        
            data_stream[len - 1] ^= poly[2];
            data_stream[len - 2] ^= poly[1];
            data_stream[len - 3] ^= poly[0];

            //deslocando todos os bits do vetor uma casa para a esquerda 
            shift_left_array(data_stream, len);
        }
        //caso o bit mais significativo seja zero (nesse caso apenas será feito o deslocamento do vetor)
        else {
            shift_left_array(data_stream, len);
        }
    }

    bit_stream(&data_stream[len-2], &data_stream[len-2], len);

    crc = ((uint16_t)data_stream[len-1] << 8) + (uint16_t)data_stream[len-2]; 
    printf ("CRC calculado: 0X%X\n", crc);
    return crc;
}

void main (void){    
    uint16_t result_crc;
    uint16_t verif;
    uint8_t verif_array[7] = {0x29, 0xC0, 0x0B, 0x0F, 0x02, 0x00, 0x80};

    result_crc = calculate_crc16(&data[0], bytes, 0);
    verif = calculate_crc16(&data[0], bytes + 2, 1);
    printf("fim\n");
}

void shift_left_array(uint8_t* vetor, size_t tamanho);
void bit_stream (const uint8_t* data, uint8_t* data_out, size_t len);
uint16_t calculate_crc16(const uint8_t* data, size_t len, bool flag_verif);
