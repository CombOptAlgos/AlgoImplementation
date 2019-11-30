# DIJKSTRA ALGOLITHM

computes shortest path from r in O(n^2) time

## Usage

### input.txt

|V| is the number of vertices and |E| is the number of edges in G. The graph vertices are named with the numbers 0, 1,..., |V|−1 respectively. r is the source of the graph.

s_i and t_i represent source and target vertices of i-th edge (directed) and di represents the cost of the i-th edge.

```
|V| |E| r

s_0 t_0 d_0
s_1 t_1 d_1
s_2 t_2 d_2
...
```

### build and run

```
$ c++ dijkstra.cc
$ ./a.out < input.txt > output.txt
```

### output.txt

The output consists of |V| lines. Print the cost of the shortest path from the source r to each vertex 0, 1, ... |V|−1 in order. If there is no path from the source to a vertex, print INF.

```
$ open output.txt
```

## Test Case

[http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=jp](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=jp)

## TODO

implement the function of outputting the concrete shortest paths
