// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include "tree.h"

int main() {
  int status = std::system("mkdir -p result");
  (void)status;
  std::ofstream out("result/experiment.csv");
  out << "n,getPermAll,getPerm1,getPerm2\n";
  for (int n = 3; n <= 6; ++n) {
    std::vector<char> in;
    for (int i = 0; i < n; ++i) in.push_back('1' + i);
    PMTree tree(in);
    auto s1 = std::chrono::high_resolution_clock::now();
    getAllPerms(tree);
    auto t1 = std::chrono::duration<double>(
        std::chrono::high_resolution_clock::now() - s1).count();
    auto s2 = std::chrono::high_resolution_clock::now();
    getPerm1(tree, 1);
    auto t2 = std::chrono::duration<double>(
        std::chrono::high_resolution_clock::now() - s2).count();
    auto s3 = std::chrono::high_resolution_clock::now();
    getPerm2(tree, 1);
    auto t3 = std::chrono::duration<double>(
        std::chrono::high_resolution_clock::now() - s3).count();
    out << n << "," << t1 << "," << t2 << "," << t3 << "\n";
  }
  out.close();
  return 0;
}
