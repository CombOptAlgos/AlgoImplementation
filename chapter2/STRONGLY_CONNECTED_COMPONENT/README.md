## Storongly Connected Component Algolithm Imprementation

### Build manual

```bash
mkdir build
cd build
cmake ..
make
./STRONGLY_CONNECTED_COMPONENT < ../input.txt > output.txt
cd ..
```

### instance

- input example  
V(G) = {0, 1, 2, 3, 4}  
E(G) = {(0, 1), (1, 2), (2, 0), (3, 4)}  

```bash
5 4  # |V(G)| |E(G)|
0 1
1 2
2 0
3 4
```
- output 
```bash
0 0 # vertices comp_value
1 0
2 0
3 1
4 2
```


