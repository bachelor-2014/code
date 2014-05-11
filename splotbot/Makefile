default: compile_all

compile_all: node_files

cpp_files: cpp node rucolang_files
	$(MAKE) -C cpp

node_files: node rucolang_files
	#(cd node ; npm install)
	$(MAKE) -C node

rucolang_files:
	$(MAKE) -C cpp/rucolang
service:
	cp evobot.sh /etc/init.d/evobot
	chmod +x /etc/init.d/evobot
	update-rc.d evobot defaults
