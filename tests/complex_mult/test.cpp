#include "../../hypercomplex.hpp"
#include <fstream>

int main() {
      complex z1 = {3, 1};
      complex z2 = {5, -3};

      std::ofstream out("output.txt");
      out << z1 * z2;
      out.close();

      return 0;
}