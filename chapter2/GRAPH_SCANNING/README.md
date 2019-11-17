# Graph Scanning Algolithm Imprementation

### Build manual

```bash
mkdir build
cd build
cmake ..
make
./GRAPH_SCANNING < input.txt > output.txt
```

### Instance

- input example  
V(G) = {0, 1, 2, 3, 4}  
E(G) = {{0, 1}, {1, 2}, {2, 0}, {3, 4}}  

```bash
5 4  # |V(G)| |E(G)|
2    # start vertex
0 1
1 2
2 0
3 4
```
- output   
vertices reachable from start vertex 

```bash
0 1 2
```



