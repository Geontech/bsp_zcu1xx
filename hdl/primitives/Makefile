$(if $(realpath $(OCPI_CDK_DIR)),,\
  $(error The OCPI_CDK_DIR environment variable is not set correctly.))
# To restrict the primitives that are built or run, you can set the Libraries or Cores
# variables to the specific list of which ones you want to build and run, e.g.:
PrimitiveLibraries=zynq_ultra
# PrimitiveCores=core1 core2
# Otherwise all primitives will be built
include $(OCPI_CDK_DIR)/include/hdl/hdl-primitives.mk
