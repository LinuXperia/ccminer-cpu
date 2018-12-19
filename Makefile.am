
EXTRA_DIST		= autogen.sh README.md README.txt LICENSE.txt \
			  ccminer.sln ccminer.vcxproj ccminer.vcxproj.filters \
			  compat/gettimeofday.c compat/getopt/getopt_long.c

SUBDIRS = compat

bin_PROGRAMS = ccminer

ccminer_SOURCES	= elist.h miner.h compat.h \
			  compat/inttypes.h compat/stdbool.h compat/unistd.h \
			  compat/sys/time.h compat/getopt/getopt.h \
			  crc32.c hefty1.c \
			  sph/sha2.c \
			  ccminer.cpp pools.cpp util.cpp bench.cpp bignum.cpp \
			  api.cpp hashlog.cpp stats.cpp sysinfos.cpp \
			  common/log/BasicLog.h  common/log/ConsoleLog.h  common/log/FileLog.h  common/log/Log.h  common/log/SysLog.h \
			  common/log/BasicLog.cpp  common/log/ConsoleLog.cpp  common/log/FileLog.cpp  common/log/Log.cpp  common/log/SysLog.cpp \
			  common/net/Job.cpp common/net/Job.h \
			  core/Controller.h core/Controller.cpp core/Config.h core/Config.cpp \
			  workers/CpuThread.cpp workers/CpuThread.h \
			  workers/Handle.cpp workers/Handle.h workers/Workers.cpp workers/Workers.h\
			  workers/Worker.cpp workers/Worker.h \
			  workers/MultiWorker.cpp workers/MultiWorker.h \
			  workers/Hashrate.cpp workers/Hashrate.h \
			  crypto/xmr-rpc.cpp crypto/wildkeccak-cpu.cpp \
			  crypto/cryptonight.cpp \
			  crypto/Asm.cpp crypto/Asm.h \
			  crypto/asm/cnv2_main_loop.S \
			  crypto/aesb.cpp  crypto/c_blake256.c  crypto/c_groestl.c  crypto/c_jh.c  crypto/c_skein.c  \
			  Mem.cpp Mem.h \
			  common/config/CommonConfig.cpp  common/config/ConfigLoader.cpp  common/config/ConfigWatcher.cpp \
			  common/net/Pool.cpp net/Network.cpp common/cpu/Cpu.cpp common/crypto/Algorithm.cpp base/tools/String.cpp \
			  common/Platform.cpp common/cpu/BasicCpuInfo.cpp \
			  common/Platform_unix.cpp common/crypto/keccak.cpp


if HAVE_WINDOWS
ccminer_SOURCES += compat/winansi.c Mem_win.cpp
else
ccminer_SOURCES += Mem_unix.cpp
endif

ccminer_LDFLAGS  = $(PTHREAD_FLAGS)
ccminer_LDADD    = @LIBCURL@ @JANSSON_LIBS@ @PTHREAD_LIBS@ @WS2_LIBS@ @OPENMP_CFLAGS@ @LIBS@ -luv
ccminer_CPPFLAGS = @LIBCURL_CPPFLAGS@ @OPENMP_CFLAGS@ $(CPPFLAGS) $(PTHREAD_FLAGS) -fno-strict-aliasing $(DEF_INCLUDES) -maes
ccminer_CPPFLAGS += -I./3rdparty

if HAVE_OSX
ccminer_CPPFLAGS += -I/usr/local/llvm/lib/clang/4.0.0/include
ccminer_LDFLAGS += -L/usr/local/llvm/lib
ccminer_LDADD += -lomp
endif

