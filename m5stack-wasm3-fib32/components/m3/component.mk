#
# Main Makefile. This is basically the same as a component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)
COMPONENT_SRCDIRS := src
COMPONENT_ADD_INCLUDEDIRS := src

CFLAGS := -DESP32
CFLAGS := -DM3_IN_IRAM
CFLAGS := -Dd_m3LogOutput=false
CFLAGS := -O3
CFLAGS := -freorder-blocks
CFLAGS := -mlongcalls

COMPONENT_ADD_LDFRAGMENTS += linker.lf
