CC = gcc
CFLAGS = -Wall -g

NLLIBNAME = libnl-1
LIBTCMD_DIR := ../libtcmd

LDLIBS += -ltcmd $(shell pkg-config --libs $(NLLIBNAME)) -lrt
CFLAGS += $(shell pkg-config --cflags $(NLLIBNAME)) -I$(LIBTCMD_DIR) -L$(LIBTCMD_DIR)

athtestcmd: athtestcmd.c athtestcmd.h testcmd.h
	$(MAKE) -C $(LIBTCMD_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

clean:
	rm -f athtestcmd
