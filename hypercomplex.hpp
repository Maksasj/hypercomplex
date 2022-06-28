#ifndef HYPERCOMPLEX_H
#define HYPERCOMPLEX_H

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <cassert>
#include <cmath>

namespace hypercomplex {
      bool valid_dim(int n) {
            return n > 0 && 0 == (1 << 30) % n;
      }

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
                  
                  base(int dim) {
                        assert(!valid_dim(dim));
                        for(int x = 0; x < dim; x++) {
                              e.push_back(0);
                        }
                  }
                  base(std::vector<float> data) {
                        assert(valid_dim(data.size()));
                        e = data;
                  };
                  base(std::vector<float> data, int dim) {
                        assert(valid_dim(data.size()) && dim == data.size());
                        e = data;
                  };

                  base operator+(base const& other) {
                        assert(e.size() == other.e.size());
                        std::vector<float> E;
                        for(int x = 0; x < e.size(); x++) {
                              E.push_back(e[x] + other.e[x]);
                        }
                        return base(E);
                  }
                  base operator-(base const& other) {
                        assert(e.size() == other.e.size());
                        std::vector<float> E;
                        for(int x = 0; x < e.size(); x++) {
                              E.push_back(e[x] - other.e[x]);
                        }
                        return base(E);
                  }  
                  
                  void operator+=(base const& other) {
                        assert(e.size() == other.e.size());
                        for(int x = 0; x < e.size(); x++)
                              e[x] += other.e[x];
                  }
                  void operator-=(base const& other) {
                        assert(e.size() == other.e.size());
                        for(int x = 0; x < e.size(); x++)
                              e[x] -= other.e[x];
                  }
                  void operator*=(base y) {
                        base tmp = self() * y;
                        e = tmp.e;
                  }

                  base operator*(base y) {
                        assert(e.size() == y.e.size());
                        if(e.size() == 1)
                              return base(std::vector<float>({e[0]*y.e[0]}));

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
                  
                  void pow(int n) {
                        base tmp = self();
                        for(int x = 0; x < n; x++) {
                              tmp *= self();
                        }
                        e = tmp.e;
                  }

                  friend std::ostream& operator<<(std::ostream& os, base other) {
                        for(int x = 0; x < other.e.size(); x++){
                              os << (other.e[x] > 0 ? '+' : '-') << fabs(other.e[x]) << "e" << x+1;
                        }
                        return os;
                  }
      };

      class bibase {
            private:
                  bibase self() { return bibase(e); }

                  Cpair<bibase, bibase> split(bibase q) {
                        int m = q.e.size() / 2; 

                        bibase a = bibase({});
                        bibase b = bibase({});
                        for(int l = 0; l < q.e.size(); l++) {
                              if (l < m) {
                                    a.e.push_back(q.e[l]);
                              } else {
                                    b.e.push_back(q.e[l]);
                              }
                        }
                        return {a, b};
                  }

                  bibase conj(bibase other) {
                        bibase xstar = bibase({});
                        for(auto a : other.e) {
                              xstar.e.push_back(a*-1.0);
                        }
                        xstar.e[0] *= -1;
                        return xstar;
                  }
            public:
                  std::vector<float> e;
                  
                  bibase(int dim) {
                        assert(!valid_dim(dim));
                        for(int x = 0; x < dim; x++) {
                              e.push_back(0);
                        }
                  }
                  bibase(std::vector<float> data) {
                        assert(valid_dim(data.size()));
                        e = data;
                  };
                  bibase(std::vector<float> data, int dim) {
                        assert(valid_dim(data.size()) && dim == data.size());
                        e = data;
                  };

                  bibase operator+(bibase const& other) {
                        assert(e.size() == other.e.size());
                        std::vector<float> E;
                        for(int x = 0; x < e.size(); x++) {
                              E.push_back(e[x] + other.e[x]);
                        }
                        return bibase(E);
                  }
                  bibase operator-(bibase const& other) {
                        assert(e.size() == other.e.size());
                        std::vector<float> E;
                        for(int x = 0; x < e.size(); x++) {
                              E.push_back(e[x] - other.e[x]);
                        }
                        return bibase(E);
                  }  
                  void operator+=(bibase const& other) {
                        assert(e.size() == other.e.size());
                        for(int x = 0; x < e.size(); x++)
                              e[x] += other.e[x];
                  }
                  void operator-=(bibase const& other) {
                        assert(e.size() == other.e.size());
                        for(int x = 0; x < e.size(); x++)
                              e[x] -= other.e[x];
                  }
                     
                  bibase operator*(bibase y) {
                        assert(e.size() == y.e.size());
                        if(e.size() == 1)
                              return bibase(std::vector<float>({e[0]*y.e[0]}));

                        Cpair<bibase, bibase> p1 = split(self());
                        Cpair<bibase, bibase> p2 = split(y);

                        bibase qp1 = bibase((p1.a1*p2.a1 - conj(p2.a2)*p1.a2).e);
                        bibase qp2 = bibase((p2.a2*p1.a1 + p1.a2*conj(p2.a1)).e);

                        bibase q = bibase({});

                        for(auto qp : qp1.e)
                              q.e.push_back(qp);
                        
                        for(auto qp : qp2.e)
                              q.e.push_back(qp);

                        return q;
                  }

                  friend std::ostream& operator<<(std::ostream& os, bibase other) {
                        for(int x = 0; x < other.e.size(); x++){
                              os << (other.e[x] > 0 ? '+' : '-') << fabs(other.e[x]) << "e" << x+1;
                        }
                        return os;
                  }
      };
}

struct complex: hypercomplex::base {
      complex(): hypercomplex::base(2) { };
      complex(std::vector<float> data): hypercomplex::base(data, 2) { };
      complex(float _a, float _i): hypercomplex::base({_a, _i}) { };

      complex(const hypercomplex::base &x) : hypercomplex::base(x) {}
};

struct quaternion: hypercomplex::base {
      quaternion(): hypercomplex::base(4) { };
      quaternion(std::vector<float> data): hypercomplex::base(data, 4) { };
      quaternion(float _a, float _i, float _j, float _k): hypercomplex::base({_a, _i, _j, _k}) { };

      quaternion(const hypercomplex::base &x) : hypercomplex::base(x) {}
};

struct octonion: hypercomplex::base {
      octonion(): hypercomplex::base(8) { };
      octonion(std::vector<float> data): hypercomplex::base(data, 8) { };
      octonion(float _a, float _i, float _j, float _k, float _e5, float _e6, float _e7, float _e8): hypercomplex::base({_a, _i, _j, _k, _e5, _e6, _e7, _e8}) { };

      octonion(const hypercomplex::base &x) : hypercomplex::base(x) {}
};

struct sedenion: hypercomplex::base {
      sedenion(): hypercomplex::base(16) { };
      sedenion(std::vector<float> data): hypercomplex::base(data, 16) { };
      sedenion(   float _a, float _i, float _j, float _k, float _e5, float _e6, float _e7, float _e8,
                  float _e9, float _e10, float _e11, float _e12, float _e13, float _e14, float _e15, float _e16
      ): hypercomplex::base({_a, _i, _j, _k, _e5, _e6, _e7, _e8, _e9, _e10, _e11, _e12, _e13, _e14, _e15, _e16}) { };

      sedenion(const hypercomplex::base &x) : hypercomplex::base(x) {}
};

#endif