// Segment tree, where the tree size is forced to be a power of 2
// dividing by 2 brings us to parent. Left children are even. Right children are odd.
template <class S, auto op, S e> class segtree {
  static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>, "op must work as S(S, S)");
  // static_assert(std::is_convertible_v<decltype(e), std::function<S()>>, "e must work as S()");
  unsigned int _n, sz, n_bits;
  std::vector<S> T;
  void update(int k) { T[k] = op(T[2*k], T[2*k+1]); }

public:
  segtree() : segtree(0) {}

  explicit segtree(int n) : segtree(std::vector<S>(n, e)) {}

  explicit segtree(const std::vector<S>& v) {
    _n = v.size();
    n_bits = 32 - __builtin_clz(_n);
    sz = 1<<n_bits;
    T.resize( 2*sz, e );

    for (int i=0; i<_n; i++) T[sz + i] = v[i];
    for (int i=sz-1; i>=1; i--) update(i);
  }

  S operator[](int i) { // 0-indexed
    return T[sz+i];
  }

  void set(int i, S x) {
    i += sz;
    T[i] = x;
    for (int j=1; j<=n_bits; j++) update(i >> j);
  }
  
  // apply operation over [l,r), 0-indexed
  S prod(int l, int r) {
    S sml = e, smr = e; // left and right sums for non-commutative operators
    l += sz;
    r += sz;

    while (l < r) {
      if (l&1) sml = op(sml, T[l++]); // l is a right child. add it then go to its cousin.
      if (r&1) smr = op(T[--r], smr); // r is a right child. r is excluded so go to left child and add it
      l >>= 1;
      r >>= 1;
    }
    return op(sml, smr);
  }

  S all_prod() { return T[1]; }



  // Find largest value of r such that prod [l,r) is true. [true true ... false]
  // You can think of 'f' as a sum threshold: return true if sum is still below x
  // binary search: order log(n)^2
  int max_right(int l, const auto f) const {
    if (l >= _n) return _n;
    l += sz;
    S sm = e;

    do {
      while (l%2 == 0) l >>= 1; // go to the highest parent whose range starts at l

      if (!f(op(sm,T[l]))) { // range is too large, make it smaller
        while (l < sz) { // going down until the last level
          l *= 2; // go down a level (to left child)
          if (f(op(sm, T[l]))) { // if range is true we store its result and go to the right sibling
            sm = op(sm,T[l]);
            l++;
          }
        }
        return l - sz; // subtract sz to convert from segtree index to actual array index
      }

      sm = op(sm, T[l]); // sum can include all of l's children, but not its parent
      l++; // so go to the cousin to its right
    } while ((l & -l) != l); // while l is not a power of two (i.e. not leftmost node in a level)
                             // this happens when l reaches the last node in a layer
                             // and goes to the next layer after incrementing. It means all true in [l,n)
    return _n; // never found a range too large, so [l,n) is true
  }

  // Find smallest value of l such that prod [l,r) is true.
  int min_left(int r, const auto f) const {
    r += sz;
    S sm = e;

    do {
      r--; // first run, this excludes initial r. Later runs, this brings us to left sibling.
      while (r>1 and (r%2) ) r >>= 1; // go to highest parent whose range ends at r

      if (!f(op(sm,T[r]))) { // if range is too large, make it smaller
        while (r < sz) { // go down to the last level (taking right children)
          r = 2*r + 1; // go down to the right child
          if (f(op(T[r],sm))) { // range returns true so add it to the sum and go to left sibling
            sm = op(T[r],sm);
            r--;
          }
        }
        r++; // last node we reach is NOT in the range, so exclude it
        return r - sz; // subtract sz to convert from segtree index to array index 
      }

      sm = op(T[r], sm);
    } while ( (r & -r) != r); // terminate when leftmost node in a layer was added to the answer

    return 0; // no range is too big, so can go to the beginning of the array: [0,r)
  }
};

