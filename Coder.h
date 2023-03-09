//
// Created by rober on 09.03.2023.
//

#ifndef TELEKOMUNA__CODER_H
#define TELEKOMUNA__CODER_H

#include <iostream>
//#include <stdio.h>
#include <cstdlib>
//#include <string.h>

class Coder {
    const int byte = 8;
public:
    void coding(int matrix_h[8][16], FILE *messageFile, FILE *encodedBinaryFile);

    void decoding(int matrix_h[8][16], FILE *encodedBinaryFile, FILE *decodedAsciiFile);
};


#endif //TELEKOMUNA__CODER_H
