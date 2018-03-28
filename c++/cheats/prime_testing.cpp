// big prime testing.
inline long long mul(long long a, long long b) {
  a %= mod;
  b %= mod;
  long double res = a;
  res *= b;
  long long c = (long long)(res / mod);
  a *= b;
  a = a - c * mod;
  a = a % mod;
  if(a < 0)
    a += mod;
  return a;
}

inline bool prime(long long a, long long n) {
  long long x = 1, step = 1ll << 60, rx;
  while(step > n - 1) step >>= 1;
  while(step > 0) {
    rx = mul(x, x, n);
    if(rx == 1 && x != 1 && x != n - 1) return false;
    x = rx;
    if(step & (n - 1)) x = mul(x, a, n);
    step >>= 1;
  }
  return (x == 1);
}

inline bool prime(long long n) {
  if(n < 100) {
    for(int i = 2; i < n; i++) {
      if(n % i == 0) return false;
    }
    return true;
  }
  return (prime(2, n) && prime(7, n) && prime(61, n) && prime(13, n));
}
