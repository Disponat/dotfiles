// associative & invertible range queries O(log N)
// point update in O(log N)
// assuming 1-indexed: first set bit indicates how many elements are in the cumulative sum
// and adding the first set bit finds the parent
// implementation is 0-indexed, so it subtracts 1 when indexing
// 0010 -> two elements   0100 -> four elements, 1000 -> eight elements
template <typename T = int>
class FenwickTree {
  std::vector<T> A;
  int n; //  #Elements
  public:

  FenwickTree(std::vector<T>&& A_) : A{std::move(A_)} { init(); }
  FenwickTree(std::vector<T>& A_) : A{A_} { init(); }
  FenwickTree(int n) : A(std::vector<T>(n)), n(n) { init(); }

  void init() {
    n = A.size();
    for (int i=1; i<=n; i++) {
      int p = i + (i & -i); // gets element i's immediate parent
      if (p <= n) {
        A[p-1] += A[i-1];
      }
    }
  }

  // cumulative sum of first i elements: one operation per set bit in i
  // i.e adds range [0,i)
  T prefix_sum(int i) const {
    T ans = 0;
    while (i > 0) {
      ans += A[i-1];
      i -= i & -i; // clear first set bit
    }
    return ans;
  }

  // range sum [i,j)  (0-indexed) 
  T sum(int i, int j) const { 
    assert (j <= n);
    return prefix_sum(j) - prefix_sum(i);
  }

  // get ith element: 0-indexed
  T operator[](int i) const {
    return sum(i, i+1);
  }

  // add 'v' to element 'i' (0-indexed)
  void add(int i, T v) {
    i++; // make i 1-indexed
    while (i <= n) {
      A[i-1] += v;
      i += (i & -i); // parent of obtained by adding the lowest set bit to i, increasing the lowest set bit
    }
  }
};

template <typename T = int>
class FenwickRange {
  // Starting with an array of zeroes, if we do a range update of +x to [l,r]
  //
  // sum[0,i] = 
  //    -> 0 if i < l
  //    -> x * (i-(l-1)) if l<=i<=r
  //    -> -x * (l-1-r) if i > r
  //
  // sum[0,i] = B1*i - B2
  // Where B1 has a value of 'x' within the updated range and 0 outside
  // and B2 has a value of x*(l-1) within the range and x*(l-1-r) outside it.
  // We can a fenwick tree have a certain value within a range and a certain value outside in O(logn)
  // by updating the beginning and end only, and looking at the prefix sum. 
 private:
  FenwickTree<T> B1, B2;
  int n;

 public:
  FenwickRange(int size) : B1(std::vector<T>(size, 0)), B2(std::vector<T>(size, 0)), n(size) {}

  FenwickRange(std::vector<T>& A) : B1(0), B2(0), n(A.size()) {
    std::vector<T> B1_init(n+1), B2_init(n+1);
    for (int i = 0; i < n; ++i) {
      B1_init[i] = A[i];
      B2_init[i] = A[i] * (i - 1);
    }
    B1_init[n] = 0; // Operator [] goes to i+1, which further goes to i+2 in the internal BIT, so increase their size by 1.
    B2_init[n] = 0;
    B1 = FenwickTree<T>(std::move(B1_init));
    B2 = FenwickTree<T>(std::move(B2_init));
  }

  // increment interval [l,r] by v
  void range_add(int l, int r, T v) {
    B1.add(l, v);
    B1.add(r+1, -v);
    B2.add(l, v*l); // (l-1) when 1-indexed becomes just l when 0-indexed
    B2.add(r+1, -v*(r+1)); // r when 1-indexed becomes r+1 when 0-indexed
  }

  // [0, i)
  T prefix_sum(int i) const {
    return B1.prefix_sum(i)*i - B2.prefix_sum(i);
  }

  // [l, r)   0-indexed
  T sum(int l, int r) const {
    return prefix_sum(r) - prefix_sum(l);
  }

  // get ith element, 0-indexed
  T operator[](int i) const {
    return B1.prefix_sum(i+1);
  }

};
