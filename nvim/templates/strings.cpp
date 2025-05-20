#include <bits/stdc++.h>
using namespace std;
#define i64 long long
#define f64 long double
#define all(v) v.begin(), v.end()

// "outer" palindrome: (l,r)
// let j be the mirror position of i: j = l + (r-i)
// We already know R[j], since j < i
// inner palindromes: (j-R[j],j+R[j]) and (i-R[i], i+R[i])
// if j-R[j] does not go below l, then we know R[i] = R[j]
// otherwise, we know R[i] is at least r-i. 
// we know it is palindromic up to 'r', but we know nothing beyond that
vector<int> _manacher_odd(string& s) {
    int n = s.size();
    vector<int> R(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(R[l + r - i], r - i); // k: size of sub-palindrome at i
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
        R[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    return R;
}

// Obtains the longest palindrome substrings centered at each position in a given string
// change abcbcba to #a#b#c#b#c#b#a#
// Then get R[i], radius of longest odd sub-palindrome centered at i
void manacher(string &s, vector<int>& d_odd, vector<int>& d_even) {
    string t;
    t.reserve(s.size()*2 + 1);
    for(int i=0; i<s.size(); i++) {
      t.push_back('#');
      t.push_back(s[i]);
    }
    t.push_back('#');
    auto R = _manacher_odd(t);
    d_odd.resize(s.size());// d_odd[i]: length of longest odd palindrome centered at position i
    d_even.resize(s.size()); // d_even[i]: length of longest even palindrome centered between i and i+1   
    for (int i=1; i<R.size()-1; i+=2) {
      d_odd[i/2] = R[i] - 1; 
      d_even[i/2] = R[i+1] - 1; // NOTE: last entry of d_even is undefined. Kept for convenience to make odd and even same size. 
    }
}

// Very similary to Manacher: store matching segment (l,r]
// Main property of a matching segment: S[l,r) = S[0, r-l)
// This implies: S[l+i,r) = S[i,r-l)   (i.e. take part of the matching segments)
// Therefore, S[i,r) = S[i-l, r-l)   (i.e. take the part that starts at i)
// Therefore, z[i] = z[i-l]  (if two string segments are equal, their z values must be equal)
// However, we can only be certain up to r, so we cap i+z[i] at r
vector<int> z_algorithm(string &s) {
  int n = s.size();
  vector<int> z(n,0); 
  z[0] = n; // string s is a prefix of itself
  for (int i=1, l=0, r=-1; i<n; i++) { // must start at i=1, otherwise we get an interval with l=0 and that messes it up
    if (i<r) z[i] = min(r-i, z[i-l]);
    while( i+z[i] < n && s[z[i]] == s[i + z[i]] ) z[i]++;
    if (i + z[i] > r) {
      l = i;
      r = i + z[i];
    }
  }
  return z;
}


// find all occurrences of string t in s
vector<int> rabin_karp(string &s, string &t) {
  const in p = 31;
  const int m = 1000000009;
  vector<long long> p_pow( max(s.size(), t.size()) );
  p_pow[0] = 1;
  for (int i=1; i < (int) p_pow.size(); i++) {
    p_pow[i] = (p_pow)
  }
}

signed main(){
  string s; cin >> s;
  int n = s.size();
  auto z = z_algorithm(s);
  for (auto c: z) cout << c << ' ';
  cout << endl;
  return 0;
}

