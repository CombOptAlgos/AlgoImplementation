# Graph Scanning Algolithm Imprementation

## Change Point

- Implemented with queue

## Usage

First, pleasre open and rewite `input.txt` as follows.
```
$ open input.txt
```
First line is `|V(G)| |E(G)|`

Secind line is `start vertex`

After the 3rd line, write all the edges ends;

- Example

input.txt
```
5 4 
2    
0 1
1 2
2 0
3 4
```

Then, let's' build and run.

```
$ c++ -std=c++11 main.cpp
$ ./a.out < input.txt > output.txt
```

You can check the result to open `output.txt`.
```
$ open output.txt
```

- Example

Output.txt
```
The vertices reachable from  2 is:
0 1 2
```

