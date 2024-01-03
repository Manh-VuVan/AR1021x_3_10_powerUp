-include .config

MAKEFLAGS += --no-print-directory

PREFIX ?= /usr
SBINDIR ?= $(PREFIX)/sbin
MANDIR ?= $(PREFIX)/share/man
PKG_CONFIG ?= pkg-config

MKDIR ?= mkdir -p
INSTALL ?= install
CC ?= "gcc"
### Manh edit ###
#CC=$(TOOLPREFIX)gcc
CFLAGS ?= -O2 -g
CFLAGS += -DWLAN_API_NL80211 -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration

ifdef IW_CFLAGS
CFLAGS = ${IW_CFLAGS}
endif
ifdef IW_LDFLAGS
LDFLAGS = ${IW_LDFLAGS}
endif

OBJS = athtestcmd.o libtcmd.o nl80211.o os.o
#OBJS += sections.o
ALL = athtestcmd

#ifdef BUILD_LIBNL
#LIBS += ${INCLUDE_LIBNL11_LIB}
#CFLAGS += -I${INCLUDE_LIBNL11_HEADER}
#else
#NL1FOUND := $(shell $(PKG_CONFIG) --atleast-version=1 libnl-1 && echo Y)
#NL2FOUND := $(shell $(PKG_CONFIG) --atleast-version=2 libnl-2.0 && echo Y)
NL1FOUND := Y
#ifeq ($(NL1FOUND),Y)
#NLLIBNAME = libnl-1
#endif
TCMD := $(shell pwd)
CFLAGS += -I$(TCMD)/../libnl-1/include
LIBS += -L$(TCMD)/../libnl-1/lib -lnl
#CFLAGS += -I/home/tukun/AR1021_ACS/WLAN-AIO_ORG/apps/libnl-1/include
#LIBS += -L/home/tukun/AR1021_ACS/WLAN-AIO_ORG/apps/libnl-1/lib -lnl
#ifeq ($(NL2FOUND),Y)
#CFLAGS += -DCONFIG_LIBNL20
#LIBS += -lnl-genl
#NLLIBNAME = libnl-2.0
#endif

#ifeq ($(NLLIBNAME),)
#$(error Cannot find development files for any supported version of libnl)
#endif

#LIBS += $(shell $(PKG_CONFIG) --libs $(NLLIBNAME))
#CFLAGS += $(shell $(PKG_CONFIG) --cflags $(NLLIBNAME))
#endif

#LIBS += -static -pthread -lrt -ldl
### Manh edit ###
LIBS += -pthread -lrt -ldl -lc -lgcc_eh -Bdynamic -lgcc_s -Bstatic
ifeq ($(V),1)
Q=
NQ=true
else
Q=@
NQ=echo
endif

all: $(ALL)

#VERSION_OBJS := $(filter-out version.o, $(OBJS))

#version.c: version.sh $(patsubst %.o,%.c,$(VERSION_OBJS)) nl80211.h athtestcmd.h Makefile \
#		$(wildcard .git/index .git/refs/tags)
#	@$(NQ) ' GEN ' $@
#	$(Q)./version.sh $@

%.o: %.c athtestcmd.h nl80211.h libtcmd.h nl80211_drv.h os.h testcmd.h
	@$(NQ) ' CC  ' $@
	$(Q)$(CC) $(CFLAGS) -c -o $@ $< -lm

athtestcmd:	$(OBJS)
	@$(NQ) ' CC  ' athtestcmd
	$(Q)$(CC) $(LDFLAGS) $(OBJS) $(LIBS)  -lm -o athtestcmd

check:
	$(Q)$(MAKE) all CC="REAL_CC=$(CC) CHECK=\"sparse -Wall\" cgcc"

%.gz: %
	@$(NQ) ' GZIP' $<
	$(Q)gzip < $< > $@

install: athtestcmd athtestcmd.8.gz
#	@$(NQ) ' INST athtestcmd'
#	$(Q)$(MKDIR) $(DESTDIR)$(SBINDIR)
#	$(Q)$(INSTALL) -m 755 athtestcmd $(DESTDIR)$(SBINDIR)
#	@$(NQ) ' INST iw.8'
#	$(Q)$(MKDIR) $(DESTDIR)$(MANDIR)/man8/
#	$(Q)$(INSTALL) -m 644 iw.8.gz $(DESTDIR)$(MANDIR)/man8/

clean:
	$(Q)rm -f iw *.o *~ *.gz *-stamp athtestcmd
#	$(Q)rm -f iw *.o *~ *.gz version.c *-stamp
