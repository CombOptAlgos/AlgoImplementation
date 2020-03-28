mod graph;
mod alg;

use std;

use std::io::{BufReader, BufWriter, stderr};
use std::io::prelude::*;
use std::fs::File;
use std::path::PathBuf;

/// Takes a filename from the command line argument, parses it,
/// compute the maximum flow, and prints it to a file named 
/// output.txt.
fn main() {
    let usage = "usage: edmons_karp [-v] FILE";
    let mut args = std::env::args().skip(1);
    let mut is_debug = true;
    let mut file_option = args.next();

    // if let None = file_option {
    // 	let _ = writeln!(stderr(), "{}", usage);
    // 	std::process::exit(1);
    // };

    // handle command line options.
    loop {
	match file_option {
	    None => {
		let _ = writeln!(stderr(), "{}", usage);
		std::process::exit(1);
	    },

	    Some(ref arg) if arg == "-v" => {
		is_debug = false;
		file_option = args.next();
	    },

	    Some(ref arg) if arg.starts_with('-') => {
		let _ = writeln!(stderr(), "{}", usage);
		std::process::exit(1);
	    },
	    
	    _ => break
	};
    };
    
    let file = PathBuf::from(file_option.unwrap());

    // Expects one command line argument, not two or more.
    match args.next() {
	Some(_) => { let _ = writeln!(stderr(), "{}", usage);
		     std::process::exit(1) },
	None => ()
    };

    let f = File::open(file).unwrap();
    let graph_result = graph::scan_reader(BufReader::new(f));
    if let Err(err) = graph_result {
	let _ = writeln!(stderr(), "error: {}", err);
	std::process::exit(1);
    };
    let mut graph = graph_result.unwrap();
    
    // FOR DEBUG:
    // graph.print();
    // graph.rev_copy().print();

    alg::edmons_karp(&mut graph);
    let out = File::create("output.txt").unwrap();
    let mut out_writer = BufWriter::new(out);
    graph.write_flow_val(&mut out_writer);
    if is_debug {
	graph.write_flow(&mut out_writer);
    };
}
