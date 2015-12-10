
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
#  \brief   : bfcp participant test
# 
#  \version : $Revision: 2519 $
# 
#  \date    : $Date: 2015-11-01 19:01:17 +0100 (Sun, 01 Nov 2015) $
# 
#  \remarks :
# 
# ------------------------------------------------------------------------- 

#---------------------------------------------------------------------------
# File identification                                                       
#---------------------------------------------------------------------------

include ../../Makeinclude
EXENAME_CLI = bfcpParticipant
OBJS_CLI = client.o
PREFIX=../..

EXENAME_SRV = bfcpServer
OBJS_SRV = server.o

all: $(EXENAME_CLI) $(EXENAME_SRV)

$(EXENAME_CLI): $(OBJS_CLI)
	$(CPP)   -o $(EXENAME_CLI) $(OBJS_CLI)  ../../$(SAMPLES_LIBS) $(LIBS) $(CPP_OPTS) 

$(EXENAME_SRV): $(OBJS_SRV)
	$(CPP)   -o $(EXENAME_SRV) $(OBJS_SRV)  ../../$(SAMPLES_LIBS) $(LIBS)  $(CPP_OPTS) 

%.o: %.cpp
	$(CPP)  $(SAMPLES_INCS_DIR) -c $< -o $@ $(CPP_OPTS) -I../../include

clean :
	rm -f $(OBJS_CLI) $(OBJS_SRV) *.obj $(EXENAME_CLI) $(EXENAME_SRV)

install:
	@echo Installing BFCP participant test to $(PREFIX)/$(DELIVERY_BINS)/:
	install -m 755 $(EXENAME_CLI) $(PREFIX)/$(DELIVERY_BINS)/
	@echo Installing BFCP server test to $(PREFIX)/$(DELIVERY_BINS)/:
	install -m 755 $(EXENAME_SRV) $(PREFIX)/$(DELIVERY_BINS)/
 
uninstall:
	@echo Uninstalling BFCP participant test from $(PREFIX)/$(DELIVERY_BINS)/:
	rm -f $(PREFIX)/$(DELIVERY_BINS)/$(EXENAME_CLI)
	@echo Uninstalling BFCP server test from $(PREFIX)/$(DELIVERY_BINS)/:
	rm -f $(PREFIX)/$(DELIVERY_BINS)/$(EXENAME_SRV)
