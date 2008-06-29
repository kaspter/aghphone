local_dir := ice
local_src := $(wildcard $(local_dir)/*.cpp)
local_objs := $(subst .cpp,.o,$(local_src))
sources += $(local_src)
extra_clean += $(local_dir)/iface.cpp $(local_dir)/iface.h $(local_dir)/iface.o

ice/%.cpp: ice/%.ice
		$(ECHO_ICE)
		cd ice && $(SLICE) $(<F)
