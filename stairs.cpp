
#include <map>
#include "pretty_printer.hpp"
#include <iostream>
#include <cstdint>

class Solution {

    std::map<int,uint64_t> sols;

public:
    void _climbstairs(int n ) {
        if (n==1) {
            sols[1] = 1;
        } else if (n==2) {
            sols[2] = 2;
        } else {
            sols[n] = (sols[n-2] + 1) + (sols[n-1] + 1);
        }
    }

    int climbStairs(int n) {
        for(int i = 1;i<=n;++i) {
            _climbstairs(i);
        }
        print( std::cout, sols);
        std::cout << std::endl;
        return sols[n];
    }
};


int main() {

    Solution sol;
    sol.climbStairs(4);
};
