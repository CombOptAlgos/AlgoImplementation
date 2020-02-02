## Euler tour Detection Algorithm Imprementation

### Build manual

```bash
make
```

### instance
- input example(Eulerian, K5)
```bash
5 10
4
0 1
0 2
0 3
0 4
1 2
1 3
1 4
2 3
2 4
3 4
```

- output
```bash
4 0 1 2 0 3 1 4 2 3 4
```

- input example(Not Eulerian, K4)
```bash
4 6
2
0 1
0 2
0 3
1 2
1 3
2 3
```

- output
```bash
This graph is not eulerian
```
