#include <array>
#include <algorithm>
#include <iostream>
using namespace std;
int main() {
    array<int, 20> arr = {22, 25, 33, 34, 48, 
        53, 55, 67, 69, 71, 82, 85, 91, 96, 101, 
                            5, 9, 13, 17, 15};
    cout << "a. Todos los elementos:" << endl;
    for (auto x : arr) cout << x << " ";
    cout << endl;
    cout << endl << "b. Mayores que 20 y menores que 50:" << endl;
    for (auto x : arr) {
        if (x > 20 && x < 50) cout << x << " ";
    }
    cout << endl;
    sort(arr.begin(), arr.end());
    cout << endl << "c. Elementos ordenados:" << endl;
    for (auto x : arr) cout << x << " ";
    cout << endl;
    cout << endl << "d. Indices impares menores que 10:" << endl;
    for (int i = 1; i < 10; i += 2) {
        cout << "[" << i << "] = " << arr.at(i) << endl;
    }
    return 0;
}
