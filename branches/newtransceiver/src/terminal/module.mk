local_dir := terminal
local_src := $(wildcard $(local_dir)/*.cpp)
local_objs := $(subst .cpp,.o,$(local_src))
sources += $(local_src)

programs += $(bin_dir)/aghphone

$(bin_dir)/aghphone: $(local_objs) \
	common/tools.o common/codecfactory.o common/ringbuffer.o ice/iface.o \
	transceiver/ccrtp/aghrtpsession.o common/codecs/dummycodec.o \
	transceiver/alsa/devicealsa.o transceiver/alsa/devicefactoryalsa.o \
	transceiver/alsa/audioalsa.o transceiver/ccrtp/transportccrtp.o \
	transceiver/transceiver.o transceiver/transceiverfactory.o common/msgbuffer.o
		$(ECHO_COMPILE_EXEC)
		$(CXX) $(LDFLAGS) -o $@ $^