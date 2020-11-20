#include "MineSweeper.h"
#include <iostream>

using namespace std;

int main() {
    class MineSweeper ms;

    while (1) {
        cout << "1. Start Mine Sweeper" << endl;
        cout << "2. Exit" << endl;

        int num = 0;
        cout << ">> ";
        cin >> num;

        if (num == 1) {
            cout << "Start Mine Sweeper" << endl;
            ms.StartMineSweeper();
            cout << "End Mine Sweeper" << endl;
        } else if (num == 2) {
            break;
        }

        cout << endl;
    }

    return 0;
}
