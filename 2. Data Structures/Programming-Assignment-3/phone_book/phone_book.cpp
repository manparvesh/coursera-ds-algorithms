#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<Query> contacts;
    map<int, string> phonebook;
    for (size_t i = 0; i < queries.size(); ++i) {
        int num = queries[i].number;
        if (queries[i].type == "add") {
            bool was_founded = false;
            // if we already have contact with such number,
            // we should rewrite contact's name
            if (phonebook.find(num) != phonebook.end()) {
                phonebook[num] = queries[i].name;
            } else {
                // otherwise, just add it
                phonebook[num] = queries[i].name;
            }
        } else if (queries[i].type == "del") {
            if (phonebook.find(num) != phonebook.end()) {
                phonebook.erase(phonebook.find(num));
            }
        } else {
            string response = "not found";
            if (phonebook.find(num) != phonebook.end()) {
                response = phonebook[num];
            }
            result.push_back(response);
        }
    }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
