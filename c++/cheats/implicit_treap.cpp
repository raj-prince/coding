// binary search tree w.r.t key and heap w.r.t priority
// implicitTreap has indices as keys
// x->update()              -> update values from its subtree
//
// printTreap(x)            -> print treap rooted at x
//
// split(x, l, r, key, add) -> split treap rooted at x into l and r such that all keys in l < key, add is the offset for index
//
// merge(x, l, r)           -> merge the subtrees rooted at l and r into x
//
// insert(x, pos, v)        -> insert a node at position pos with value v
//                             split the treap into [0, pos) and [pos, n)
//                             merge the left treap with new node and then merge the tree back
//
// update                   -> first split [0, n) into [0, l) and [l, n)
//                          -> then split  [l, n) into [l, r] and [r + 1, n)
//                          -> then do the required operation on treap containing [l, r]
//                          -> lazy propagation can be implemented
//
// query                    -> repeat above procedure to obtain treap containing [l, r]
//                          -> then return the corresponding value

const int N = 100010;

struct node {
  int cnt, val, prior;
  long long sum;
  node * l, * r;

  inline void update() {
    cnt = 1 + (l ? l->cnt : 0) + (r ? r->cnt : 0);
    sum = val + (l ? l->sum : 0) + (r ? r->sum : 0);
  }
} mem[N];

typedef node * p_node;

inline p_node newNode() {
  static int mem_ptr = 0;
  return mem + mem_ptr++;
}

void print(p_node x, int level = 0) {
  if(!x) return;
  if(x->l) {
    print(x->l, level + 1);
  }
  printf("%*s(%d, %lld, %d)\n", level * 2, "", x->val, x->sum, x->prior);
  if(x->r) {
    print(x->r, level + 1);
  }
}

inline int size(p_node x) {
  return x ? x->cnt : 0;
}

inline long long sum(p_node x) {
  return x ? x->sum : 0;
}

void split(p_node x, p_node & l, p_node & r, int key, int add = 0) {
  if(!x) {
    l = r = NULL;
    return;
  }
  int curKey = add + size(x->l);
  if(key <= curKey) {
    split(x->l, l, x->l, key, add);
    r = x;
  } else {
    split(x->r, x->r, r, key, curKey + 1);
    l = x;
  }
  x->update();
}

void merge(p_node & x, p_node l, p_node r) {
  if(!l or !r)
    x = l ? l : r;
  else if(l->prior > r->prior) {
    merge(l->r, l->r, r);
    x = l;
  } else {
    merge(r->l, l, r->l);
    x = r;
  }
  if(x) x->update();
}

inline void insert(p_node & T, int pos, int v) {
  p_node cur = newNode();
  cur->val = cur->sum = v;
  cur->prior = rand();
  cur->cnt = 1;
  cur->l = cur->r = NULL;
  p_node l, r;
  split(T, l, r, pos);
  merge(l, l, cur);
  merge(T, l, r);
}

inline void update(p_node & T, int pos, int v) {
  p_node l, m, r;
  split(T, l, m, pos);
  split(m, m, r, 1);

  if(m) {
    m->sum = m->val = v;
  }

  merge(T, l, m);
  merge(T, T, r);
}

inline long long getSum(p_node & T, int ql, int qr) {
  p_node l, m, r;

  split(T, l, m, ql);
  split(m, m, r, qr - ql + 1);

  long long ret = sum(m);

  merge(T, l, m);
  merge(T, T, r);

  return ret;
}
