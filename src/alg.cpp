// Copyright 2022 NNTU-CS
#include <vector>
#include <algorithm>
#include "tree.h"

void build(Node* parent, std::vector<char> rem) {
  if (rem.empty()) return;
  std::sort(rem.begin(), rem.end());
  for (size_t i = 0; i < rem.size(); ++i) {
    Node* child = new Node(rem[i]);
    parent->children.push_back(child);
    std::vector<char> next = rem;
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

void dfs(Node* node, std::vector<char>& cur,
         std::vector<std::vector<char>>& res) {
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

void navigate(Node* node, int& cur, int target, std::vector<char>& path,
              std::vector<char>& res) {
  path.push_back(node->val);
  if (node->children.empty()) {
    if (++cur == target) res = path;
  } else {
    for (auto child : node->children) {
      if (res.empty()) navigate(child, cur, target, path, res);
    }
  }
  path.pop_back();
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  std::vector<std::vector<char>> all = getAllPerms(tree);
  if (num < 1 || static_cast<size_t>(num) > all.size()) return {};
  return all[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  std::vector<char> res, path;
  int cur = 0;
  for (auto root : tree.roots) {
    if (res.empty()) navigate(root, cur, num, path, res);
  }
  return res;
}
