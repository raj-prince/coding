// simple a balance binary tree.
// O(log n) insert, delete, order statics.

struct Node {
  int key, prior, sz;
  Node *l, *r;
  Node() {}
  Node(int k, int p) : key(k), prior(p), l(NULL), r(NULL) {}

  inline void update() {
    sz = (l ? l->sz : 0) + (r ? r->sz : 0) + 1;
  }
};

typedef Node* pnode;

// l will contain (z <= key) and r will contain (z > key).
inline void split(pnode x, pnode &l, pnode &r, int key) {
  if (!x) {
    l = r = NULL;
  } else if (key < x->key) {
    split(x->l, l, x->l, key);
    r = x;
  } else {
    split(x->r, x->r, r, key);
    l = x;
  }
  if (x) {
    if (x->l) x->l->update();
    if (x->r) x->r->update();
    x->update();
  }
}

// insert node y into x.
inline void insert(pnode &x, pnode y) {
  if(!x) {
    x = y;
  } else if (y->prior > x->prior) {
    split(x, y->l, y->r, y->key);
    x = y;
  } else {
    insert(y->key < x->key ? x->l : x->r, y);
  }
  if (x) {
    if (x->l) x->l->update();
    if (x->r) x->r->update();
    x->update();
  }
}

// for merging max of l should less than or equal to min of r.
inline void merge(pnode &x, pnode l, pnode r) {
  if (!l || !r) {
    x = l ? l : r;
  } else if (l->prior > r->prior) {
    merge(l->r, l->r, r);
    x = l;
  } else {
    merge(r->l, l, r->l);
    x = r;
  }
  if (x) {
    if (x->l) x->l->update();
    if (x->r) x->r->update();
    x->update();
  }
}

// reach the required node and merge their child to that node.
inline void erase(pnode &x, int key) {
  if (!x) return;
  if (x->key == key) {
    merge(x, x->l, x->r);
  } else {
    erase(key < x->key ? x->l : x->r, key);
  }
  if (x) {
    if (x->l) x->l->update();
    if (x->r) x->r->update();
    x->update();
  }
}

// merging two tree in any order here, no condition is given.
inline pnode join(pnode l, pnode r) {
  if (!l || !r) return l ? l : r;
  if (l->prior < r->prior) {
    swap(l, r);
  }
  pnode lt, rt;
  split(r, lt, rt, l->key);
  l->l = join(l->l,lt);
  l->r = join(l->r, rt);
  if (l) {
    if (l->l) l->l->update();
    if (l->r) l->r->update();
    l->update();
  }
  return l;
}

// find kTh smallest element.
inline int kthSmallest(pnode x, int k) {
  if (!x) {
    return -1;
  } else {
    int cnt = (x->l ? x->l->sz : 0) + 1;
    if (k == cnt) {
      return x->key;
    } else if (k < cnt) {
      return kthSmallest(x->l, k);
    } else {
      return kthSmallest(x->r, k - cnt);
    }
  }
}

// no. of element less than equal to val.
inline int lessOrEqual(pnode x, int val) {
  if (!x) {
    return 0;
  } else {
    int cnt = (x->l ? x->l->sz : 0) + 1;
    if (val >= x->key) {
      return lessOrEqual(x->r, val) + cnt;
    } else {
      return lessOrEqual(x->l, val);
    }
  }
}

// walk in - order.
inline void inorder(pnode x) {
  if (x) {
    inorder(x->l);
    printf("%d ", x->key);
    inorder(x->r);
  }
}

inline int getRandom() {
  return (rand() << 15) + rand();
}
