
BUILD_DEBUG:=false
OpenCASCADE_INCLUDE_DIR :=/usr/local/include/opencascade
OpenCASCADE_MODULES := TKRWMesh TKBinXCAF TKBin TKBinL TKOpenGl TKXCAF TKVCAF TKCAF TKV3d TKHLR TKMesh TKService TKShHealing TKPrim TKTopAlgo TKGeomAlgo TKBRep TKGeomBase TKG3d TKG2d TKMath TKLCAF TKCDF TKernel TKFillet TKBool TKBO TKOffset

LIBS:= $(foreach V, $(OpenCASCADE_MODULES),	-l$(V))

CPPFLAGS += -g
CPPFLAGS += -I$(OpenCASCADE_INCLUDE_DIR)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<

all: test
	@echo $(MAKE_VERSION)

test: test.o $(lib1_OBJS)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -o $@ test.o $(LIBS)

clean:
	$(RM) -r *.o test

.PHONY: all clean

print-%: ; @echo $* = $($*)
