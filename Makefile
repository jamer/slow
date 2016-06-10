CXXFLAGS := -std=c++14 -I.

SOURCES := \
	src/args.cpp \
	src/main.cpp \
	src/slower.cpp \
	src/slowers/mach.cpp \
	src/slowers/unix.cpp

slow: $(SOURCES)
	$(CXX) -o slow $(SOURCES) $(CXXFLAGS)
