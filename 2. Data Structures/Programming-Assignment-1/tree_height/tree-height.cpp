#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Node {
  public:
    int value;
    std::vector<int> children;

    Node(int value) : value(value) {}

    void add_child(int child) {
        this->children.push_back(child);
    }

    int get_size() {
        return this->children.size();
    }
};

class Tree {
  private:
    int number_of_nodes;
    Node *root;
    std::vector<int> parents;
    std::map<int, Node *> nodes;

    void construct_tree() {
        for (int i = 0; i < this->number_of_nodes; i++) {
            this->nodes[i] = new Node(i);
        }

        for (int i = 0; i < this->number_of_nodes; i++) {
            int parent = this->parents[i];
            if (parent == -1) {
                // root node
                this->root = this->nodes[i];
            } else {
                // add child
                this->nodes[parent]->add_child(i);
            }
        }
    }

    int get_max_height(Node *node) {
        if (node == NULL) return 0; // this ain't shit
        if (node->get_size() == 0) return 1; // no children

        int height = 0;
        for (int i = 0; i < node->get_size(); i++) {
            int height_of_this_child = this->get_max_height(this->nodes[node->children[i]]);
            height = max(height, height_of_this_child);
        }

        return height + 1;
    }

  public:
    // deconstructor to delete memory allocated to nodes->
    ~Tree() {
        for (const auto &node : this->nodes) {
            delete node.second;
        }
    }

    // reading the tree
    void read() {
        cin >> this->number_of_nodes;
        this->parents.resize(this->number_of_nodes);
        for (int i = 0; i < this->number_of_nodes; i++) {
            cin >> this->parents[i];
        }
    }

    int get_height() {
        this->construct_tree();
        this->get_max_height(this->root);
    }

    void print_tree() {
        for (int i = 0; i < number_of_nodes; i++) {
            if (nodes.find(i) != nodes.end()) {
                cout << nodes[i]->value << ": ";
                for (int j = 0; j < nodes[i]->get_size(); ++j) {
                    cout << nodes[i]->children[j] << " ";
                }
                cout << endl;
            }
        }
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Tree *tree = new Tree();
    tree->read();
    // tree->print_tree();
    cout << tree->get_height() << endl;

    return 0;
}
