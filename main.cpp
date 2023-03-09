#include <iostream>
#include "Coder.h"
#include <memory>
#include <algorithm>
#include <string>

using namespace std;

int chooseProgramMode() {
    int testValue;

    cout << "Autorzy: Robert Laski 242456 \tKacper Pietrzak 242495\n";
    cout << "Przed uruchomieniem programu nalezy uzupelnic message.txt.\n"
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
    if (choice == 1) {
        FILE *toEncrypt = fopen("message.txt", "r");

        if (toEncrypt == nullptr) {
            cout << "Blad pliku (sprawdz czy posiada zawartosc)";
            return 1;
        }

        FILE *code = fopen("coded.txt", "w");
        coder->coding(toEncrypt, code);

        fclose(toEncrypt);
        fclose(code);

    }
    if (choice == 2) {
        FILE *encoded = fopen("coded.txt", "r");
        FILE *decoded = fopen("decoded.txt", "w");
        coder->decoding(encoded, decoded);
        cout << "\nPlik zostal odkodowany";
        fclose(encoded);
        fclose(decoded);
    }
    return 0;
}