// take s and initialize len with its length.
// more useful when we have to calculate LCP of any two suffix. O(log n)
// can be used so many times without resetting the value.

const int N = 500010;
const int lgN = 22;

struct Suffix {
  int pr[2]; // rank as a pair.
  int idx; // starting index of suffix.
} sa[N];

int step, cnt, len;
int rnk[lgN][N]; // rank[k][i] store rank of suffix of length 2^k started at i.
char s[N];

bool cmp(Suffix a, Suffix b) {
  if (a.pr[0] == b.pr[0]) {
    return a.pr[1] < b.pr[1];
  }
  return a.pr[0] < b.pr[0];
}

void buildSuffixArray() {
  for(int i = 0; i < len; i++) {
    rnk[0][i] = s[i] - 'A';
  }
  for(step = 1, cnt = 1; (cnt >> 1) < len; step++, cnt <<= 1) {
    for(int i = 0; i < len; i++) {
      sa[i].pr[0] = rnk[step - 1][i];
      sa[i].pr[1] = (i + cnt < len) ? rnk[step - 1][i + cnt] : -1;
      sa[i].idx = i;
    }
    sort(sa, sa + len, cmp);
    for(int i = 0; i < len; i++) {
      rnk[step][sa[i].idx] = (i > 0 && sa[i].pr[0] == sa[i - 1].pr[0] && sa[i].pr[1] == sa[i - 1].pr[1]) ? rnk[step][sa[i - 1].idx] : i;
    }
  }
}

// calculate LCP between suffix started at x and y.
inline int lcp(int x, int y) {
  int lcp_cnt = 0;
  if(x == y) {
    return len - x;
  }
  for(int k = step - 1; k >= 0 && x < len && y < len; k--) {
    if(rnk[k][x] == rnk[k][y]) {
      x += (1 << k);
      y += (1 << k);
      lcp_cnt += (1 << k);
    }
  }
  return lcp_cnt;
}
