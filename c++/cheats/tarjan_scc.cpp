// O(v + e); strongly connected component for directed graph.
// best_rank is the minimum rank of a node, which also considers rank of their child.

const int N = 100010;

int timer, cn;
int best_rank[N], own_rank[N];
int instack[N], know[N];

stack <int> stk;
vector <int> g[N];
vector <int> comp[N]; // all the nodes to the given component number.

// call until any unknown vertex remaining.
inline void tarjan_scc(int cur) {
  best_rank[cur] = own_rank[cur] = timer++;
  know[cur] = 1;
  stk.push(cur);
  instack[cur] = 1;
  for (auto nbr : g[cur]) {
    if (!know[nbr]) {
      tarjan_scc(nbr);
    }
    if (instack[nbr]) {
      best_rank[cur] = min(best_rank[cur], best_rank[nbr]);
    }
  }
  if (best_rank[cur] == own_rank[cur]) {
    // cur is the root.
    while (!stk.empty() && stk.top() != cur) {
      instack[stk.top()] = 0;
      // do whatever u want here.
      comp[cn].push_back(stk.top());
      stk.pop();
    }
    instack[cur] = 0;
    // do action for root here.
    comp[cn].push_back(cur);
    cn++;
    stk.pop();
  }
}
