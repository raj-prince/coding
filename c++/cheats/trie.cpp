// O(word length) all query.
// manipulate add, query and Del function according to need.

const int CHILD = 26;

struct Node {
  Node* child[CHILD];
  int cnt;

  Node() {
    cnt = 0;
    for (int i = 0; i < CHILD; i++) {
      child[i] = NULL;
    }
  }

  void clear() {
    cnt = 0;
    for (int i = 0; i < CHILD; i++) {
      child[i] = NULL;
    }
  }
};

typedef Node* pnode;

struct Trie {
  pnode root;

  Trie() {
    root = new Node();
  }

  ~Trie() {
    delete root;
  }

  void add(const string &x) {
    pnode cur = root;
    for (int i = 0; i < x.size(); i++) {
      cur->cnt++;
      int c = (x[i] - 'a');
      if (cur->child[c] == NULL) {
        cur->child[c] = new Node();
      }
      cur = cur->child[c];
    }
    cur->cnt++;
  }

  bool query(const string &x) {
    pnode cur = root;
    for (int i = 0; i < x.size(); i++) {
      int c = (x[i] - 'a');
      if (cur->child[c] == NULL || cur->cnt <= 0) {
        return false;
      }
      cur = cur->child[c];
    }
    return (cur->cnt > 0);
  }

  void del(const string &x) {
    pnode cur = root;
    for (int i = 0; i < x.size(); i++) {
      cur->cnt--;
      int c = (x[i] - 'a');
      assert(cur->child[c] != NULL);
      cur = cur->child[c];
    }
    cur->cnt--;
  }
};
