#include <iostream>
#include "hypercomplex.hpp"

int main() {
      complex q1 = {3, 1};
      complex q2 = {5, -3};
      
      quaternion q4 = {1 , 6, -4, 1};
      quaternion q5 = {-2 , 5, 7, -3};

      quaternion q6 = {q1, -6.0, 5.0};
      std::cout << q6 << "\n";

      std::cout << "(" << q1 << ")*(" << q2 << ") = " << q1*q2 << "\n";
      std::cout << "(" << q4 << ")*(" << q5 << ") = " << q4*q5 << "\n";
      std::cout << "(" << q4 << ")*(" << q5 << ") = " << q4+q5 << "\n";
      std::cout << "(" << q1 << ")*(" << q1 << ") = " << q1*q1 << "\n";
      return 0; 
}