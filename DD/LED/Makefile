obj-m := gpiomodule.o
gpio-objs:=gpiomodule.o
KDIR := /home/marco/buildroot/buildroot-2021.08/output/build/linux-custom
ARCH ?= arm64


CROSS_COMPILE ?= /home/marco/buildroot/buildroot-2021.08/output/host/bin/aarch64-buildroot-linux-uclibc-
  

export ARCH CROSS_COMPILE


KBUILD_TARGETS	:= clean help modules modules_install

.PHONY: all $(KBUILD_TARGETS)

all: modules
$(KBUILD_TARGETS):
	#$(MAKE) -C $(KDIR) M=$(shell pwd) $@ EXTRA_CFLAGS="$(MY_CFLAGS)"
	$(MAKE) -C $(KDIR) M=$(shell pwd) $@

