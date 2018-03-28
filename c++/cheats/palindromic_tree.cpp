// Palindrome Tree : Creates all Palindromic Substrings with their Frequencies in O(n)
//    tree[1] = palindrome of length -1 (for odd length palindrome)
//    tree[2] = palindrome of length 0 (for even length palindrome)
//    cnt : Contains frequency of palindrome of that node
// driver program : http://www.spoj.com/problems/NUMOFPAL/

const int alpha = 26;
const int N = 105000;

struct Node {
  int next[alpha]; // link to palindrome by adding alpha
  int len; // length of palindrome
  int sufflink; // link to largest suffix palindrome
  int cnt; // frequency of palindrome
};

int e; // last alloted node number.
int last; // index of last suffix.

Node tree[N];
char s[N];

// node - 1 is root of odd length palindrome.
// node - 2 is root of even length palindrome.
inline void initTree() {
  tree[1].len = -1;
  tree[1].sufflink = 1;
  tree[2].len = 0;
  tree[2].sufflink = 1;
  e = 2, last = 2;
  for (int i = 0; i < N; i++) {
    tree[i].cnt = 0;
    memset(tree[i].next, 0, sizeof tree[i].next);
  }
}

// returns node - number of the node whose left side contains the
// same character which I am going to add in the right side.
inline int getLink(int cur, int pos) {
  while (pos - tree[cur].len - 1 < 0 || s[pos - tree[cur].len - 1] != s[pos]) {
    cur = tree[cur].sufflink;
  }
  return cur;
}

// add a new node if the max palindrome which can be made after adding
// the current character is not represented by any node till now.
// other wise simply return by incrementing the count once.
inline bool addLetter(int pos) {
  int c = s[pos] - 'a';
  int cur = last;
  cur = getLink(cur, pos);
  if (tree[cur].next[c]) {
    last = tree[cur].next[c];
    tree[last].cnt += 1;
    return false;
  }
  ++e; // otherwise create new node.
  last = e;
  tree[e].len = tree[cur].len + 2;
  tree[e].cnt += 1;
  tree[cur].next[c] = e;
  if (tree[e].len == 1) {
    tree[e].sufflink = 2;
    return true;
  }
  tree[e].sufflink = tree[getLink(tree[cur].sufflink, pos)].next[c];
  return true;
}

// update count of all node to it's suffix link node.
inline void updateCount() {
  for (int i = e; i > 1; i--) {
    tree[tree[i].sufflink].cnt += tree[i].cnt;
  }
}
