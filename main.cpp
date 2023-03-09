#include <iostream>
#include "Coder.h"
#include <memory>
#include <algorithm>
#include <string>

using namespace std;

//MACIERZ KONTROLNA
int martix_H[8][16] = {
        {1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        {1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0},
        {1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1}};



int chooseProgramMode() {
    int testValue;

    cout << "Autorzy:\tRobert Laski 242456 \tKacper Pietrzak 242495\n";
    cout << "Przed uruchomieniem programu należy uzupełnić message.txt.\n"
         << "Wybierz tryb programu: \n"
         << "1. Kodowanie pliku\n"
         << "2. Odkodowywanie pliku\n"
         << "Wybor: ";
    cin >> testValue;

    while (testValue != 1 && testValue != 2) {
        cout << "Nieprawidlowa wartosc, sprobuj jeszcze raz:";
        cin >> testValue;
    }
    return testValue;
}

int main() {

    shared_ptr<Coder> coder = make_shared<Coder>();
    int choice = chooseProgramMode();
    switch (choice) {
        case 1: {
            FILE *toEncrypt = fopen("message.txt", "r");

            if (toEncrypt == nullptr) {
                cout << "Blad pliku (sprawdz czy posiada zawartosc)";
                exit(0);
            }

            FILE *code = fopen("coded.txt", "w");
            coder->coding(martix_H, toEncrypt, code);

            fclose(toEncrypt);
            fclose(code);

            break;
        }
        case 2: {

            FILE *encoded = fopen("coded.txt", "r");
            FILE *decoded = fopen("decoded.txt", "w");
            coder->decoding(martix_H, encoded, decoded);
            cout << "\nPlik odkodowany poprawnie\n";
            fclose(encoded);
            fclose(decoded);

            break;
        }
    }
    return 0;
}