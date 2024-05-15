template <int L> inline u64 mulSlow(u64 a, u64 b) {
  static constexpr int l = L >> 1;
  const u64 a0 = a & ((1ULL << l) - 1), a1 = a >> l;
  const u64 b0 = b & ((1ULL << l) - 1), b1 = b >> l;
  const u64 a0b0 = mulSlow<l>(a0, b0);
  return (a0b0 ^ mulSlow<l>(1ULL << (l - 1), mulSlow<l>(a1, b1)))
      | (a0b0 ^ mulSlow<l>(a0 ^ a1, b0 ^ b1)) << l;
} /* O(log n^1.58), to optimize use (a ^ b) * c = a * c ^ b * c */
template <> inline u64 mulSlow<1>(u64 a, u64 b) { return a & b; }