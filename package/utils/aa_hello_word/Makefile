#
# Copyright (C) 2010 Jo-Philipp Wich <xm@subsignal.org>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=hello_word
PKG_RELEASE:=1

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)-$(BUILD_VARIANT)
PKG_USE_MIPS16:=0

include $(INCLUDE_DIR)/package.mk

define Package/hello_word
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Simplest mips prog to test mips assembler
  MAINTAINER:=test <xm@subsignal.org>
  DEPENDS:=+libpthread
endef

define Package/hello_word/description
 Hello_word is a tiny assembler app to test binutils and generated insn support 
 on a field processos cores.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile
	$(TARGET_CROSS)as -o $(PKG_BUILD_DIR)/hw.o hw.S
	$(TARGET_CROSS)ld -o $(PKG_BUILD_DIR)/hw $(PKG_BUILD_DIR)/hw.o
	$(TARGET_CC) $(TARGET_CFLAGS) -o $(PKG_BUILD_DIR)/treadspeed test3.c -pthread
endef

define Package/hello_word/install
	$(INSTALL_DIR) /tmp/lx
#$(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/hw /tmp/lx/hw
#$(1)/usr/sbin/hw
endef

$(eval $(call BuildPackage,hello_word))
