#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

// T: type of elements in array. U: type of elements used for updating
// Root vertex at index 1
// First leaf node is at index n and last leaf node at index 2n-1 
template<typename T, typename U>
class LazySegTree {
private:
    int n_bits;
    void apply_lazy(U f, int k) {
      A[k] = map_op(f, A[k]);
      if (k<n) lazy[k] = comp_op(f, lazy[k]);
    }

    void activate_children(int k) { // pushes node's lazy value to its children
      apply_lazy(lazy[k], 2*k);
      apply_lazy(lazy[k], 2*k+1);
      lazy[k] = map_id;
    }

    void activate_path(int k) { // start at root node and apply lazy values to nodes on path to index k
      for (int i=n_bits; i >= 1; i--) {
        activate_children( k >> i);
      }
    }

    void activate_range(int l, int r) {
      for (int i = n_bits; i >= 1; i--) {
        if (((l >> i) << i) != l) activate_children(l >> i); // only if there are right children 
        unsigned int mask = (1U<<i) - 1;
        if ( (mask & r) != mask) activate_children(r >> i); // only if there are left children
      }
    }

    void update_range(int l, int r) {
      for (int i = 1; i < n_bits; i++) {
          if (((l >> i) << i) != l) {
            update(l >> i);
          }
          unsigned int mask = (1U<<i) - 1;
          if ( (mask & r) != mask) {
            update(r >> i); // only if there are left children
          }
      }
    }

    void update(int k) { // recalculate a node's value from its child nodes
      A[k] = op(A[2*k], A[2*k+1]);
    }

    void update_path(int p) { // update nodes on path from a leaf to root
      for (int i=1; i <= n_bits; i++) update( p >> i );
    }

public:
  std::vector<T> A;
  std::vector<U> lazy;
  T id; // zero-element
  U map_id;
  std::function<T(T,T)> op;
  std::function<T(U,T)> map_op; // how an update affects values of the array
  std::function<U(U,U)> comp_op; // how two updates interact with each other
  int n;
 
  LazySegTree(
      T id_,
      U map_id_,
      std::function<T(T,T)> op_, 
      std::function<T(U,T)> map_op_,
      std::function<U(U,U)> comp_op_,
      std::vector<T>& A_
    ) : id{id_}, map_id{map_id_}, op{op_}, map_op{map_op_}, comp_op{comp_op_} {
    n = A_.size();
    n_bits = 32 - __builtin_clz(n);

    A = std::vector<T>(2*n, id);
    lazy = std::vector<U>(n, map_id);
    for (int i=0; i<n; i++) A[n + i] = A_[i];
    for (int i=n-1; i>0; --i) update(i);
  }

  void display_node(int i, bool include_lazy=true) {
    if (i==0) return;
    cout<<"{"<<A[i].cnt0<<","<<A[i].cnt1<<"," << A[i].inv << "}";
    //if (i<n and include_lazy) 
    //  cout<<"&{"<<lazy[i].b<<", "<<lazy[i].c<<"}";
  }
  void display(bool all_levels = true, int l = 0, int r = -1) {
    if (r == -1) r = n-1;
    l += n;
    r += n;
    do
     {
      int l2 = l, r2 = r;
      while (l2 <= r2) {
        display_node(l2++); 
        cout << ' ';
      }
      cout << '\n';
      r /= 2;
      if (r == l) r--;
      l /= 2;
    } while (l <= r and all_levels);
  }

  void set(int ind, T val) {
    ind += n;
    activate_path(ind);
    A[ind] = val;

    while (ind > 1) {
      ind /= 2;
      val = op(A[2*ind], A[2*ind + 1]);
      if (A[ind] != val) {
        A[ind] = val;
      }
      else {
        return; 
      }
    }
  }

  T operator[](int ind) { // 0-indexed
    ind += n;
    activate_path(ind);
    return A[ind];
  }

  // apply operation from index l to r (0-index) inclusive
  T prod(int l, int r) {
    l += n;
    r += n;
    activate_range(l,r);
    T ans_l = id, ans_r = id;
    while (l <= r) {
      if (l&1) ans_l = op(A[l++], ans_l);
      if (!(r&1)) ans_r = op(ans_r, A[r--]);
      l /= 2;
      r /= 2;
    }
    return op(ans_l, ans_r);
  }

  T all_prod() { 
    activate_lazy(A[1], lazy[1]);
    return A[1]; 
  }

  void apply(int p, U f) {
    p += n;
    activate_path(p);
    A[p] = map_op(f, A[p]);
    update_path(p);
  }

  // 0-indexed [l,r] (inclusive)
  void apply(int l, int r, U f) {
    l += n;
    r += n;
    activate_range(l,r);
    int l2 = l, r2 = r;
    while (l <= r) {
      if (l&1) apply_lazy(f, l++);
      if (!(r&1)) apply_lazy(r--, f);
      l /= 2;
      r /= 2;
    }
    l = l2, r = r2;
    update_range(l,r);
  }

};

struct S {i64 cnt0, cnt1, inv;};
using F = bool;
S op(S l, S r) {return {l.cnt0 + r.cnt0, 
                        l.cnt1 + r.cnt1,
                        (l.inv + r.inv) + r.cnt0 * l.cnt1}; }
S map_op(F f, S s) {
  if (f) { return {s.cnt1, s.cnt0, s.cnt0*s.cnt1 - s.inv}; }
  else return s;
}
F comp_op(F f, F g) {return (f && !g) || (!f && g);}

int main() {
  int n,q; cin >> n >> q;
  vector<S> A(n);
  for (int i=0; i<n; i++) {
    int x; cin >> x;
    if (x) A[i] = {0,1,0};
    else A[i] = {1,0,0};
  }

  LazySegTree<S,F> seg(S{0,0,0}, false, op, map_op, comp_op, A);
  seg.display();
  for (int i=0; i<q; i++) {
    int t,l,r; cin >> t >> l >> r;
    l--; r--;
    if (t == 1) {
      seg.apply(l,r, true);
    }
    else {
      cout << seg.prod(l,r).inv << '\n';
    }
  }
  return 0;
}
