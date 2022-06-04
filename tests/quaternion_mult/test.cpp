#include "../../hypercomplex.hpp"
#include <fstream>

int main() {
      octonion o1 = {7, 3, 5, -6, 8, 2, 9, 1};
      octonion o2 = {1, -6, 4, 3, 8, 8, 9, 9};

      std::ofstream out("output.txt");
      out << o1 * o2;
      out.close();

      return 0;
}