# Linux and Mac OS X findfirst, findnext and findclose

This is an implementation of
[findfirst](http://msdn.microsoft.com/en-US/library/zyzxfzac.aspx),
[findnext](http://msdn.microsoft.com/en-US/library/6tkkkc1y.aspx) and
[findclose](http://msdn.microsoft.com/en-US/library/0165cecc.aspx) for Linux.
Linux and Mac OS X functions should have the same signatures as their Win32 equivalents.

## Integration

To use in your own projects, the required files are:

- findfirst.c
- findfirst.h
- spec.h
- spec.c
- apple_fstatat.c
- fstatat.c
- apple_dir_mutex.c
- dir_mutex.c
- dir_mutex.h
- tup.compat.h

Refer to main.c for a usage example.

