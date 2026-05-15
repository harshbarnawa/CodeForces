#include <iostream>
#include <string>
using namespace std;
 
int main() {
    int n;
    cin >> n;
    
    while (n--) {
        string wd;
        cin >> wd;
 
        if (wd.length() > 10) {
            cout << wd[0]<< wd.length() - 2 << wd[wd.length() - 1] << endl;
        } else {
            cout << wd << endl;
        }
    }
 
    return 0;
}