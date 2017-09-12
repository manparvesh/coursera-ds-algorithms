#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

#define pb push_back

string InverseBWT(const string& bwt) {
    string text = "";

    // write your code here
    vector<string> v(bwt.length(), "");
    int x = bwt.length();
    while (x--) {
        for (int i = 0; i < bwt.length(); i++) {
            v[i] = bwt[i] + v[i];
        }
        sort(v.begin(), v.end());
    }

    text = v[0];
    text.erase(text.begin(), text.begin() + 1);
    text += '$';

    return text;
}

int main() {
    string bwt;
    cin >> bwt;
    cout << InverseBWT(bwt) << endl;
    return 0;
}
