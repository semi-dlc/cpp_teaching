#include<iostream>

using namespace std;

int main() {
    long long int* p = new long long int(42);

    for (long long int i = 1; i < 10000000000; i += 1) {

        delete p;
        p = new long long int(i);

        if (i % 10000000 == 0) {
            cout << *p << endl;
        }
    }

    char c;
    while(cin>>c) {
        cout << c << endl;
        return 0;
    }

}