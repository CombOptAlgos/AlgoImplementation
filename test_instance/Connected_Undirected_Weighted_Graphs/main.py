import random

N = 5
MAX_M = 10
MAX_W = 10
assert (N-1 <= MAX_M) and (MAX_M <= N/2*(N-1)), "imvalid number of edges!"

Graph = [[] for i in range(N)]
edges = []

v_reachable = [0]
v_not_reachable = [i for i in range(1, N)]


def add_vertices(v, w):
    edges.append([v, w])
    Graph[v].append(w)
    Graph[w].append(v)


def main():
    for i in range(N-1):
        v = random.choice(v_reachable)
        w = random.choice(v_not_reachable)
        v_reachable.append(w)
        v_not_reachable.remove(w)
        add_vertices(v, w)

    n_edges = N-1

    while (n_edges < MAX_M):
        v = random.randint(0, N-1)
        candidate = [i for i in range(N) if i not in Graph[v]]
        w = random.choice(candidate)
        add_vertices(v, w)
        n_edges += 1

    # Save results
    path_w = "./output_txt/test.txt"
    with open(path_w, mode='w') as f:
        f.write(str(N)+" "+str(MAX_M)+"\n")
        for e in edges:
            if e[0] != e[1]:
                f.write(str(e[0])+" "+str(e[1])+" "+str(random.randint(1, MAX_W))+"\n")

if __name__ == "__main__":
    main()
