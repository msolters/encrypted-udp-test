all: encrypted-udp-test

TARGET = srf06-cc26xx
BOARD = sensortag/cc2650

CONTIKI=../..

CFLAGS += -DPROJECT_CONF_H=\"project-conf.h\"
CFLAGS += -DDEV_SN=\"$(DEV_SN)\"

# linker optimizations
SMALL=1

CONTIKI_WITH_IPV6 = 1
include $(CONTIKI)/Makefile.include
