// Read large block at once, then parse it
enum {BUF_SIZE=(1<<17)};
char buf[BUF_SIZE|1], *pos, *endbuf;

#if defined _BSD_SOURCE || defined _SVID_SOURCE
#define fread fread_unlocked
#endif

inline int buffer() {
    size_t len=fread(buf, 1, BUF_SIZE, stdin);
    buf[len] = 0;
    endbuf = buf + len;
    pos = buf;
    return len;
}

inline int rebuffer() {
    ptrdiff_t left=endbuf-pos;
    if (buf+left >= pos)
        return *pos;

    memcpy(buf, pos, left);
    size_t len=fread(buf+left, 1, BUF_SIZE-left, stdin);
    endbuf = buf + (left+=len);
    *endbuf = 0;
    pos = buf;
    return len;
}

inline int scan() {
    int u=0;
    if (pos + 10 >= endbuf)
        rebuffer();

    do {
        u = u*10 + *pos-'0';
    } while (*++pos >= '0');

    ++pos;
    return u;
}
