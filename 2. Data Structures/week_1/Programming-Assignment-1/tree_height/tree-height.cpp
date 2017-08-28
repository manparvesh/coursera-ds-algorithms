#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif
using namespace std;

class Node;

class Node {
  public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
        this->parent = NULL;
    }

    void setParent(Node *theParent) {
        parent = theParent;
        parent->children.push_back(this);
    }
};

#define debug

int main_with_large_stack_space() {
    std::ios_base::sync_with_stdio(0);
    int n;
    std::cin >> n;

    vector<vector<int>> nds(n);
    int root = -1;

    for (int child_index = 0; child_index < n; child_index++) {
        int parent_index;
        std::cin >> parent_index;
        if (parent_index >= 0) {
            nds[parent_index].push_back(child_index);
        } else {
            root = child_index;
        }
    }

    // Replace this code with a faster implementation
    int maxHeight = 0;

    queue<int> q;
    q.push(root);
    q.push(-1);
    while (q.size()) {
        int temp_node = q.front();
#ifdef debug
        cout << "Front = " << temp_node << endl;
#endif
        q.pop();
        if (temp_node == -1) {
            maxHeight++;
#ifdef debug
            cout << "new height = " << maxHeight << endl;
#endif
        } else {
            for (int w = 0; w < nds[temp_node].size(); w++) {
                q.push(nds[temp_node][w]);
#ifdef debug
                cout << "Pushing " << nds[temp_node][w] << endl;
#endif
            }
            if (nds[temp_node].size()) {
                q.push(-1);
#ifdef debug
                cout << "Pushing " << -1 << endl;
#endif
            }
        }
    }

    std::cout << maxHeight << std::endl;
    return 0;
}

int main (int argc, char **argv) {
#if defined(__unix__) || defined(__APPLE__)
    // Allow larger stack space
    const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0) {
        if (rl.rlim_cur < kStackSize) {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0) {
                std::cerr << "setrlimit returned result = " << result << std::endl;
            }
        }
    }

#endif
    return main_with_large_stack_space();
}
