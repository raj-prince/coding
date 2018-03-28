// lowest common ancestor <n * log n, log n>
// call dfs(0, -1) and initialize p[0] = 0;
// call process and after that find lca.
const int N = 100010;
const int LGN = 20;

int timer;
int tin[N], tout[N];
int p[N], ancs[N][LGN];

vector<int> g[N];

// is x an ancestor of y
inline bool anc(int x, int y) {
  return (tin[x] <= tin[y] && tout[x] >= tout[y]);
}

inline void dfs(int cur, int par) {
  p[cur] = par;
  tin[cur] = timer++;
  for(auto nbr : g[cur]) {
    if(nbr != par) {
      dfs(nbr, cur);
    }
  }
  tout[cur] = timer++;
}

inline void process(int n) {
  for(int i = 0; i < n; i++) {
    ancs[i][0] = p[i];
  }
  for(int j = 1; j < LGN; j++) {
    for(int i = 0; i < n; i++) {
      ancs[i][j] = ancs[ancs[i][j - 1]][j - 1];
    }
  }
}

inline int lca(int x, int y) {
  if(anc(x, y)) return x;
  for(int i = LGN - 1; i >= 0; i--) {
    if(!anc(ancs[x][i], y)) {
      x = ancs[x][i];
    }
  }
  return p[x];
}
