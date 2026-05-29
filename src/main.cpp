// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "tree.h"

int main() {
#ifdef _WIN32
  std::system("mkdir result 2>nul");
#else
  std::system("mkdir -p result");
#endif

    std::ofstream out("result/experiment.csv");
    out << "n,getPermAll,getPerm1,getPerm2\n";

    for (int n = 3; n <= 7; ++n) {
        std::vector<char> in;
        for (int i = 0; i < n; ++i) in.push_back('1' + i);
        PMTree tree(in);

        auto start = std::chrono::high_resolution_clock::now();
        getAllPerms(tree);
        auto t1 = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();

        start = std::chrono::high_resolution_clock::now();
        getPerm1(tree, 1);
        auto t2 = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();

        start = std::chrono::high_resolution_clock::now();
        getPerm2(tree, 1);
        auto t3 = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();

        out << n << "," << t1 << "," << t2 << "," << t3 << "\n";
    }
    out.close();
    return 0;
}
