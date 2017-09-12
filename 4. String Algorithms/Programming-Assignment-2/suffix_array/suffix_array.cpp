#include <bits/stdc++.h>
using namespace std;


// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(const string& text) {
    vector<int> result;
    // Implement this function yourself

    std::vector<pair<string, int>> v;
    for (int i = 0; i < text.length(); i++) {
        v.push_back(make_pair(text.substr(i), i));
    }

    sort(v.begin(), v.end());
    for (auto i : v) {
        result.push_back(i.second);
    }

    return result;
}

int main() {
    string text;
    cin >> text;
    vector<int> suffix_array = BuildSuffixArray(text);
    for (int i = 0; i < suffix_array.size(); ++i) {
        cout << suffix_array[i] << ' ';
    }
    cout << endl;
    return 0;
}
