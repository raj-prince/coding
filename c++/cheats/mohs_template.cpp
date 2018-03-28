// off line query processing algorithm.
// here we have to count no. of distinct element in [l, r].

const int M = 2000010; // no of query.
const int BLOCK = 250; // sqrt (N) ; N - no of element.

int ans[M];
int ql[M], qr[M], id[M];

// smart comparator for sorting range.
inline bool cmp(int i, int j) {
  int u = ql[i] / BLOCK;
  int v = ql[j] / BLOCK;
  if(u != v) return u < v;
  return qr[i] < qr[j];
}

inline void del(int pos) {
  // change required when we delete the element at
  // given position from the current sub - array.
}

inline void add(int pos) {
  // change required when we add the element at position
  // in the current sub - array.
}

int main() {
  // take array as input
  int n;
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    scanf("%d", a + i);
  }
  // take query as range.
  int m;
  scanf("%d", &m);
  for(int i = 0; i < m; i++) {
    scanf("%d %d", ql + i, qr + i);
    ql[i]--, qr[i]--;
    id[i] = i;
  }

  sort(id, id + m, cmp);
  int curl = ql[0], curr = ql[0] - 1;
  for(int i = 0; i < m; i++) {
    while(curr < qr[id[i]]) {
      curr++;
      add(curr);
    }
    while(curl > ql[id[i]]) {
      curl--;
      add(curl);
    }
    while(curr > qr[id[i]]) {
      del(curr);
      curr--;
    }
    while(curl < ql[id[i]]) {
      del(curl);
      curl++;
    }
    //ans[id[i]] = required result.
  }
  for(int i = 0; i < m; i++) {
    printf("%d\n", ans[i]);
  }
}


