/**
* let f[i] = f[i - 1] + f[i - 2];
* F0 = {f[0], f[1]};
* FN + 1 = {f[n + 1], f[n + 2]};
* F(I + 1) = T * F(I)
* hence F(N) = T ^ N * F0;
*/
// calculates Fibonacci in (log n).
// technique for optimizing DP calculation.

const int mod = 1e9 + 7;
const int sz = 2;

inline void add(int &x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

inline int mul(int x, int y) {
  return (long long) x * y % mod;
}

struct Matrix {
  int a[sz][sz];

  Matrix(int dia = 0) {
    for (int i = 0; i < sz; i++) {
      for (int j = 0; j < sz; j++) {
        a[i][j] = (i == j) ? dia : 0;
      }
    }
  }

  Matrix operator*(const Matrix &o) const {
    Matrix ans(0);
    for (int i = 0; i < sz; i++) {
      for (int j = 0; j < sz; j++) {
        int  res = 0;
        for (int k = 0; k < sz; k++) {
          add(res, mul(a[i][k], o.a[k][j]));
        }
      }
    }
    return ans;
  }

  Matrix operator+(const Matrix &o) const {
    Matrix ans(0);
    for (int i = 0; i < sz; i++) {
      for (int j = 0; j < sz; j++) {
        add(ans.a[i][j], a[i][j]);
        add(ans.a[i][j], o.a[i][j]);
      }
    }
    return ans;
  }
};

inline Matrix power(Matrix &x, int n) {
  Matrix res(1);
  while (n > 0) {
    if (n & 1) {
      res = (res * x);
    }
    x = (x * x);
    n >>= 1;
  }
  return res;
}

inline int fib(int n) {
  Matrix t;
  t.a[0][0] = 0;
  t.a[0][1] = 1;
  t.a[1][0] = 1;
  t.a[1][1] = 1;
  Matrix res = power(t, n);
  return res.a[0][1];
}
