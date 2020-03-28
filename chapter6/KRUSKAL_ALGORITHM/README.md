# KRUSKAL ALGORITHM

This algorithm finds minimum spannning tree of undirected graph G in O(mα(m,n)) time. Here, α(m, n) is the nverse function of Ackermann function.

## Usage

### 1. Open and edit input.txt

```
$ open input.txt
```

input.txt has the format below.

```
N M
tail head weight (xM)
```

##### example
```
5 7
1 2 1
1 3 1
1 4 2
1 5 3
2 3 6
2 4 5
4 5 4
```

### 2. Run the script

```
$ c++ main.cpp
$ ./a.out < input.txt > output.txt
```

### 3. Check the result

```
$ open output.txt
```

output.txt
```
5 4
1 2 1
1 3 1
1 4 2
1 5 3
```
