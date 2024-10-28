#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    // Open the file
    ifstream inputFile("arrivingAnimals.txt");

    // Check if the file opened successfully
    if (!inputFile) {
        cerr << "Error opening file." << endl;
        return 1; // Exit with error code
    }

    string line;

    // Read the file line by line
    while (getline(inputFile, line)) {
        cout << line << endl; // Output each line
    }

    // Close the file
    inputFile.close();

    cout << "\nThis is my Zoo Challenge Project\n" << endl;


    return 0;
}
