## Next-Fit Algorithm 

### Build manual

```bash
make run
make clean
```

### instance
- input example
```bash
15   // number of items
0.21 // items
0.74
0.32
0.48
0.59
0.64
0.82
0.2
0.37
0.52
0.13
0.02
0.36
0.96
0.17
```

- output
```bash
1: 0.95 ... 0.21 0.74 // bin number: total weight ... items
2: 0.8 ... 0.32 0.48 
3: 0.59 ... 0.59
4: 0.64 ... 0.64 
5: 0.82 ... 0.82
6: 0.57 ... 0.2 0.37 
7: 0.67 ... 0.52 0.13 0.02 
8: 0.36 ... 0.36 
9: 0.96 ... 0.96 
10: 0.17 ... 0.17 
```
