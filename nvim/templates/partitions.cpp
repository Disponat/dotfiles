class Partitions {
public:
  class Iterator {
    public:
    // iterate through partitions of n, in descending order
    int n;
    int k = 0; // index of 'v' we are on. k+1 = length of partition
    vector<int> v;

    Iterator(int _n) : n(_n) {
      v.assign(n,0);
      v[0] = n;
    }

    Iterator(int _n, bool is_end) : n(_n), k(-1) {}

    const std::vector<int> operator*() {
      return std::vector<int>(v.begin(), v.begin() + k + 1);
    }


    Iterator& operator++() {
      int rem = 0;
      while (k >= 0 && v[k] == 1) {
        rem++;
        k--;
      }

      if (k<0) {
        return *this; // all values are 1: Done iterating.
      }

      v[k]--;
      rem++;

      // When remainder is larger than current value, we can't just append it to the right
      // because that would violate the non-increasing order.
      // Instead, we distribute the current value until the remainder is smaller than that value
      // EX: P(6) -> v = [2], rem = 4, then v = [2,2] remainder = 2, which results in v = [2,2,2]
      while (rem > v[k]) {
        v[k+1] = v[k];
        rem -= v[k];
        k++;
      }

      v[k+1] = rem;
      k++;
      return *this;
    }

    // This != operator is only useful for range loops, but not std::find or std::distance
    bool operator!= (const Iterator& other) {
      return k != other.k;
    }

  };

    Partitions(int n) : n(n) {}

    Iterator begin() const {
        return Iterator(n);
    }

    Iterator end() const {
        return Iterator(n, true);
    }

private:
    int n;
};
