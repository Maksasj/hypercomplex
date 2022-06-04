#ifndef HYPERCOMPLEX_H
#define HYPERCOMPLEX_H

#include <string>
#include <iostream>
#include <cmath>
#include <utility>

template<class T1, class T2> struct Cpair {
      T1 a1;
      T2 a2;
};


/*


def conj(x):
      xstar = -x
      xstar[0] *= -1
      return xstar 

def CayleyDickson(x, y):
      n = len(x)

      if n == 1:
            return x*y

      m = n // 2

      a, b = x[:m], x[m:]
      c, d = y[:m], y[m:]
      z = np.zeros(n)
      z[:m] = CayleyDickson(a, c) - CayleyDickson(conj(d), b)
      z[m:] = CayleyDickson(d, a) + CayleyDickson(b, conj(c))
      return z

*/

namespace hypercomplex {
      enum Dim {
            COMPLEX = 2,
      };

      
      struct base {
            int d;
            std::vector<float> e;
            base(std::vector<float> other) {
                  e = other;
                  d = other.size();
            };

            base self() { return base(e); }

            Cpair<base, base> split(base q) {
                  int m = q.e.size() / 2; 

                  base a = base({});
                  base b = base({});
                  for(int l = 0; l < q.e.size(); l++) {
                        if (l < m) {
                              a.e.push_back(q.e[l]);
                        } else {
                              b.e.push_back(q.e[l]);
                        }
                  }
                  a.d = a.e.size();
                  b.d = b.e.size();
                  return {a, b};
            }

            base conj(base other) {
                  base xstar = base({});
                  for(auto a : other.e) {
                        xstar.e.push_back(a*-1.0);
                  }
                  xstar.e[0] *= -1;
                  xstar.d = xstar.e.size();
                  return xstar;
            }

            base operator+(base const& other) {
                  std::vector<float> E;
                  for(int x = 0; x < e.size(); x++) {
                        E.push_back(e[x] + other.e[x]);
                  }
                  return base(E);
            }
            base operator-(base const& other) {
                  std::vector<float> E;
                  for(int x = 0; x < e.size(); x++) {
                        E.push_back(e[x] - other.e[x]);
                  }
                  return base(E);
            }
            
            std::vector<float> conj(std::vector<float> other) {
                  std::vector<float> xstar;
                  for(auto a : other) {
                        xstar.push_back(a*-1.0);
                  }
                  xstar[0] *= -1;
                  return xstar;
            }

            base operator*(base y) {
                  if(e.size() == 1) {
                        return base({e[0]*y.e[0]});
                  }

                  Cpair<base, base> p1 = split(self());
                  Cpair<base, base> p2 = split(y);

                  
                  std::vector<float> qp1_vec = (p1.a1*p2.a1 - conj(p2.a2)*p1.a2).e;
                  std::vector<float> qp2_vec = (p2.a2*p1.a1 + p1.a2*conj(p2.a1)).e;


                  base qp1 = base(qp1_vec);
                  base qp2 = base(qp2_vec);

                  base q = base({});
                  q.d = e.size()*2;

                  for(auto qp : qp1.e) {
                        q.e.push_back(qp);
                  }
                  
                  for(auto qp : qp2.e) {
                        q.e.push_back(qp);
                  }

                  return q;
            }
      };
}

/*
struct complex: hypercomplex::base {
      complex(float _a, float _i): hypercomplex::base({_a, _i}, 2) {

      };
};


struct imaginary {
      float a;
      
      float operator+(imaginary const& other) { return a + other.a; }
      float operator-(imaginary const& other) { return a - other.a; }
      float operator/(imaginary const& other) { return a / other.a; }
      float operator*(imaginary const& other) { return (-1.0)*(a*other.a); }

      friend std::ostream& operator<<(std::ostream& os, imaginary other) {
            os << other.a;
            return os;
      }
};

/*
struct complex {
      float a;
      imaginary i;

      complex(float _a, float _i) { a = _a; i.a = _i; };
      complex(float _a, imaginary _i) { a = _a; i = _i; };

      complex operator+(complex const& other) { return {a + other.a, i + other.i}; }
      complex operator-(complex const& other) { return {a - other.a, i - other.i}; }
      complex operator*(float const& x) { return {(a*x), (i.a*x)}; }
      complex operator*(complex const& other) {
            return {
                  (a*other.a - i.a*other.i.a),
                  (a*other.i.a + i.a*other.a)
            };
      }

      friend std::ostream& operator<<(std::ostream& os, complex other) {
            os << other.a << (other.i.a > 0 ? '+' : '-') << abs(other.i.a) << "i";
            return os;
      }
};

struct quaternion: complex {
      imaginary j;
      imaginary k;

      quaternion(float _a, float _i, float _j, float _k): complex(_a, _i) { j.a = _j; k.a = _k; };

      Cpair<complex, complex> cut(quaternion q) {
            return {{q.a, q.i.a}, {q.j.a, q.k.a}};
      }

      quaternion operator-(quaternion const& other) { return {a - other.a, i - other.i, j - other.j, k - other.k}; }
      quaternion operator+(quaternion const& other) { return {a + other.a, i + other.i, j + other.j, k + other.k}; }
      quaternion operator*(float const& x) { return {(a*x), (i.a*x), (j.a*x), (k.a)*x}; }
      quaternion operator*(quaternion const& other) { 
            auto p1 = cut({a, i.a, j.a, k.a});
            auto p2 = cut(other);

            complex qp1 = {p1.a1*p2.a1 - conj(p2.a2)*p1.a2};
            complex qp2 = {p2.a2*p1.a1 + p1.a2*conj(p2.a1)};

            quaternion q = {qp1.a, qp1.i.a, qp2.a, qp2.i.a};
            return q;
      }

      
      quaternion operator*(quaternion const& other) { 
            return {
                  (a*other.a - i.a*other.i.a - j.a*other.j.a - k.a*other.k.a),
                  (a*other.i.a + i.a*other.a + j.a*other.k.a - k.a*other.j.a),
                  (a*other.j.a - i.a*other.k.a + j.a*other.a + k.a*other.i.a),
                  (a*other.k.a + i.a*other.j.a - j.a*other.i.a + k.a*other.a)
            };
      }
      

      friend std::ostream& operator<<(std::ostream& os, quaternion other) {
            os    << other.a 
                  << (other.i.a > 0 ? '+' : '-') << fabs(other.i.a) << "i" 
                  << (other.j.a > 0 ? '+' : '-') << fabs(other.j.a) << "j" 
                  << (other.k.a > 0 ? '+' : '-') << fabs(other.k.a) << "k";
            return os;
      }
};

struct octonion: quaternion {
      imaginary e5;
      imaginary e6;
      imaginary e7;
      imaginary e8;

      octonion(   float _a, float _i, float _j, float _k,
                  float _e5, float _e6, float _e7, float _e8
      ): quaternion(_a, _i, _j, _k) { 
            e5.a = _e5;
            e6.a = _e6;
            e7.a = _e7;
            e8.a = _e8;
      };

      Cpair<quaternion, quaternion> cut(octonion o) {
            return {{o.a, o.i.a, o.j.a, o.k.a}, {o.e5.a, o.e6.a, o.e7.a, o.e8.a}};
      }

      octonion operator*(octonion const& other) { 
            auto p1 = cut({a, i.a, j.a, k.a, e5.a, e6.a, e7.a, e8.a});
            auto p2 = cut(other);

            quaternion qp1 = {p1.a1*p2.a1 - conj(p2.a2)*p1.a2};
            quaternion qp2 = {p2.a2*p1.a1 + p1.a2*conj(p2.a1)};

            octonion q = {qp1.a, qp1.i.a, qp1.j.a, qp1.k.a, qp2.a, qp2.i.a, qp2.j.a, qp2.k.a};
            return q;
      }

      friend std::ostream& operator<<(std::ostream& os, octonion other) {
            os    << other.a 
                  << (other.i.a > 0 ? '+' : '-') << fabs(other.i.a) << "i" 
                  << (other.j.a > 0 ? '+' : '-') << fabs(other.j.a) << "j" 
                  << (other.k.a > 0 ? '+' : '-') << fabs(other.k.a) << "k"

                  << (other.e5.a > 0 ? '+' : '-') << fabs(other.e5.a) << "e5"
                  << (other.e6.a > 0 ? '+' : '-') << fabs(other.e6.a) << "e6"
                  << (other.e7.a > 0 ? '+' : '-') << fabs(other.e7.a) << "e7"
                  << (other.e8.a > 0 ? '+' : '-') << fabs(other.e8.a) << "e8";
            return os;
      }
};
*/
#endif