#include <iostream>

#include <memory>
#include <limits>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstring>

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


void catchAndTry(int &var) {
    int testValue;
    cin >> testValue;
    while (testValue != 1 && testValue != 2) {
        cout << "Nieprawidlowa wartosc, sprobuj jeszcze raz:";
        cin >> testValue;
    }
    var = testValue;
}

void chooseProgramMode(int &choice) {

	cout<<"Autorzy:\tRobert Laski 242456 \tKacper Pietrzak 242495\n";
    cout << "Przed uruchomieniem programu należy uzupełnić message.txt.\n"
    << "Wybierz tryb programu: \n"
    << "1. Kodowanie pliku\n"
    << "2. Odkodowywanie pliku\n"
    << "Wybor: ";
    catchAndTry(choice);
}

int main() {

    shared_ptr<MistakeDetectionCorrection> mistakeDetectionCorrection = make_shared<MistakeDetectionCorrection>();
    int choice;
    string fileName;
    fstream streamFile;
    chooseProgramMode(choice);
    switch (choice) {
        case 1: {

            fileName = "message.txt";
            char file[15];
            strcpy(file, fileName.c_str());
            FILE *toEncrypt;
            toEncrypt = fopen(file, "r");

            if (toEncrypt == nullptr) {
                cout << "Blad pliku (sprawdz czy posiada zawartosc)";
                exit(0);
            }

            FILE *code = fopen("coded.txt", "w");
            FILE *code2 = fopen("coded2.txt", "w");
            mistakeDetectionCorrection->coding(martix_H, toEncrypt, code, code2);

            fclose(toEncrypt);
            fclose(code);
            fclose(code2);

            break;
        }
        case 2: {

            FILE *encoded = fopen("coded.txt", "r");
            FILE *decoded = fopen("decoded.txt", "w");
            mistakeDetectionCorrection->checkCorrectness(martix_H, encoded, decoded);
            cout << "\nPlik odkodowany poprawnie\n";
            fclose(encoded);
            fclose(decoded);

            break;
        }
    }
    return 0;
}