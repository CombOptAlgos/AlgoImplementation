## How to generate test instance

```bash
mkdir build
cd build
cmake ..
make 
./Undirected_Weighted_Graphs > ../output_txt/test.txt
cd ..
```

## How to visualize

```bash
cd graphviz
mkdir build
cd build
cmake ..
make
./graphviz < ../../output_txt/test.txt > ../output_dot/test.dot

dot -Tpng < ../output_dot/test.dot > ../../output_png/test.png 
open ../../output_png/test.png
cd ..
```

