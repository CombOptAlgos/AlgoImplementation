use std;
use std::io::stderr;
use std::io::BufWriter;
use std::io::prelude::*;
use std::str::FromStr;

/// The `Edge` type to express an edge with `capacity` and `flow`.
#[derive(Copy, Clone)]
pub struct Edge {
    pub dest: usize,
    pub capacity: f64,
    pub flow: f64
}

/// The `Graph` type to express an instance of graph flow problems.
pub struct Graph {
    pub v_size: usize,
    pub e_size: usize,
    pub src: usize,
    pub sink: usize,
    pub v: Vec<Vec<Edge>>  // adjecent list representation
}

impl Edge {
    /// Prints an edge.
    #[allow(dead_code)]
    pub fn print(&self, source: usize) {
	println!("source, dest, capacity, flow: {}, {}, {}, {}",
		 source, self.dest, self.capacity, self.flow);
    }
}

impl Graph {
    /// Returns a newly constructed graph initialized with specified parameters and
    /// an empty edge set.
    pub fn new(v_size: usize, e_size: usize,
	       src: usize, sink: usize) -> Graph {
	let mut v = Vec::new();
	for _ in 0 .. v_size {
	    v.push(Vec::new());
	};
	Graph { v_size, e_size, src, sink, v }
    }
    
    /// Adds to a graph an edge with flow 0.0 as well as other parameters
    /// specified in the argumetns.
    pub fn add_edge(&mut self, src: usize, dest: usize, 
		    capacity: f64, flow: f64) {
	let edges = &mut self.v[src];
	let mut done = false;

	// check if a parallel edge already exsts
	for i in 0 .. edges.len() {
	    if edges[i].dest == dest {
		println!("add_edge: parallel edge {}, {}, {} is merged to a one that already exists.",
		src, dest, capacity);
		edges[i].capacity += capacity;
		edges[i].flow += flow;
		done = true;
	    }
	}
	if src < self.v_size && dest < self.v_size 
	    && !done {
	    let edge = Edge {
		dest,
		capacity,
		flow // default flow value
	    };
	    
	    edges.push(edge);
	} else if !done {
	    let _ = writeln!(stderr(), "error: index of a vertex is out of the specified bound.");
	}
    }

    /// Increases the flow of the edge from `s` to `t` by `val`.
    /// `val` is signed, i.e. decreases the flow if `val` is negative.
    pub fn gain_flow(&mut self, s: usize, t: usize, val: f64) {
	let edges = &mut self.v[s];
	
	for i in 0 .. edges.len() {
	    if edges[i].dest == t {
	    	let flow = edges[i].flow + val;
	    	if flow >= 0. && flow <= edges[i].capacity {
	    	    edges[i].flow = flow;
	    	} else {
	    	    let _ = writeln!(stderr(),
	    	    		     "error: graph::gain_flow: cannot add `val` to `self.flow`");
	    	};
	    	break;
	    };
	};
    }
    
    /// Returns a new copy of a graph whose edges are the reverses of the old.
    pub fn rev_copy(&self) -> Graph {
	let mut graph = Graph::new(self.v_size,
				   self.e_size,
				   self.src,
				   self.sink);
	let edges = &self.v;
	for i in 0 .. edges.len() {
	    for edge in &edges[i] {
		// add a reverse edge
		graph.add_edge(edge.dest, i, edge.flow, 0.);
	    };
	};

	graph  // return the constructed reverse graph
    }

    /// Formats and pritns the contents of a graph.
    #[allow(dead_code)]
    pub fn print(&self) {
	println!("size: {}", self.v_size);
	println!("src, sink: {}, {}", self.src, self.sink);
	
	let v = &self.v;
	for i in 0 .. self.v_size {
	    for edge in &(v[i]) {
		edge.print(i);
	    };
	};
    }

    /// Write the flow of a graph to `writer`.
    pub fn write_flow<W>(&self, writer: &mut BufWriter<W>)
	where W: Write
    {
	let _ = writeln!(writer, "src, sink: {}, {}", self.src, self.sink);

	let edges = &self.v;
	let _ = writeln!(writer, "(from, to): flow/capacity");
	for i in 0 .. edges.len() {
	    for e in &edges[i] {
		let _ = writeln!(writer, "({}, {}): {}/{}",
				 i, e.dest, e.flow, e.capacity);
	    };
	};
    }

    /// Write the value of flow to `writer`.
    pub fn write_flow_val<W>(&self, writer: &mut BufWriter<W>)
	where W: Write
    {
	let edges = &self.v[self.src];
	let mut val = 0.;
	for e in edges {
	    val += e.flow;
	};

	let _ = writeln!(writer, "{}", val);
    }
} // impl Graph


// graph scanner
enum States {
    Sizes,
    SrcAndSink,
    Edges
}

/// The `GenError` type to experess multiple error types at once.
pub type GenError = Box<dyn std::error::Error>;
/// The `GenResult` type with `GenError` as its error type.
pub type GenResult<T> = Result<T, GenError>;

/// An error handler.
fn handle_err(msg: &str) {
    let _ = writeln!(stderr(), "{}", msg);
    std::process::exit(1);
}

/// Returns a graph constructed from data
/// scaned and parsed from `reader`.
pub fn scan_reader<R>(reader: R) -> GenResult<Graph>
    where R: BufRead
{
    let mut state: States = States::Sizes;
    let mut v_size: usize = 0;
    let mut e_size: usize = 0;
    let mut src: usize = 0;
    let mut sink: usize = 0;
    let mut graph: Graph = Graph::new(v_size, e_size, src, sink); // dummy
    let err_msg = "error: wrong input format";

    for line_result in reader.lines() {
	let line = line_result?;
	let nums = line.trim().split(' ').collect::<Vec<_>>();

	match state {
	    States::Sizes => if nums.len() == 2 {
		v_size = usize::from_str(nums[0])?;
		e_size = usize::from_str(nums[1])?;
		state = States::SrcAndSink;
	    } else {
		handle_err(err_msg);
	    },

	    States::SrcAndSink => if nums.len() == 2 {
		src = usize::from_str(nums[0])?;
		sink = usize::from_str(nums[1])?;
		graph = Graph::new(v_size, e_size, src, sink);
		state = States::Edges;
	    } else {
		handle_err(err_msg);
	    },

	    States::Edges => if nums.len() == 3 {
		graph.add_edge(usize::from_str(nums[0])?,
			       usize::from_str(nums[1])?,
			       f64::from_str(nums[2])?,
			       0.);
	    } else if nums.len() != 0 {
		handle_err(err_msg);
	    } // if nums.len() == 0, then the scanner simply ignore the line
	};
    };

    Ok(graph) // return the scanned graph
}
