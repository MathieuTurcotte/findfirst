#ifdef __APPLE__
    #define AT_SYMLINK_NOFOLLOW 0x100
    #include "fstatat.c"
#endif
