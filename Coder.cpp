//
// Created by rober on 09.03.2023.
//

#include "Coder.h"

using namespace std;

void Coder::coding(int matrix_h[8][16], FILE *messageFile, FILE *encodedBinaryFile) {
    int sign, message[byte], parityArray[byte];

    while ((sign = fgetc(messageFile)) != EOF) {
        //zapełnienie tablicy parzystosci zerami
        fill_n(parityArray, byte, 0);

        //zamiana znaku ascii na binarny
        for (int i = byte - 1; i >= 0; i--) {
            message[i] = sign % 2;
            sign = sign / 2;
        }

        //sprawdzanie parzystosci kodu
        for (int i = 0; i < byte; i++) {
            for (int j = 0; j < byte; j++) {
                parityArray[i] += message[j] * matrix_h[i][j];
            }
            parityArray[i] %= 2;
        }

        //zapis znaku w binarny do pliku
        for (int i = 0; i < byte; i++) {
            fputc(message[i] + 48, encodedBinaryFile);
        }

        //dodanie bitow parzystoci
        for (int i = 0; i < byte; i++) {
            fputc(parityArray[i] + 48, encodedBinaryFile);
        }

        //nowa linia w pliku
        fputc('\n', encodedBinaryFile);
    }
}

void Coder::decoding(int matrix_h[8][16], FILE *encodedBinaryFile, FILE *decodedAsciiFile) {
    int encodedSignArray[byte * 2];
    int errorsArray[byte];
    int sign, counter = 0, signCounter = 1, errorsCounter = 0;

    while ((sign = fgetc(encodedBinaryFile)) != EOF) {
        //pominiecie znaku nowej linii
        if (sign != '\n') {
            //zapisanie kodu w tablicy jako int
            encodedSignArray[counter] = sign - 48;
            counter++;
        } else {
            int firstErrorIndex;
            int secondErrorIndex;

            //zapełnienie tablicy bledow zerami
            fill_n(errorsArray, byte, 0);

            for (int i = 0; i < byte; i++) {
                for (int j = 0; j < (byte * 2); j++) {
                    //mnozenie macierzy T oraz zakodowanego znaku
                    errorsArray[i] += encodedSignArray[j] * matrix_h[i][j];
                }
                errorsArray[i] %= 2;

                //sprawdzenie czy znaleziono jeden blad
                if (errorsArray[i] == 1) {
                    errorsCounter = 1;
                }
            }

            //naprawa bledow, jesli sie pojawily
            if (errorsCounter != 0) {
                int numberOfErrors = 1;
                for (int i = 0; i < (byte * 2 - 1); i++) {
                    for (int j = i + 1; j < (byte * 2); j++) {
                        numberOfErrors = 2;
                        for (int k = 0; k < byte; k++) {
                            if (errorsArray[k] != (matrix_h[k][i] ^ matrix_h[k][j])) {
                                numberOfErrors = 1;
                                break;
                            }
                        }

                        //jesli 2 bledy to zmiana wartosci na odpowiednim indeksie
                        if (numberOfErrors == 2) {
                            firstErrorIndex = i;
                            secondErrorIndex = j;

                            encodedSignArray[firstErrorIndex] = !encodedSignArray[firstErrorIndex];
                            encodedSignArray[secondErrorIndex] = !encodedSignArray[secondErrorIndex];
                            i = 15;
                            break;
                        }
                    }
                }

                //naprawa jednego bledu
                if (numberOfErrors == 1) {
                    for (int i = 0; i < (byte * 2); i++) {
                        for (int j = 0; j < byte; j++) {
                            if (matrix_h[j][i] != errorsArray[j]) { break; }

                            //zmiana wartosci na odpowiednim indeksie
                            if (j == 7) {
                                encodedSignArray[i] = !encodedSignArray[i];
                                i = 16;
                            }
                        }
                    }
                }
            }
            counter = 0;
            signCounter++;
            errorsCounter = 0;


            //zamiana kodu na znaki ascii i wpisanie ich do pliku
            int binaryValue = 128;
            char decodedSign = 0;
            for (int i = 0; i < byte; i++) {
                decodedSign += binaryValue * encodedSignArray[i];
                binaryValue /= 2;
            }

            fputc(decodedSign, decodedAsciiFile);
        }
    }

}
