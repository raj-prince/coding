// Sparse Table (range query)
// O(nlogn) preprocessing, O(1) range query
// change op(x, y) to any associative function
// call init function before any query

const int N = 100010;

int log_2[N];  // log_2[i] stores the index of last 1's in o-indexing.
int dp[N][20]; // dp[i][j] stores function value of range of length 2^j starting from i.

inline int op(int a, int b) {
  return max(a, b);
}

int a[N]; // data array

inline void init(int sz) {
  // initialize log table
  // in case of multiple test cases, use this just at the begining
  log_2[0] = -1;
  for (int i = 1; i < N; i++) {
    log_2[i] = log_2[i - 1];
    if ((i & (i - 1)) == 0) {
      log_2[i]++;
    }
  }
  for (int i = 0; i < sz; i++) {
    dp[i][0] = a[i];
  }
  for (int j = 1; (1 << j) <= sz; j++) {
    for (int i = 0; i + (1 << j) <= sz; i++) {
      dp[i][j] = op(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
    }
  }
}

// takes the l and r in 0-indexing.
inline int query(int l, int r) {
  int k = log_2[r - l + 1];
  return op(dp[l][k], dp[r - (1 << k) + 1][k]);
}
