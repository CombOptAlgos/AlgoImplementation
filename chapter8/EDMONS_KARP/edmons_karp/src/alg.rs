use super::graph;
use std;
use std::clone::Clone;
use std::collections::VecDeque;


/// The `ResGraph` type to represent a residual graph.
pub struct ResGraph<'a> {
    graph: &'a mut graph::Graph,
    v_org: Vec<Vec<graph::Edge>>,  // edges of an original graph
    v_rev: Vec<Vec<graph::Edge>>  // their reverse edges
}

/// The `ResVertex` type to distinguish between original vertices and reverse vertices.
/// See "Implementation detail" commnet in the source code.
// Implementation detail: In general, we know which edge (original/reverse) to use
// by the target, rather than by the source. For example, 
// (Org(1), Rev(3)) and (Rev(1), Rev(3)) both mean the edge (1, 3) of the reverse edges
// while (Rev(1), Org(3)) means the one of the original.
#[derive(Copy, Clone)]
enum ResVertex {
    Org(usize),
    Rev(usize)
}

impl ResVertex {
    /// Returns the content of `self`.
    fn id(&self) -> usize {
	match self {
	    ResVertex::Org(v) => *v,
	    ResVertex::Rev(v) => *v
	}
    }
}

impl<'a> ResGraph<'a> {
    /// Returns a newly constructed value of type `ResGraph`.
    pub fn new(graph: &'a mut graph::Graph) -> ResGraph {
	let v_org = graph.v.clone();
	let rev_graph = graph.rev_copy();
	ResGraph { graph,
		   v_org,
		   v_rev: rev_graph.v.clone() }
    }

    /// Returns the edge specified by source `s` and target `t` if there's any.
    fn edge(&self, s: usize, t: ResVertex) -> Option<graph::Edge> {
	let edges = match t {
	    ResVertex::Org(_) => &self.v_org[s],
	    ResVertex::Rev(_) => &self.v_rev[s]
	};

	let mut edge = None;
	for e in edges {
	    if e.dest == t.id() {
		edge = Some(*e);
		break;
	    };
	};

	match edge {
	    Some(_) => (),
	    None => println!("error: no edge between {} & {}.", s, t.id())
	};

	edge
    }

    /// Rerturns the adjacent list of a vertex `v`.
    fn adjs_of(&self, v: usize) -> Vec<ResVertex> {
	let mut adjs = Vec::new();
	let org_edges = &self.v_org[v];
	let rev_edges = &self.v_rev[v];

	for e in org_edges {
	    if e.capacity > 0. {
		adjs.push(ResVertex::Org(e.dest));
	    };
	};

	for e in rev_edges {
	    if e.capacity > 0. {
		adjs.push(ResVertex::Rev(e.dest));
	    };
	};

	adjs
    }

    /// increase the capacity of the edge from `s` to `t` by `val`.
    fn gain_capacity(&mut self, s: usize, t: ResVertex, val: f64) {
	let edges = match t {
	    ResVertex::Org(_) => &mut self.v_org[s],
	    ResVertex::Rev(_) => &mut self.v_rev[s]
	};

	for i in 0 .. edges.len() {
	    if edges[i].dest == t.id() {
		edges[i].capacity += val;
		break;
	    };
	};
    }
    
    /// decrease the capacity of the edge from `s` to `t` by `val`.
    fn reduce_capacity(&mut self, s:usize, t: ResVertex, val: f64) {
	let edges = match t {
	    ResVertex::Org(_) => &mut self.v_org[s],
	    ResVertex::Rev(_) => &mut self.v_rev[s]
	};

	for i in 0 .. edges.len() {
	    if edges[i].dest == t.id() {
		if val <= edges[i].capacity {
		    edges[i].capacity -= val;
		};
		break;
	    };
 	};
    }

    /// Augments the flow of a residual graph along a given path.
    fn augment_along(&mut self, path: &[ResVertex]) {
	// identify the bottle neck.
	let mut min = -1.;
	for i in 0 .. path.len() - 1 {
	    let edge = self.edge(path[i].id(), path[i+1]).unwrap();
	    if min < 0. || edge.capacity < min {
		min = edge.capacity;
	    };
	};

	if min > 0. {
	    for i in 0 .. path.len() - 1 {
		match (path[i].id(), path[i+1]) {
		    (s, t @ ResVertex::Org(_)) => {
			self.graph.gain_flow(s, t.id(), min);
			self.reduce_capacity(s, t, min);
			self.gain_capacity(t.id(), ResVertex::Rev(s), min);
		    },
		    (s, t @ ResVertex::Rev(_)) => {
			self.graph.gain_flow(s, t.id(), -min);
			self.reduce_capacity(s, t, min);
			self.gain_capacity(t.id(), ResVertex::Org(s), min);
		    }
		}; // match ..
	    }; // for ..
	}; // if ..
    }
} // impl ResGraph

/// Enqueues the vertices in `adjs` to `work_list`
/// and update the corresponding entries of `visited`.
fn push_adjs(visited: &mut [Option<ResVertex>],
	     prev: ResVertex,
	     work_list: &mut VecDeque<ResVertex>,
	     adjs: &[ResVertex]) {
    for adj in adjs {
	if visited[adj.id()].is_none() {
	    visited[adj.id()] = Some(prev);
	    work_list.push_back(*adj);
	};
    };
}

/// Performs BFS to find one of the shortest paths in `graph`
/// from `graph.src` to `graph.sink` 
/// consisting of edges with positive capacities.
fn bfs(res_graph: &ResGraph) -> Option<Vec<ResVertex>> {
    let mut visited = vec![None; res_graph.graph.v_size];
    let mut work_list = VecDeque::new();
    let src = res_graph.graph.src;
    let sink = res_graph.graph.sink;
    let mut path = Vec::new();
    let mut curr_v = ResVertex::Org(src); // contains the vertex we're on.
    
    // initialization
    visited[src] = Some(curr_v);
    push_adjs(&mut visited, curr_v,
	      &mut work_list, &res_graph.adjs_of(src));
    
    while curr_v.id() != sink && !work_list.is_empty() {
	curr_v = work_list.pop_front().unwrap();
	push_adjs(&mut visited, curr_v,
		  &mut work_list, &res_graph.adjs_of(curr_v.id()));
    };
    
    if curr_v.id() == sink {
	while curr_v.id() != src {
	    path.push(curr_v);
	    curr_v = visited[curr_v.id()].unwrap();
	};
	// push src to the `path`
	path.push(curr_v);
	path.reverse();
	Some(path)
    } else {
	None
    }
}


/// Computes the maximum flow from `graph.src` to `graph.sink`
/// and updates `graph.flow`.
pub fn edmons_karp(g: &mut graph::Graph) {
    let mut res_graph = ResGraph::new(g);

    while let Some(path) = bfs(&res_graph) {
	res_graph.augment_along(&path);
    };
}
