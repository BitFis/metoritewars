#ifndef _MACROS_H
#define _MACROS_H 1

/* http://stackoverflow.com/questions/8439907/macro-for-iterator-loop-for-stl-iterables */
#define foreach(iter, iterable) for(typeof((iterable).begin()) iter = (iterable).begin(); ((iterable).size()) && iter != (iterable).end(); ++iter)

#endif /* _MACROS_H */
