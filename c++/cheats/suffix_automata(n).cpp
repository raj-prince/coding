// First initialize the automaton and extend one by one.
// To convert to Map version comment the codes marked by 'Array version' and
// uncomment the codes marked by 'Map version'

const int alpha = 26;

struct State {
  int len, link;
  map<char, int> next; // Map Version
//  int next[alpha]; // Array Version
};

const int N = 50010;

int term[N + N]; // Marks the terminal/final states.
State st[N + N];
int sz, last; // sz = size of the automaton

// Initialize Suffix Automaton
inline void initAutomata() {
  sz = last = 0;
  st[0].len = 0;
  st[0].link = -1;
  sz++;

  // Map version.
  for (int i = 0; i < (N + N); i++) {
    st[i].next.clear();
    term[i] = 0;
  }

//  // Array Version
//  for (int i = 0; i < N + N; i++) {
//    term[i] = 0;
//    memset(st[i].next, -1, sizeof st[i].next);
//  }
}

// In case of array version give normalize int like 0 for 'a';
inline void extendAutomata(int c) {
  int cur = sz++;
  st[cur].len = st[last].len + 1;
  int p = last;

  // Map Version
  while(p != -1 && !st[p].next.count(c)) {
    st[p].next[c] = cur;
    p = st[p].link;
  }

//  // Array Version
//  while (p != -1 && st[p].next[c] == -1) {
//    st[p].next[c] = cur;
//    p = st[p].link;
//  }

  if(p == -1) {
    st[cur].link = 0;
  } else {
    int q = st[p].next[c];
    if(st[p].len + 1 == st[q].len) {
      st[cur].link = q;
    } else {
      int clone = sz++;
      st[clone].len = st[p].len + 1;

      // Map Version
      st[clone].next = st[q].next;

//      // Array version
//      for (int j = 0; j < alpha; j++) {
//        st[clone].next[j] = st[q].next[j];
//      }

      st[clone].link = st[q].link;
      while(p != -1 && st[p].next[c] == q) {
        st[p].next[c] = clone;
        p = st[p].link;
      }
      st[q].link = st[cur].link = clone;
    }
  }
  last = cur;
}

// Marks the terminal/final states of the automaton
inline void markTerminal() {
  int link = last;
  while (link != -1) {
    term[link] = 1;
    link = st[link].link;
  }
}

// count no. of distinct substring which is no. of different
// path from the initial node in suffix automaton.
int d[N + N];
inline int cntDistinctSubs(int s) {
  int tp = 1;
  if(d[s]) return d[s];
  for (auto x : st[s].next) {
    tp += cntDistinctSubs(x.second);
  }
  d[s] = tp;
  return d[s];
}
