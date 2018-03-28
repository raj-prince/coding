// Articulation point O(V + E)
// best_rank is the minimum rank of a node, which also considers rank of their child.

const int N = 100010;

vector <int> g[N];
int art[N], visited[N];
int timer = 0;
int own_rank[N], best_rank[N];

inline void dfs(int cur, int par = -1) {
  own_rank[cur] = best_rank[cur] = timer++;
  visited[cur] = 1;
  int children = 0;
  for (int i = 0; i < g[cur].size(); i++) {
    int child = g[cur][i];
    if (child == par) {
      continue;
    }
    if (visited[child]) {
      best_rank[cur] = min(best_rank[cur], own_rank[child]);
    } else {
      children++;
      dfs(child, cur);
      best_rank[cur] = min(best_rank[cur], best_rank[child]);
      if (best_rank[child] >= own_rank[cur] && par != -1) {
        art[cur] = 1;
      }
    }
  }
  if (par == -1 && children > 1) {
    art[cur] = 1;
  }
}
