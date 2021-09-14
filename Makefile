
BUILD_DEBUG:=false

ifndef EMSDK
$(error EMSDK not defined)
endif

noop :=
space := $(noop) $(noop)
comma := ,

EMSDK_INC_DIR := $(EMSDK)/upstream/emscripten/cache/sysroot/include/emscripten
EMSDK_LIB_DIR := $(EMSDK)/upstream/emscripten/cache/sysroot/lib/wasm32-emscripten
OpenCASCADE_INCLUDE_DIR :=$(EMSDK)/upstream/emscripten/cache/sysroot/include/opencascade
OpenCASCADE_LIB_DIR :=$(EMSDK)/upstream/emscripten/cache/sysroot/lib

OpenCASCADE_MODULES := TKRWMesh TKBinXCAF TKBin TKBinL TKOpenGl TKXCAF TKVCAF TKCAF TKV3d TKHLR TKMesh TKService TKShHealing TKPrim TKTopAlgo TKGeomAlgo TKBRep TKGeomBase TKG3d TKG2d TKMath TKLCAF TKCDF TKernel TKFillet TKBool TKBO TKOffset

LIBS:= $(foreach V, $(OpenCASCADE_MODULES),	$(OpenCASCADE_LIB_DIR)/lib$(V).a)

EXPORT_FUNCTION_NAMES := _main _Sum
EXPORT_FUNCTIONS_STRING := $(subst $(space),$(comma),$(EXPORT_FUNCTION_NAMES))

CPPFLAGS += -g -fdebug-compilation-dir="."
CPPFLAGS += -I$(OpenCASCADE_INCLUDE_DIR) -I$(EMSDK_INC_DIR)
CPPFLAGS += --bind

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<

all: demoapp.js
	@echo $(MAKE_VERSION)
	@echo $(EXPORT_FUNCTIONS_STRING)

demoapp.js: src/main.o src/my_class.o src/model_base.o
	$(CXX) $(CPPFLAGS) $(CFLAGS) -o $@ src/main.o src/my_class.o src/model_base.o -s EXPORTED_FUNCTIONS='[$(EXPORT_FUNCTIONS_STRING)]' -L$(OpenCASCADE_LIB_DIR) -L$(EMSDK_LIB_DIR) $(LIBS)

clean:
	$(RM) -r src/*.o *.wasm *.js

.PHONY: all clean

print-%: ; @echo $* = $($*)
