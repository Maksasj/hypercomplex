#include <iostream>
#include "hypercomplex.hpp"

int main() {
      complex q1 = {1, 5};
      complex q2 = {2, 4};

      complex q3 = q1 + q2;

      quaternion q4 = {1 , 6, 8, 6};
      std::cout << q4.i;
      std::cout << q3.a << " " << q3.i;
      return 0; 
}