// change mod according to question.
// division only work when mod is prime.

const int mod = (int)1e9 + 7;

// add y to x.
inline void add(int &x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

// subtract y from x.
inline void sub(int &x, int y) {
  x -= y;
  if (x < 0) {
    x += mod;
  }
}

// return x * y.
inline int mul(int x, int y) {
  return (long long) x * y % mod;
}

// return x ^ n.
inline int power(int x, int n) {
  int res = 1;
  while (n > 0) {
    if (n & 1) {
      res = mul(res, x);
    }
    x = mul(x, x);
    n >>= 1;
  }
  return res;
}

// used for division.
inline int invMod(int a) {
  return power(a, mod - 2);
}

// return x / y.
inline int divide(int x, int y) {
  return mul(x, invMod(y));
}
