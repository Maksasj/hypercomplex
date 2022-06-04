#include <iostream>
#include <vector>
#include "hypercomplex.hpp"

template<typename T> void printH(T a1, T a2) {
      std::cout << "(" << a1 << ")*(" << a2 << ") = " << a1*a2 << "\n";
}


int main() {
      hypercomplex::base b4 = hypercomplex::base({7, 3, 5, -6, 8, 2, 9, 1});
      hypercomplex::base b5 = hypercomplex::base({1, -6, 4, 3, 8, 8, 9, 9});

      hypercomplex::base b6 = b4*b5;

      for(auto x : b6.e) {
            std::cout << x << " ";
      }

      return 0; 
}