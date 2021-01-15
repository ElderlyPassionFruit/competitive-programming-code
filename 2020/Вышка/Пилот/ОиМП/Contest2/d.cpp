#include <iostream>
#include <map>
#include <string>

using namespace std;

struct Node{
    map<string, Node*> edges;
    Node() {
        edges = {};
    }
};

void addPath(const string& path, string::size_type startPos, Node* rootOfPrefixTree) {
    auto endPos = path.find('/', startPos + 1);
    if (endPos == string::npos) {
        return;
    }
    string directoryName = path.substr(startPos + 1, endPos - startPos - 1);
    if (!rootOfPrefixTree->edges.count(directoryName)) {
        rootOfPrefixTree->edges[directoryName] = new Node();
    }
    addPath(path, endPos, rootOfPrefixTree->edges[directoryName]);
}

void printPrefixTree(string path, Node* rootOfPrefixTree) {
    cout << path << "\n";
    for (auto [addPath, nextNode] : rootOfPrefixTree->edges) {
        printPrefixTree(path + addPath + "/", nextNode);
    }
}

int main() {
    Node* rootOfPrefixTree = new Node();
    string path;
    while (cin >> path) {
        addPath(path, path.find('/'), rootOfPrefixTree);
    }
    printPrefixTree("/", rootOfPrefixTree);
    return 0;
}
