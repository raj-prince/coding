// comparison of double with specified precision.
const double pi = acos(-1.0d);
const double eps = 1e-10;

// return true when a > b.
inline bool gr(double a, double b) {
  return (a - b) >= eps;
}

// return true when a < b.
inline bool ls(double a, double b) {
  return gr(b, a);
}

// return true when a == b.
inline bool eq(double a, double b) {
  return fabs(a - b) < eps;
}
