default: compile_all

compile_all: node_files cpp_files

cpp_files: cpp
	(cd cpp ; make)

node_files: node
	(cd node ; npm install)
	(cd node ; make)
