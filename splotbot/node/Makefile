debug: splotbot_wrapper.cc binding.gyp data/experiments.db:
	CXXFLAGS='-std=c++0x' node-gyp configure
	CXXFLAGS='-std=c++0x' node-gyp build -d

release: splotbot_wrapper.cc binding.gyp data/experiments.db:
	CXXFLAGS='-std=c++0x' node-gyp configure
	CXXFLAGS='-std=c++0x' node-gyp build

data/experiments.db:
	-@mkdir data 2>/dev/null || true
	sqlite3 data/experiments.db < logging/data/table.sql


clean:
	rm -r build
