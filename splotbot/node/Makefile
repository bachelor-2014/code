debug: splotbot_wrapper.cc binding.gyp
	CXXFLAGS='-std=c++0x' node-gyp configure
	CXXFLAGS='-std=c++0x' node-gyp build -d

release: splotbot_wrapper.cc binding.gyp
	CXXFLAGS='-std=c++0x' node-gyp configure
	CXXFLAGS='-std=c++0x' node-gyp build


clean:
	rm -r build
