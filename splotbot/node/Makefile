debug: splotbot_wrapper.cc binding.gyp data/experiments.db data/images
	CXXFLAGS='-std=c++0x' node-gyp configure
	CXXFLAGS='-std=c++0x' node-gyp build -d

release: splotbot_wrapper.cc binding.gyp data/experiments.db data/images
	CXXFLAGS='-std=c++0x' node-gyp configure
	CXXFLAGS='-std=c++0x' node-gyp build

data/experiments.db:
	-@mkdir data 2>/dev/null || true
	sqlite3 data/experiments.db < ../cpp/logging/data/table.sql

data/images:
	mkdir -p data/images


clean:
	rm -r build
