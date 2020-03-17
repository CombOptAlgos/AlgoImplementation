import random


class Graph():

    def __init__(self):
        self.V = [[] for i in range(n)]
        self.E = []

    def add_vertices(self.v, w):
        """add vertices v, w and edge {v, w} to the graph
        Parameters:
        -----------
        v, w: int
        """
        self.V.[v].append(w)
        self.V.[w].append(v)
        self.E.append([v, w])


def generate_graph(n, max_m, max_w):
    assert (n-1 <= max_w) and (max_m <= n/2*(n-1)), "imvalid number of edges!"
    


    v_reachable = [0]
    v_not_reachable = [i for i in range(1, n)]


    for i in range(n-1):
        v = random.choice(v_reachable)
        w = random.choice(v_not_reachable)
        v_reachable.append(w)
        v_not_reachable.remove(w)
        add_vertices(v, w)

    n_edges = n-1

    while (n_edges < max_m):
        v = random.randint(0, n-1)
        candidate = [i for i in range(n) if i not in Graph[v]]
        w = random.choice(candidate)
        add_vertices(v, w)
        n_edges += 1

    # Save results
    path_w = "./output_txt/test.txt"
    with open(path_w, mode='w') as f:
        f.write(str(n)+" "+str(max_m)+"\n")
        for e in edges:
            if e[0] != e[1]:
                f.write(str(e[0])+" "+str(e[1])+" "+str(random.randint(1, max_w))+"\n")

if __name__ == "__main__":
    generate_graph(5, 10, 10)
