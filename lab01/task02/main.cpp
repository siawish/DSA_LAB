#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {

    ifstream inputFile("Input.txt");
    ofstream outputFile("Output.txt");

    if (!inputFile) {
        cerr << "Error opening Input.txt" << endl;
        return 1;
    }

    if (!outputFile) {
        cerr << "Error opening Output.txt" << endl;
        return 1;
    }

    string name;
    float m1, m2, final, avg;

    while (inputFile >> name >> m1 >> m2 >> final) {
        avg = (0.25 * m1) + (0.25 * m2) + (0.50 * final);
        outputFile << name << " " << m1 << " " << m2 << " " << final << " " << avg << endl;
    }

    cout << "\nData Saved Successfully\n";

    inputFile.close();
    outputFile.close();

    return 0;
}