#include<iostream>
using namespace std;

int main() {
    int x = 13;
    int steps = 0;
    int rmdr = x % 5;

    if(rmdr == 0){
        steps = x/5;
    } else {
        steps = x/5 + 1;
    }
    cout << steps;

    return 0;
}