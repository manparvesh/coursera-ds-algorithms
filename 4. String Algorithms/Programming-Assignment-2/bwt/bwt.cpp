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

string BWT(const string& s) {
    string result = "";

    // write your code here
    vector<string> v;
    string t = s;
    v.pb(t);
    char last_char;
    for (int i = 0; i < s.length() - 1; i++) {
        last_char = t.back();
        t.pop_back();
        t.insert(t.begin(), last_char);
        v.pb(t);
    }

    sort(v.begin(), v.end());

    for (int i = 0; i < v.size(); i++) {
        result += v[i].back();
    }

    return result;
}

int main() {
    string text;
    cin >> text;
    cout << BWT(text) << endl;
    return 0;
}