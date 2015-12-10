#---------------------------------------------------------------------------
# Unpublished Confidential Information of IVES Do not disclose.             
# Copyright (c) 2000-2014 IVES  All Rights Reserved.                        
#---------------------------------------------------------------------------
#!
#  COMPANY  : IVES
# 
#  MODULE   : libbfcp
# 
#  \author  : Philippe Verney
# 
#  \file    : Makefile
# 
#  \brief   : main bfcp library Makefile
# 
#  \version : $Revision: 32 $
# 
#  \date    : $Date: 2010-10-06 17:13:35 +0200 (mer. 06 oct. 2010) $
# 
#  \remarks :
# 
# ------------------------------------------------------------------------- 

ifdef PREFIXE
       MAIN_PREFIXE=$(PREFIXE)
else
       MAIN_PREFIXE=./bfcpsdk
endif

ifeq ($(DEBUG),yes)
       MAIN_CC_OPTS = -D__DEBUG__ -Wall -g -Werror -Wunused -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations  -fPIC
       MAIN_CPP_OPTS = -D__DEBUG__ -Wall -g -Werror -Wunused  -fPIC
       MAIN_LIBS = -g -lpthread
       BINS_PRE=dbg
else
       MAIN_CC_OPTS = -Wall -O2 -Werror -Wunused -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations  -fPIC
       MAIN_CPP_OPTS = -Wall -O2 -Werror -Wunused  -fPIC
       MAIN_LIBS = -lpthread
       BINS_PRE=rel
endif

MAIN_LIBNAME=libbfcp$(BINS_PRE)
MAIN_CC = gcc
MAIN_CPP = g++
MAIN_AR = ar
ifdef LIBSUBDIR
	DELIVERY_LIBS=$(LIBSUBDIR)
else
	DELIVERY_LIBS=lib
endif

DELIVERY_BINS=bin
DELIVERY_INCLUDES=include
DELIVERY_OBJS=$(BINS_PRE)/objs
DELIVERY_DOCS=doc/libbfcp

all: lib so samples

	
samples:
	cd libbfcp ; make install
	cd libbfcp/samples ; make all
	
	
modules: prep
	cd libbfcp/bfcpmsg ; make all 
	cd libbfcp/bfcpsrvctl/bfcpcli ;  make all 
	cd libbfcp/bfcpsrvctl/bfcpsrv ;  make all
	cd libbfcp ; make all
	
prep: 
	echo "CC = $(MAIN_CC)" > Makeinclude
	echo "CPP =$(MAIN_CPP)" >>Makeinclude
	echo "AR = $(MAIN_AR)" >>Makeinclude
	echo "CC_OPTS=$(MAIN_CC_OPTS)" >>Makeinclude
	echo "CPP_OPTS=$(MAIN_CPP_OPTS)" >>Makeinclude
	echo "LIBS=$(MAIN_LIBS)" >>Makeinclude
	echo "INCS_DIR=-I $(PWD)/libbfcp" >>Makeinclude
	echo "SAMPLES_INCS_DIR= -I $(DELIVERY_INCLUDES)" >>Makeinclude
	echo "SAMPLES_LIBS=$(DELIVERY_LIBS)/$(MAIN_LIBNAME).a" >>Makeinclude
	echo "DELIVERY_LIBS=$(DELIVERY_LIBS)" >>Makeinclude
	echo "DELIVERY_BINS=$(DELIVERY_BINS)" >>Makeinclude
	echo "DELIVERY_INCLUDES=$(DELIVERY_INCLUDES)" >>Makeinclude
	echo "DELIVERY_OBJS=$(DELIVERY_OBJS)" >>Makeinclude
	echo "DELIVERY_DOCS=$(DELIVERY_DOCS)" >>Makeinclude
	mkdir -p $(DELIVERY_LIBS)
	mkdir -p $(DELIVERY_BINS)
	mkdir -p $(DELIVERY_INCLUDES)
	mkdir -p $(DELIVERY_OBJS)
	mkdir -p $(DELIVERY_DOCS)
	mkdir -p $(DELIVERY_OBJS)
	rm -f $(DELIVERY_LIBS)/$(MAIN_LIBNAME).a $(DELIVERY_LIBS)/$(MAIN_LIBNAME).so

clean:	prep
	cd libbfcp/bfcpmsg  &&  make clean
	cd libbfcp/bfcpsrvctl/bfcpcli  &&  make clean
	cd libbfcp/bfcpsrvctl/bfcpsrv &&  make clean
	cd libbfcp  &&  make clean
	cd libbfcp/samples  &&  make clean
	rm -f $(DELIVERY_INCLUDES)/*.h $(DELIVERY_LIBS)/$(MAIN_LIBNAME).a $(DELIVERY_LIBS)/$(MAIN_LIBNAME).so
		
install: 
	cd libbfcp/bfcpmsg ; make install 
	cd libbfcp/bfcpsrvctl/bfcpcli ;  make install 
	cd libbfcp/bfcpsrvctl/bfcpsrv ;  make install
	cd libbfcp  &&  make install
	cd libbfcp/samples  &&  make install
	mkdir -p $(MAIN_PREFIXE)/$(DELIVERY_LIBS)
	mkdir -p $(MAIN_PREFIXE)/$(DELIVERY_BINS)
	mkdir -p $(MAIN_PREFIXE)/$(DELIVERY_INCLUDES)
	mkdir -p $(MAIN_PREFIXE)/$(DELIVERY_DOCS)
	@echo Installing BFCP library to $(MAIN_PREFIXE)/$(DELIVERY_LIBS)
	install -m 755 $(DELIVERY_LIBS)/$(MAIN_LIBNAME).a $(MAIN_PREFIXE)/$(DELIVERY_LIBS)/
	install -m 755 $(DELIVERY_LIBS)/$(MAIN_LIBNAME).so $(MAIN_PREFIXE)/$(DELIVERY_LIBS)/
	@echo Installing BFCP samples to $(MAIN_PREFIXE)/$(DELIVERY_BINS)
	install -m 755 $(DELIVERY_BINS)/* $(MAIN_PREFIXE)/$(DELIVERY_BINS)/
	@echo Installing BFCP server headers to $(MAIN_PREFIXE)/$(DELIVERY_INCLUDES)
	install -m 755 $(DELIVERY_INCLUDES)/*.h $(MAIN_PREFIXE)/$(DELIVERY_INCLUDES)/
	@echo Installing BFCP documentation to $(MAIN_PREFIXE)/$(DELIVERY_DOCS)
	cp -r docs/* $(MAIN_PREFIXE)/$(DELIVERY_DOCS)/
 
uninstall: 
	@echo Uninstalling BFCP library from $(MAIN_PREFIXE)/$(DELIVERY_LIBS)
	rm -f $(MAIN_PREFIXE)/$(DELIVERY_LIBS)/$(MAIN_LIBNAME).a
	rm -f $(MAIN_PREFIXE)/$(DELIVERY_LIBS)/$(MAIN_LIBNAME).so
	@echo Uninstalling BFCP samples to $(MAIN_PREFIXE)/$(DELIVERY_BINS)
	rm -f $(MAIN_PREFIXE)/$(DELIVERY_BINS)/*
	@echo Uninstalling BFCP library headers from $(MAIN_PREFIXE)/$(DELIVERY_INCLUDES)/
	rm -f $(MAIN_PREFIXE)/$(DELIVERY_INCLUDES)/*
	@echo clean up $(MAIN_PREFIXE)
	rm -f $(MAIN_PREFIXE)/$(DELIVERY_LIBS)/*
	rm -f $(MAIN_PREFIXE)/$(DELIVERY_INCLUDES)/*
	rm -f $(MAIN_PREFIXE)/$(DELIVERY_OBJS)/*
	rm -f $(MAIN_PREFIXE)/$(DELIVERY_BINS)/*
	rm -f $(MAIN_PREFIXE)/$(DELIVERY_DOCS)/*
	rm -rf $(MAIN_PREFIXE)
	
so: modules
	g++ -shared -Wl,-soname,$(MAIN_LIBNAME).so -o $(DELIVERY_LIBS)/$(MAIN_LIBNAME).so $(DELIVERY_OBJS)/*.o $(MAIN_CPP_OPTS) $(MAIN_LIBS)

lib: modules 
	ar ruv $(DELIVERY_LIBS)/$(MAIN_LIBNAME).a $(DELIVERY_OBJS)/*.o 
	
