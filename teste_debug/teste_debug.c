#include <stdio.h>
#include <stdint.h>

int main (void){
    uint8_t vetor[2] = {0xFF, 0xAA};
    
    for (int count = 0; count < 16; count++){
        vetor[1] <<= 1;
        printf ("vetor: 0x%X 0x%X\n", vetor[1], vetor[0]);
    }
}