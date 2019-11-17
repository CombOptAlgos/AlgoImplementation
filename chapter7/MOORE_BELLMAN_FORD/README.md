# MOORE BELLMAN FORD ALGORITHM

This algorithm finds shortest path from s to all the other vertices in O(nm) time.

## Usage

```input.txt
5 7 2
1 2 1
1 3 1
1 4 2
1 5 3
2 3 6
2 4 5
4 5 4
```

```
$ c++ main.cpp
$ ./a.out < input.txt > output.txt
```

```output.txt
Done!
s: 2
distance between s and 1 : Unreachable
distance between s and 2 : 0
distance between s and 3 : 6
distance between s and 4 : Unreachable
distance between s and 5 : Unreachable

parent of 1: Undefined
parent of 3: 2
parent of 4: Undefined
parent of 5: Undefined
```


