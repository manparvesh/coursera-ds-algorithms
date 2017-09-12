#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

struct suffix {
    int index;
    int rank[2];
};

int cmp(suffix a, suffix b) {
    return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1]) :
           (a.rank[0] < b.rank[0]);
}

vector<int> BuildSuffixArray(const string& text) {
    vector<int> result;
    // Implement this function yourself

    int n = text.length();
    suffix ss[n];

    for (int i = 0; i < n; i++) {
        ss[i].index = i;
        ss[i].rank[0] = text[i] - 'a';
        ss[i].rank[1] = i + 1 < n ? text[i + 1] - 'a' : -1;
    }

    // sort suffixes using comparator function
    sort(ss, ss + n, cmp);

    // sorted by first 2 characters. now we move to 4, 8, 16...
    int ind[n];

    for (int k = 4; k < 2 * n; k *= 2) {
        int rank = 0;
        int prev_rank = ss[0].rank[0];
        ss[0].rank[0] = rank;
        ind[ss[0].index] = 0;

        // update ranks
        for (int i = 1; i < n; i++) {
            // if first and next ranks are same as that of previous
            // suffix in array, assign the same new rank to this suffix
            if (ss[i].rank[0] == prev_rank &&
                    ss[i].rank[1] == ss[i - 1].rank[1]) {
                prev_rank = ss[i].rank[0];
                ss[i].rank[0] = rank;
            } else {
                prev_rank = ss[i].rank[0];
                ss[i].rank[0] = ++rank;
            }
            ind[ss[i].index] = i;
        }

        // assign next rank
        for (int i = 0; i < n; i++) {
            int next_index = ss[i].index + k / 2;
            ss[i].rank[1] = next_index < n ? ss[ind[next_index]].rank[0] : -1;
        }

        // sort again using our comparator
        sort(ss, ss + n, cmp);
    }

    for (int i = 0; i < n; i++) {
        result.push_back(ss[i].index);
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
