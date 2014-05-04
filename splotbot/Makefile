default: compile_all

compile_all: node_files

cpp_files: cpp node
	$(MAKE) -C cpp

node_files: node
	#(cd node ; npm install)
	$(MAKE) -C node

rucolang_files:
	$(MAKE) -C cpp/rucolang
