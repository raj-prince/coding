const int LOG = 18;
const int N = (1 << LOG);

int tree[N + 1];

// add v to value at x.
inline void add(int x, int v) {
  while (x <= N) {
    tree[x] += v;
    x = (x | (x - 1)) + 1;
  }
}

// get cumulative sum up to and including x
inline int get(int x) {
  int res = 0;
  while (x > 0) {
    res += tree[x];
    x &= (x - 1);
  }
  return res;
}

// get largest value with cumulative sum less than or equal to x;
// for smallest, pass x-1 and add 1 to result
inline int getind(int x) {
  int idx = 0, mask = N;
  while (mask > 0 && idx < N) {
    int t = idx + mask;
    if (x >= tree[t]) {
      idx = t;
      x -= tree[t];
    }
    mask >>= 1;
  }
  return idx;
}
