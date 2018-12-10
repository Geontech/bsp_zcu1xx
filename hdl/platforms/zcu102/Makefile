$(if $(realpath $(OCPI_CDK_DIR)),,\
  $(error The OCPI_CDK_DIR environment variable is not set correctly.))
# This is an HDL platform Makefile for the "zcu102" platform

Libraries=axi zynq_ultra sdp

Configurations=base

ExportFiles=zcu102.mk zcu102.xdc zcu102_bit.xdc

include $(OCPI_CDK_DIR)/include/hdl/hdl-platform.mk
