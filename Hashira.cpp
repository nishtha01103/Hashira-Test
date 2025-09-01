#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cctype>
#include <iomanip>
using namespace std;

// Convert a string in given base to decimal
long long convertToDecimal(const string &s, int base) {
    long long val = 0;
    for (char c : s) {
        int digit;
        if (isdigit(c)) digit = c - '0';
        else if (isalpha(c)) digit = 10 + (tolower(c) - 'a');
        else continue;
        val = val * base + digit;
    }
    return val;
}

// Lagrange interpolation → only constant term
long double lagrangeConstant(const vector<long double> &x, const vector<long double> &y) {
    int n = x.size();
    long double constantTerm = 0.0;

    for (int i = 0; i < n; i++) {
        long double term = y[i];
        long double denom = 1.0;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            term *= (-x[j]);
            denom *= (x[i] - x[j]);
        }
        constantTerm += term / denom;
    }
    return constantTerm;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read JSON input
    string input, line;
    while (getline(cin, line)) {
        input += line;
    }

    // Extract n and k
    size_t posN = input.find("\"n\"");
    size_t posK = input.find("\"k\"");
    int n = stoi(input.substr(input.find(":", posN)+1));
    int k = stoi(input.substr(input.find(":", posK)+1));

    vector<long double> x, y;
    int count = 0;

    // Parse roots until we get k values
    for (int idx = 1; idx <= n && count < k; idx++) {
        string key = "\"" + to_string(idx) + "\"";
        size_t pos = input.find(key);
        if (pos == string::npos) continue;

        // Base
        size_t posBase = input.find("\"base\"", pos);
        size_t startBase = input.find("\"", posBase+7) + 1;
        size_t endBase = input.find("\"", startBase);
        int base = stoi(input.substr(startBase, endBase - startBase));

        // Value
        size_t posVal = input.find("\"value\"", pos);
        size_t start = input.find("\"", posVal+7) + 1;
        size_t end = input.find("\"", start);
        string valStr = input.substr(start, end - start);

        long long val = convertToDecimal(valStr, base);

        x.push_back(idx); // root index
        y.push_back(val); // converted value
        count++;
    }

    // Compute constant term
    long double c = lagrangeConstant(x, y);

   cout << "Constant term (c) = " << c << "\n";
    return 0;
}
