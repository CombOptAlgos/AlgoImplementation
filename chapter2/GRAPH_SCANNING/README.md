# Graph Scanning Algolithm Imprementation == 1.0.1

## Change Point
    - Implemented with queue

## Usage

```
$ open input.txt
```

Please 

First line is `|V(G)| |E(G)|`

Secind line is `start vertex`

After the 3rd line, please write all the edges ends;

- Example
```input.txt
5 4 
2    
0 1
1 2
2 0
3 4
```

Then, build and run.

```
$ c++ -std=c++11 main.cpp
$ ./a.out < input.txt > output.txt
```

You can check the result to open `output.txt`.
```
$ open output.txt
```

- Example
```Output.txt
The vertices reachable from  2 is:
0 1 2
```

