struct RNG {
    mt19937 mt;
    random_device rd;
    RNG() {mt = mt19937(rd());}
    i64 operator()(i64 x) { return this->operator()(0, x); } // [0, x)
    i64 operator()(i64 l, i64 r) {
        uniform_int_distribution<i64> d(l, r - 1);
        return d(mt);
    }
} rng;
