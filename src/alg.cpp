// Copyright 2022 NNTU-CS
#include "tree.h"

void build(Node* parent, std::vector<char> remaining) {
    if (remaining.empty()) return;
    std::sort(remaining.begin(), remaining.end());
    for (size_t i = 0; i < remaining.size(); ++i) {
        char val = remaining[i];
        Node* child = new Node(val);
        parent->children.push_back(child);
        std::vector<char> next = remaining;
        next.erase(next.begin() + i);
        build(child, next);
    }
}

PMTree::PMTree(const std::vector<char>& in) {
    std::vector<char> sorted = in;
    std::sort(sorted.begin(), sorted.end());
    for (size_t i = 0; i < sorted.size(); ++i) {
        Node* root = new Node(sorted[i]);
        std::vector<char> next = sorted;
        next.erase(next.begin() + i);
        build(root, next);
        roots.push_back(root);
    }
}

void dfs(Node* node, std::vector<char>& cur, std::vector<std::vector<char>>& res) {
    cur.push_back(node->val);
    if (node->children.empty()) res.push_back(cur);
    for (auto child : node->children) dfs(child, cur, res);
    cur.pop_back();
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> res;
    std::vector<char> cur;
    for (auto root : tree.roots) dfs(root, cur, res);
    return res;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    auto all = getAllPerms(tree);
    if (num < 1 || static_cast<size_t>(num) > all.size()) return {};
    return all[num - 1];
}

void navigate(Node* node, int& cur, int target, std::vector<char>& path, std::vector<char>& res) {
    path.push_back(node->val);
    if (node->children.empty()) {
        cur++;
        if (cur == target) res = path;
    } else {
        for (auto child : node->children) {
            navigate(child, cur, target, path, res);
            if (!res.empty()) break;
        }
    }
    path.pop_back();
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    std::vector<char> res, path;
    int cur = 0;
    for (auto root : tree.roots) {
        navigate(root, cur, num, path, res);
        if (!res.empty()) break;
    }
    return res;
}
