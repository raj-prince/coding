// finds augmenting path related to each and every from each
// and every left side vertex. reset know before calling augment.

const int N = 2010;

bitset <N> know;
int match[N];

vector <int> g[N]; // contains neighbor of each left partition vertex.

inline int augment(int l) {
  if (know[l]) {
    return 0;
  }
  know[l] = true;
  for (auto r : g[l]) {
    if (match[r] == -1 || augment(match[r])) {
      match[r] = l;
      return 1;
    }
  }
  return 0;
}

// [0, n) is the node of left partition.
int maxMatch(int n) {
   memset(match, -1, sizeof match);
   int mcbm = 0;
   for (int i = 0; i < n; i++) {
     know.reset();
     mcbm += augment(i);
   }
   return mcbm;
}

