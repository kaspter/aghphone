local_dir := transceiver/alsa
local_src := $(wildcard $(local_dir)/*.cpp)
local_objs := $(subst .cpp,.o,$(local_src))
sources += $(local_src)
