// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <algorithm>

struct Node {
    char val;
    std::vector<Node*> children;
    explicit Node(char v) : val(v) {}
    ~Node() {
        for (auto child : children) delete child;
    }
};

class PMTree {
public:
    std::vector<Node*> roots;
    PMTree(const std::vector<char>& in);
    ~PMTree() {
        for (auto root : roots) delete root;
    }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
