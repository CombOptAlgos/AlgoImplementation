## Knapsack DP

### Build manual

```bash
mkdir build
cd build
cmake ..
make
./DYNAMIC_PROGRAMMING_KNAPSACK < ../input.txt > ../output.txt
cd ..
```

### instance

```bash
n
w1 c1 # weight profit
w2 c2
...
wn cn
W
```
- example
```bash
4
2 3
1 2
3 4
2 2
5
```
output
```
3 1 0
5 7
```
