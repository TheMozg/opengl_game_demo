BUILD_DIR    := build.out
INSTALL_DIR  := install.out

IS_WINDOWS := $(if $(wildcard C:\Windows),YES,NO)

ifeq ($(IS_WINDOWS),YES)
CMAKE         := cmake.exe
BUILD         := "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\MSBuild.exe"
BUILD_FLAGS   := /nologo /verbosity:minimal ALL_BUILD.vcxproj
INSTALL_FLAGS := /nologo /verbosity:minimal INSTALL.vcxproj
RM            := rmdir /S /Q
SILENT        := > nul
else
CMAKE         := cmake
BUILD         := make
BUILD_FLAGS   :=
INSTALL_FLAGS := install
RM            := rm -rf
SILENT        := > /dev/null
endif


.PHONY: all
all: configure build install

.PHONY: configure
configure: $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CMAKE) -DCMAKE_INSTALL_PREFIX="../$(INSTALL_DIR)" ..

.PHONY: build
build: $(BUILD_DIR)
	cd $(BUILD_DIR) && $(BUILD) $(BUILD_FLAGS)

.PHONY: install
install: $(INSTALL_DIR)
	cd $(BUILD_DIR) && $(BUILD) $(INSTALL_FLAGS)

.PHONY: clean
clean: $(BUILD_DIR) $(INSTALL_DIR)
	$(RM) $(BUILD_DIR)
	$(RM) $(INSTALL_DIR)

$(BUILD_DIR) $(INSTALL_DIR):
	mkdir $@