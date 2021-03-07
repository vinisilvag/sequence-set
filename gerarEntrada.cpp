#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  srand((unsigned)time(NULL));

  ofstream myfile("entradas.dat");

  string search[20];

  for (int i = 0; i < 100; i++) {
    string text;

    for (int i = 0; i < 6; i++) {
      char letter = 97 + rand() % 26;

      text += letter;
    }

    if (i < 20) {
      search[i] = text;
    }

    unsigned tdp = rand() % 1000;

    float cinebench = rand() % 120;

    myfile << "i " << i + 1 << " " << text << " " << text << " " << tdp << " "
           << text << " " << text << " " << cinebench << " " << cinebench << " "
           << cinebench << endl;
  }

  for (int i = 0; i < 20; i++) {
    myfile << "b " << search[i] << endl;
  }

  myfile << "p" << endl << "d";

  myfile.close();

  return 0;
}