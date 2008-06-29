local_dir := terminal
local_src := $(wildcard $(local_dir)/*.cpp)
local_objs := $(subst .cpp,.o,$(local_src))
sources += $(local_src)

programs += $(bin_dir)/aghphone

$(bin_dir)/aghphone: $(local_objs) gui/dummyui.o common/globals.o common/main.o common/tools.o common/codecfactory.o common/ringbuffer.o ice/iface.o ice/icecommon.o transceiver/transceiver.o common/codecs/dummycodec.o directory/directory.o
		$(ECHO_COMPILE_EXEC)
		$(CXX) $(LDFLAGS) -o $@ $^
