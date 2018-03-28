// b[j] denotes if there is a mismatch occurs at j then
// from which position we have to start matching.
// O(n + m) text_length + pattern_length
const int N = 100010;

int b[N];

inline void calc_failure(const string &p) {
  int k = -1, i = 0;
  b[0] = -1;
  int lop = p.size();
  while (i < lop) {
    while (k >= 0 && p[k] != p[i]) {
      k = b[k];
    }
    i++, k++;
    b[i] = k;
  }
}

inline void kmp_search(const string &t, const string &p) {
  int k = 0, i = 0;
  int lop = p.size();
  int lot = t.size();
  calc_failure(p);
  while (i < lot) {
    while (k >= 0 && p[k] != t[i]) {
      k = b[k];
    }
    k++, i++;
    if (k == lop) {
      // match found at i - lop.
      k = b[k]; // k = 0, if have to find non-overlapping
    }
  }
}
