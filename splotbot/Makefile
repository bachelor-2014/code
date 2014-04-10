default: compile_all

compile_all: node cpp mendelf

code: cpp
	(cd cpp ; make)

node: node
	(cd node ; npm install)
	(cd node ; make)

mendelf: ../lib/BeBoPr
	(cd ../lib/BeBoPr ; make)
