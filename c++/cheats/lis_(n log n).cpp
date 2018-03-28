// 2, 6, 7, 4, 5
// lets increasing sub sequence is 2, 4, 5.
// index of 4 will be store in link[index of 5].

const int N = 100010;

int a[N], link[N], idx[N];

// returns longest increasing subsequence.
vector <int> incrSeq(int x[], int n) {
  vector <int> v;
  int last_idx = 0;
  for (int i = 0; i < n; i++) {
    // use upper_bound for non decreasing subsequence.
    int pos = lower_bound(v.begin(), v.end(), x[i]) - v.begin();
    idx[pos] = i;
    link[i] = (pos == 0) ? -1 : idx[pos - 1];
    if (pos < v.size()) {
      v[pos] = x[i];
    } else {
      v.push_back(x[i]);
      idx[pos] = i;
      last_idx = i;
    }
  }
  v.clear();
  int cur = last_idx;
  while (cur >= 0) {
    v.push_back(x[cur]);
    cur = link[cur];
  }
  reverse(v.begin(), v.end());
  return v;
}
