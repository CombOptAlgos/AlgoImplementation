# Dinic's Algorithm Implementation

## Dinic's Algorithm's idea
- make level graph of residual graph.
- find blocking flow in level graph.
- augment flow by blocking flow.
- compared to Ford-Fulkerson's Algorithm or Edmonds-Karp's Algorithm, the number of iteration is smaller!

## Build manual
write instance to input.txt and run below commands.
```bash
make run
make clean
```
then, the optimun(maximun) flow is written in output.txt!

## Example
- input.txt
    - number of vertices, edges.
    - s and t of s-t-flow.
    - directed edge and its cost.
```bash
8 15
0 7
0 1 10
0 2 5
0 3 15
1 2 4
1 4 9
1 5 15
2 3 4
2 5 8
3 6 16
4 5 15
4 7 10
5 7 10
5 6 15
6 2 6
6 7 10
```

- output.txt
```bash
v_from	v_to	flow
0	1	10
0	2	5
0	3	13
1	2	0
1	4	8
1	5	2
2	3	0
2	5	8
3	6	13
4	5	0
4	7	8
5	7	10
5	6	0
6	2	3
6	7	10
```
