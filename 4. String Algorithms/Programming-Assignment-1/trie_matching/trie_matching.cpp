#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

using std::vector;
using std::string;

struct edge;

struct node {

  public:
    node(int i) {
        index = i;
    }
    int index;
    vector<edge> edges;

    bool is_leaf() {return edges.empty();}
};

struct edge {
  public:
    edge(char ch, node* next) {
        symbol = ch;
        nextNode = next;
    }
    char symbol;
    node* nextNode;
};

void create_new_edge(char currentSymbol, int &index, node *&currentNode);

edge * is_there_edge(node *node, char symbol) {
    edge* result = nullptr;
    for (int i = 0; i < node->edges.size(); ++i) {
        if (node->edges.at(i).symbol == symbol) {
            result = &(node->edges.at(i));
            break;
        }
    }
    return result;
}

node* build_trie(vector<string> & patterns) {
    int index = 0;
    node* root = new node(index);
    edge* foundEdge = nullptr;
    for (int i = 0; i < patterns.size(); ++i) {
        node *currentNode = root;
        auto pattern = patterns.at(i);
        for (int j = 0; j < pattern.size(); ++j) {
            char currentSymbol = pattern.at(j);
            if (currentNode->edges.empty()) {
                create_new_edge(currentSymbol, index, currentNode);
            } else if ( (foundEdge = is_there_edge(currentNode, currentSymbol)) != nullptr ) {
                currentNode = foundEdge->nextNode;
                foundEdge = nullptr;
            } else {
                create_new_edge(currentSymbol, index, currentNode);
            }
        }
    }
    return root;
}

void create_new_edge(char currentSymbol, int &index, node *& currentNode) {
    auto newOne = new node(++index);
    edge e(currentSymbol, newOne);
    currentNode->edges.push_back(e);
    currentNode = newOne;
}


vector<string> read_patterns() {
    string line;
    vector<string> patterns;
    ifstream file("sample3");
    if (file.is_open()) {
        getline(file, line);
        while (getline(file, line)) {
            patterns.push_back(line);
        }
        file.close();
    }
    return patterns;
}

void print_tree(node* root) {
    if (root == nullptr || root->is_leaf()) {
        return;
    }
    for (int i = 0; i < root->edges.size(); ++i) {
        auto edge = root->edges.at(i);
        std::cout << root->index << "->" << edge.nextNode->index << ":" << edge.symbol << "\n";
        print_tree(edge.nextNode);
    }
}

void clean_up(node* root) {
    if (root == nullptr) {
        return;
    }
    if (root->is_leaf()) {
        delete  root;
        return;
    }
    for (int i = 0; i < root->edges.size(); ++i) {
        clean_up(root->edges.at(i).nextNode);
    }
    delete root;
}


void construct_trie() {

    vector<string> patterns = read_patterns();

    node* t = build_trie(patterns);

    print_tree(t);

    clean_up(t);
}

string read_data(vector<string>& patterns) {
    string text;
    string count;
    getline(cin, text);
    getline(cin, count);
    string line;
    while (getline(cin, line)) {
        patterns.push_back(line);
    }
    return text;
}

int prefix_trie_matching(string& text, int startSymbolIndex, node* root) {
    node* currentNode = root;
    int initIndex = startSymbolIndex;
    char currentSymbol = text.at(initIndex);

    edge* foundEdge = nullptr;
    while (true) {
        if (currentNode->is_leaf()) {
            return initIndex;
        } else if ((foundEdge = is_there_edge(currentNode, currentSymbol)) != nullptr) {
            currentNode = foundEdge->nextNode;
            currentSymbol = (++startSymbolIndex < text.size()) ?  text.at(startSymbolIndex) : '\0';
            foundEdge = nullptr;
        } else {
            return -1;
        }
    }
}

vector<int> trie_matching(string& text, node* root) {
    vector<int> results;
    for (int i = 0; i < text.size(); ++i) {
        auto result = prefix_trie_matching(text, i, root);
        if (result > -1) {
            results.push_back(result);
        }
    }
    return results;
}

void matching() {
    vector<string> patterns;
    string text = read_data(patterns);
    node* root_trie = build_trie(patterns);
    auto results = trie_matching(text, root_trie);

    for (int i = 0; i < results.size(); ++i) {
        cout << results.at(i) << "\n";
    }

    clean_up(root_trie);
}

int main() {
    // construct_trie();

    matching();


    return 0;
}