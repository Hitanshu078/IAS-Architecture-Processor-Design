#include <bits/stdc++.h>

using namespace std;
long long nPr(int n, int r) {
    if (n < r) {
        printf("Invalid input");
        return 0;
    }

    long long result = 1;


    for (int i = 0; i < r; ++i) {
        result *= (n - i);
    }

    return result;
}

int main() {
    int n, r;

    cout << "Enter the value of n and r: ";
    cin >> n >> r;
    


    // Calculate and print NPR
    cout << "Permutations(" << n << ", " << r << ") = " << nPr(n, r) << endl;

    return 0;
}