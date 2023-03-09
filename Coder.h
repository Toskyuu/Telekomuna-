#ifndef TELEKOMUNA__CODER_H
#define TELEKOMUNA__CODER_H

#include <iostream>
#include <cstdlib>


class Coder {
    const int byte = 8;
    const int matrix_h[8][16] = {
            {0, 1, 1, 1, 1, 1, 1, 1,	1, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 1, 1, 1, 1, 1, 1,	0, 1, 0, 0, 0, 0, 0, 0},
            {1, 1, 0, 1, 1, 0, 1, 1,	0, 0, 1, 0, 0, 0, 0, 0},
            {1, 1, 1, 0, 0, 1, 0, 1,	0, 0, 0, 1, 0, 0, 0, 0},
            {1, 1, 1, 1, 0, 1, 1, 0,	0, 0, 0, 0, 1, 0, 0, 0},
            {0, 1, 0, 1, 1, 0, 1, 1,	0, 0, 0, 0, 0, 1, 0, 0},
            {1, 1, 1, 0, 1, 1, 0, 1,	0, 0, 0, 0, 0, 0, 1, 0},
            {1, 0, 1, 1, 1, 1, 1, 0,	0, 0, 0, 0, 0, 0, 0, 1},
    };
public:
    void coding(FILE *messageFile, FILE *encodedBinaryFile);

    void decoding(FILE *encodedBinaryFile, FILE *decodedAsciiFile);
};


#endif //TELEKOMUNA__CODER_H
