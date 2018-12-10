$(if $(realpath $(OCPI_CDK_DIR)),,\
  $(error The OCPI_CDK_DIR environment variable is not set correctly.))
# This is an HDL platform Makefile for the "zcu111" platform

Libraries=axi zynq_ultra sdp

Configurations=base

ExportFiles=zcu111.mk zcu111.xdc zcu111_bit.xdc

include $(OCPI_CDK_DIR)/include/hdl/hdl-platform.mk
