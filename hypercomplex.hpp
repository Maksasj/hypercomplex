#ifndef HYPERCOMPLEX_H
#define HYPERCOMPLEX_H

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <utility>

namespace hypercomplex {
      template<class T1, class T2> struct Cpair {
            T1 a1;
            T2 a2;
      };

      class base {
            private:
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
                        return {a, b};
                  }

                  base conj(base other) {
                        base xstar = base({});
                        for(auto a : other.e) {
                              xstar.e.push_back(a*-1.0);
                        }
                        xstar.e[0] *= -1;
                        return xstar;
                  }
            public:
                  std::vector<float> e;

                  base(std::vector<float> other) {
                        e = other;
                  };

                  base operator+(base const& other) {
                        std::vector<float> E;
                        for(int x = 0; x < e.size(); x++) {
                              E.push_back(e[x] + other.e[x]);
                        }
                        return base(E);
                  }
                  void operator+=(base const& other) {
                        for(int x = 0; x < e.size(); x++) {
                              e[x] += other.e[x];
                        }
                  }
                  base operator-(base const& other) {
                        std::vector<float> E;
                        for(int x = 0; x < e.size(); x++) {
                              E.push_back(e[x] - other.e[x]);
                        }
                        return base(E);
                  }     
                  base operator*(base y) {
                        if(e.size() == 1)
                              return base({e[0]*y.e[0]});

                        Cpair<base, base> p1 = split(self());
                        Cpair<base, base> p2 = split(y);

                        base qp1 = base((p1.a1*p2.a1 - conj(p2.a2)*p1.a2).e);
                        base qp2 = base((p2.a2*p1.a1 + p1.a2*conj(p2.a1)).e);

                        base q = base({});

                        for(auto qp : qp1.e)
                              q.e.push_back(qp);
                        
                        for(auto qp : qp2.e)
                              q.e.push_back(qp);

                        return q;
                  }

                  friend std::ostream& operator<<(std::ostream& os, base other) {
                        for(int x = 0; x < other.e.size(); x++){
                              os << (other.e[x] > 0 ? '+' : '-') << fabs(other.e[x]) << "e" << x+1;
                        }
                        return os;
                  }
      };
}

struct complex: hypercomplex::base {
      complex(): hypercomplex::base({0, 0}) { };
      complex(float _a, float _i): hypercomplex::base({_a, _i}) { };

      complex(const hypercomplex::base &x) : hypercomplex::base(x) {}
};

struct quaternion: hypercomplex::base {
      quaternion(): hypercomplex::base({0, 0, 0, 0}) { };
      quaternion(float _a, float _i, float _j, float _k): hypercomplex::base({_a, _i, _j, _k}) { };

      quaternion(const hypercomplex::base &x) : hypercomplex::base(x) {}
};

struct octonion: hypercomplex::base {
      octonion(): hypercomplex::base({0, 0, 0, 0, 0, 0, 0, 0}) { };
      octonion(float _a, float _i, float _j, float _k, float _e5, float _e6, float _e7, float _e8): hypercomplex::base({_a, _i, _j, _k, _e5, _e6, _e7, _e8}) { };

      octonion(const hypercomplex::base &x) : hypercomplex::base(x) {}
};

#endif