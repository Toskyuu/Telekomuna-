//
// Created by rober on 09.03.2023.
//

#include "Coder.h"

using namespace std;

void Coder::coding(int (*matrix_h)[16], FILE *messageFile, FILE *encodedBinaryFile) {
    int sign, message[byte], parityTable[byte];

    while ((sign = fgetc(messageFile)) != EOF) {
        //zapełnienie tablicy kontrolnej zerami
        fill_n(parityTable, byte, 0);

        //zamiana znaku ascii na binarny
        for (int i = byte - 1; i >= 0; i--) {
            message[i] = sign % 2;
            sign = sign / 2;
        }

        //sprawdzanie parzystosci kodu
        for (int i = 0; i < byte; i++) {
            for (int j = 0; j < byte; j++) {
                parityTable[i] += message[j] * matrix_h[i][j];
            }
            parityTable[i] %= 2;
        }

        //zapis znaku w binarny do pliku
        for (int i = 0; i < byte; i++) {
            fputc(message[i] + 48, encodedBinaryFile);
        }

        //dodanie bitow parzystoci
        for(int i = 0; i < byte; i++){
            fputc(parityTable[i] + 48, encodedBinaryFile);
        }

        //nowa linia w pliku
        fputc('\n', encodedBinaryFile);
    }
}

void Coder::decoding(int (*matrix_h)[16], FILE *encodedBinaryFile, FILE *decodedAsciiFile) {

}
