## First-Fit-Decreasing Algorithm 

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
1: 0.98 ... 0.96 0.02 // bin number: total weight ... items
2: 0.99 ... 0.82 0.17 
3: 0.95 ... 0.74 0.21 
4: 1 ... 0.64 0.36    
5: 0.96 ... 0.59 0.37
6: 1 ... 0.52 0.48 
7: 0.65 ... 0.32 0.2 0.13
```
