export ARCHS = armv7 armv7s arm64 
export TARGET = iphone:clang
SDKVERSION_armv6 = 5.1
TARGET_IPHONEOS_DEPLOYMENT_VERSION = 3.0
TARGET_IPHONEOS_DEPLOYMENT_VERSION_arm64 = 7.0

TOOL_NAME = MemoryCheat
MemoryCheat_FILES = main.mm
MemoryCheat_LDFLAGS += -Wl,-segalign,4000
MemoryCheat_CODESIGN_FLAGS = -Sent.xml
MemoryCheat_PRIVATE_FRAMEWORKS = Foundation,libsystem_kernel

include theos/makefiles/common.mk
include $(THEOS_MAKE_PATH)/tool.mk
