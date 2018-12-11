#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
using namespace std;

struct treeNode {
    char value;
    char position;
    treeNode *left;
    treeNode *right;
    treeNode *parent;
    treeNode(char v, char p):value(v), position(p), left(NULL), right(NULL), parent(NULL){ };
};

struct point {
    char value;
    char position;
    point(char v, char p):value(v), position(p){ };
};

treeNode *createTree(queue<point> &q)
{
    point current = q.front();
    q.pop();
    treeNode *root = new treeNode(current.value, current.position);
    treeNode *sroot;
    stack<treeNode*> subroots;
    subroots.push(root);
    while (!q.empty()) {
        current = q.front();
        q.pop();
        sroot = subroots.top();
        while (sroot->left && sroot->right) {
            subroots.pop();
            sroot = subroots.top();
        }
        if (!sroot->left) {
            sroot->left = new treeNode(current.value, current.position);
            sroot->left->parent = sroot;
            if (sroot->left->position != '1')
                subroots.push(sroot->left);
        } else {
            sroot->right = new treeNode(current.value, current.position);
            sroot->right->parent = sroot;
            if (sroot->right->position != '1')
                subroots.push(sroot->right);
        }
    }
    
    return root;
}


void levelOrderPrint(treeNode *root)
{
    vector<treeNode*> qu;
    stack<treeNode*> stk;
    treeNode *current;
    qu.push_back(root);
    int i = 0;
    while (i < qu.size()) {
        root = qu[i];
        if (root->left && root->left->value != '$') {
            current = root->left;
            stk.push(current);
            while (current->right && current->right->value != '$') {
                current = current->right;
                stk.push(current);
            }
        }
        while (!stk.empty()) {
            qu.push_back(stk.top());
            stk.pop();
        }
        i++;
    }
    
    for (int i = 0; i < qu.size(); ++i)
        cout << qu[i]->value << " ";
    cout << endl;
}

int main(int argc, char *argv[])
{
    int n;
    cin >> n;
    string tmp;
    queue<point> q;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        q.push(point(tmp[0], tmp[1]));
    }
    treeNode *root = createTree(q);
    levelOrderPrint(root);
    return 0;
}

