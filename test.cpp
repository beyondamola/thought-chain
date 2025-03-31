#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

int main() {
/*string line = "";
    ifstream file("chain_of_thought.txt");

    if (!file.is_open()) {
        cerr << "Failed to open file.\n";
        return 1;
    }

    while (getline(file, line)) {
        cout << line << "\n";
    }

    file.close();*/
    cout << "Looking in: " << filesystem::current_path() << endl;
}

