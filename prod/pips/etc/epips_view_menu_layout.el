;; The following description of the ``View'' menu is automatically generated from ``pipsmake-rc.tex'' through \verb|./generate_all_menu_documentation|.

(setq epips-view-menu-layout '(
	("Sequential View" "PRINTED_FILE" epips-display-fortran-file "sequential")
	("User View" "PARSED_PRINTED_FILE" epips-display-fortran-file "user")
	("Alias View" "ALIAS_FILE" epips-display-plain-file "-")
	("Control Graph Sequential View" "GRAPH_PRINTED_FILE" epips-display-graph-file "-")
	("Dependence Graph View" "DG_FILE" epips-display-plain-file "DG")
	("Callgraph View" "CALLGRAPH_FILE" epips-display-xtree-file "callgraph")
	("Graphical Call Graph" "DVCG_FILE" epips-display-graph-file "callgraph")
	("ICFG View" "ICFG_FILE" epips-display-plain-file "ICFG")
	("Distributed View" "WP65_COMPUTE_FILE" epips-display-distributed-file "WP65_PE")
	("Parallel View" "PARALLELPRINTED_FILE" epips-display-fortran-file "parallel")
	("Flint View" "FLINTED_FILE" epips-display-plain-file "-")
))
