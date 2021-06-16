#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Node {
    char whoWin;
    long long possible;
};

void initTree(vector<Node>& tree, const string& str) {
    for (int i = str.size(); i > 0; --i) {
        tree[i].whoWin = str[str.size()-i];
        if (2*i+1 < tree.size()) {
            tree[i].possible = 0;
            if (tree[i].whoWin != '0') {
                tree[i].possible += tree[2*i].possible;
            }
            if (tree[i].whoWin != '1') {
                tree[i].possible += tree[2*i+1].possible;
            }
        } else {
            if (tree[i].whoWin == '?') {
                tree[i].possible = 2;
            } else {
                tree[i].possible = 1;
            }
        }
    }
}

void updateTree(vector<Node>& tree, const long long qIdx, const char qChar) {
    tree[qIdx].whoWin = qChar;
    for (int i = qIdx; i > 0; i = i/2) {
        if (2*i+1 < tree.size()) {
            tree[i].possible = 0;
            if (tree[i].whoWin != '0') {
                tree[i].possible += tree[2*i].possible;
            }
            if (tree[i].whoWin != '1') {
                tree[i].possible += tree[2*i+1].possible;
            }
        } else {
            if (tree[i].whoWin == '?') {
                tree[i].possible = 2;
            } else {
                tree[i].possible = 1;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int k;
    cin >> k;
    
    string str;
    cin >> str;
    vector<Node> tree(str.size()+1);
    initTree(tree, str);

    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        long long qIdx;
        char qChar;
        cin >> qIdx >> qChar;
        str[qIdx-1] = qChar;
        updateTree(tree, (long long)tree.size() - qIdx, qChar);
        cout << tree[1].possible << '\n';
    }
}