class Primes {
public:
  vector<int> divisor_cnt;
  vector<int> P;

  constexpr Primes(int ub) {
    divisor_cnt.resize(ub+1,0);
    for (int i=2; i<=ub; i++) {
      if (divisor_cnt[i]) continue;
      P.push_back(i);
      for (int j=i; j<=ub; j+=i) {
        int k = j;
        while (k%i == 0) divisor_cnt[j]++, k/=i;
      }
    }
 }

