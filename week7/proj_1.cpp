#include <iostream>
#include <queue>
#include <cstdlib>
#include <cstdio>
using namespace std;

struct point {
    string mName;
    int mDegree;
    point( ) { };
    point(string &str, int degree):mName(str), mDegree(degree){ }
} _point;

struct treeNode {
    string value;
    treeNode *leftMostChild;
    treeNode *rightSilbling;
    int degree;
    treeNode():degree(0), leftMostChild(NULL), rightSilbling(NULL){ };
} node;

treeNode *createTree(queue<point> &q)
{
    queue<treeNode*> subroots;
    treeNode *root = new treeNode;
    treeNode *ret = root;
    point current = q.front();
    root->degree = current.mDegree;
    root->value = current.mName;
    q.pop();
    subroots.push(root);
    treeNode *sroot;
    while (!q.empty()) {
        sroot = subroots.front();
        subroots.pop();
        int degree = sroot->degree;
        if (degree) {
            current = q.front();
            q.pop();
            treeNode *left = new treeNode;
            left->degree = current.mDegree;
            left->value = current.mName;
            subroots.push(left);
            sroot->leftMostChild = left;
            sroot = sroot->leftMostChild;
            for (int i = 0; i < degree-1; ++i) {
                current = q.front();
                q.pop();
                treeNode *right = new treeNode;
                right->degree = current.mDegree;
                right->value = current.mName;
                subroots.push(right);
                sroot->rightSilbling = right;
                sroot = sroot->rightSilbling;
            }
        }
    }
    return ret;
}

treeNode *createBinaryTree(queue<treeNode*> &forest)
{
    treeNode *root = forest.front();
    treeNode *subroot = root;
    treeNode *current;
    forest.pop();
    while (!forest.empty()) {
        current = forest.front();
        forest.pop();
        subroot->rightSilbling = current;
        subroot = subroot->rightSilbling;
    }
    return root;
}

void freeTree(treeNode *root)
{
    if (root->leftMostChild)
        freeTree(root->leftMostChild);
    if (root->rightSilbling)
        freeTree(root->rightSilbling);
    delete root;
}

void inorderTraverseBinaryTree(treeNode *root)
{
    if (root->leftMostChild)
        inorderTraverseBinaryTree(root->leftMostChild);
    cout << root->value << " ";
    if (root->rightSilbling)
        inorderTraverseBinaryTree(root->rightSilbling);
}

int main(int argc, char *argv[])
{
    int n;
    cin >> n;
    getchar();
    
    char ch;
    int degree = 0;
    string degreeValue;
    string nodeValue;
    
    queue<treeNode*> forest;
    
    while (n--) {
        int parseValue = 1;
        int parseDegree = 0;
        queue<point> q;
        while (true) {
            ch = getchar();
            if (ch == '\n'){
                degree = atoi(degreeValue.c_str());
                q.push(point(nodeValue, degree));
                nodeValue.clear();
                degreeValue.clear();
                break;
            }
            if (ch == ' ') {
                if (parseValue) {
                    parseValue = 0;
                    parseDegree = 1;
                } else {
                    parseDegree = 0;
                    parseValue = 1;
                    degree = atoi(degreeValue.c_str());
                    q.push(point(nodeValue, degree));
                    nodeValue.clear();
                    degreeValue.clear();
                }
                continue;
            }
            if (parseValue)
                nodeValue.push_back(ch);
            else
                degreeValue.push_back(ch);
        }
        treeNode *tmp = createTree(q);
        forest.push(tmp);
    }
    
    treeNode *root = createBinaryTree(forest);
    inorderTraverseBinaryTree(root);
    cout << endl;
    freeTree(root);
    return 0;
}

