# edmons_karp

An implementation of Edmonds-Karp algorithm. 

In the following, the home directory is 
assumed to be `EDMONS_KARP/`.

## Idea

The basic idea is the same as Ford-Fulkerson algorithm. In Edmons-Karp algorithm,
every augmenting path is chosen from the shortest paths of a residual graph.
Suprisingly, this trick assures the termination of the algorith for arbitrary inputs.

## Build Manual

Run the following command in any directory below `edmons_karp/`.
```console
$ cargo build --release
```
To clean the outcomes, run
```console
$ cargo clean
```
again, in any directory below `edmons_karp/`.
## Usage

After the build command, change your directry and move `input.txt`
 to `edmons_karp/target/release/` and run
```console
$ edmons_karp input.txt
```
and you get the output in `output.txt`.

If you need only the value of a flow, you can use `-v` option:
```console
$ edmons_karp -v input.txt
```
Besides, you can run
```console
$ run.sh [-v] input.txt
```
in `EDMONS_KARP/` to perform the above at once.

## Examples

`input.txt` should contain:

- the numbers of vertices and edges.
- the vertex numbers of the source and the sink.
- the directed edges and their capacity.

```
# input.txt
6 9
0 5
0 1 5
0 2 2
0 3 9
1 2 2
2 4 3
3 1 1
3 4 4
3 5 2
4 5 10

```

The output for the input is:
```
# output.txt
9
src, sink: 0, 5
(from, to): flow/capacity
(0, 1): 1/5
(0, 2): 2/2
(0, 3): 6/9
(1, 2): 1/2
(2, 4): 3/3
(3, 1): 0/1
(3, 4): 4/4
(3, 5): 2/2
(4, 5): 7/10
```
If you run the prograpm with `-v` option, the output is:
```
# output.txt
9
```

## Tests
Run
```console
$ test.sh
```
 to see the program works on the test cases in 
`../test/instances/`, though actually, the ansers for case 16 and 38 do not coincide with
the ones in `../test/instances/outputs/`.

I suspect that `output16.txt` and `output38.txt` might be wrong.

## Information

For information involving the implementation and the interfaces of modules, you can run
```console
$ cargo doc --no-deps --open
```
in `edmons_karp/` and consult the genarated document.
