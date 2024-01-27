#include"start.hpp"




int main(int argc, char* argv[]) {
    using namespace std;
    int frequency[128];
    for (int i = 0; i < 128; i++){
    frequency[i] = 0;
    }
    char* filename;
    bool printit = false;
    cout << "Shall the process be printed on the screen? 0 for false, 1 for true" << endl;
    cin >> printit;

    if (argc > 2) {
        cerr << "Only one program parameter - filename" << endl;
    }
    if (argc == 2) {
    filename = argv[1];
    }
    else if (argc == 1) {
        filename = "42.txt";
        cout << "Enter optional filename. Filename must be longer than one character. Press 0 otherwise" << endl;
        string s = "";
        cin >> s;
        if (s.length() > 1) {
            filename = const_cast<char*>(s.c_str());
        }
        
    }
    chrono::steady_clock::time_point begint = std::chrono::steady_clock::now();

    ifstream reading;
    reading.open(filename);


    /*

    if (!reading.is_open()) {
            std::cerr << "Failed to open the file." << std::endl;
            return 1; // Exit the program with an error
        }
    */

    char temp;
    while(reading >> temp) {
        if (not(int(temp) < 129 && int(temp) >= 0)) {
            continue;
        } 
        frequency[temp]++;

        if (printit) {cout << temp << endl;}

        
    }
    reading.close();
    

    ofstream writing;
    const char* outlog = "out.log";
    writing.open(outlog);

    for (int i = 31; i < 128; i++) {
        if(printit) {cout << " " << static_cast<unsigned char>(i) << " " << ": " << frequency[i] << endl;}
        writing << " " << static_cast<unsigned char>(i) << " " << ": " << frequency[i] << endl;
    }

    chrono::steady_clock::time_point endt = std::chrono::steady_clock::now();

    if (chrono::duration_cast<std::chrono::milliseconds>(endt - begint).count() != 0) {
        if(printit) {cout << "Amount of time = " << chrono::duration_cast<std::chrono::milliseconds>(endt - begint).count() << "[ms]" << std::endl;}
        writing << "Amount of time = " << chrono::duration_cast<std::chrono::milliseconds>(endt - begint).count() << "[ms]" << std::endl;
    }
    else {
        if(printit) {cout << "Amount of time = " << chrono::duration_cast<std::chrono::microseconds>(endt - begint).count() << "[micros]" << std::endl;}
            writing << "Amount of time = " << chrono::duration_cast<std::chrono::microseconds>(endt - begint).count() << "[micros]" << std::endl;   
    }

    writing.close();

    return 0;
}