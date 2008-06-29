local_dir := directory
local_src := $(wildcard $(local_dir)/*.cpp)
local_objs := $(subst .cpp,.o,$(local_src))
sources += $(local_src)
extra_clean += $(local_dir)/directory.cpp $(local_dir)/directory.h $(local_dir)/directory.o

directory/%.cpp: directory/%.ice
		$(ECHO_ICE)
		cd directory && $(SLICE) $(<F)

programs += $(bin_dir)/directory

$(bin_dir)/directory: $(local_objs) directory/directory.o ice/icecommon.o
		$(ECHO_COMPILE_EXEC)
		$(CXX) $(LDFLAGS) -o $@ $^

