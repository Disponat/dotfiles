constexpr i64 MOD = 1000000007;
vector<i64> fact, finv;

i64 modpow(int n, int p = MOD - 2) {
  if (p == 0) return 1;
  i64 tmp = modpow(n, p/2);
  tmp = (tmp * tmp) % MOD;
  if (p%2 == 1) tmp = (tmp * n) % MOD;
  return tmp;
}

void fact_init(int N) {
  fact.resize(N);
  finv.resize(N);
  fact[0] = finv[0] = 1;
  for (int i=1; i<N; i++) {
    fact[i] = (fact[i-1] * i) % MOD;
    finv[i] = modpow(fact[i], MOD - 2);
  }
}

i64 C(int n, int k) {
  if (k < 0 || n < k) return 0;
  return ((fact[n] * finv[k])%MOD * finv[n-k])%MOD;
}
