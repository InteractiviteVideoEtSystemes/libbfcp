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
#  \brief   : bfcp api Makefile
# 
#  \version : $Revision: 2510 $
# 
#  \date    : $Date: 2015-10-30 23:44:03 +0100 (Fri, 30 Oct 2015) $
# 
#  \remarks :
# 
# ------------------------------------------------------------------------- 

#---------------------------------------------------------------------------
# File identification                                                       
#---------------------------------------------------------------------------
include ../Makeinclude
PREFIX=..

OBJS = BFCPconnection.o BFCP_fsm.o 
BUILDOBJS = $(addprefix $(PREFIX)/$(DELIVERY_OBJS)/,$(OBJS))
	
$(PREFIX)/$(DELIVERY_OBJS)/%.o: %.cpp
	$(CPP)  $(INCS_DIR) -c $< -o $@ -I $(PREFIX)/$(DELIVERY_INCLUDES)  $(CPP_OPTS) -fno-strict-aliasing

$(PREFIX)/$(DELIVERY_OBJS)/%.o: %.c
	$(CC)  $(INCS_DIR) -c $< -o $@  -I$(PREFIX)/$(DELIVERY_INCLUDES) $(CC_OPTS)

all: $(BUILDOBJS)


clean:
	rm -f $(BUILDOBJS)

install:
	@echo Installing BFCP api headers to $(PREFIX)/$(DELIVERY_INCLUDES)/:
	install -m 755 BFCPconnection.h $(PREFIX)/$(DELIVERY_INCLUDES)/
	install -m 755 BFCP_fsm.h $(PREFIX)/$(DELIVERY_INCLUDES)/
	install -m 755 BFCPexception.h $(PREFIX)/$(DELIVERY_INCLUDES)/
	install -m 755 bfcp_threads.h $(PREFIX)/$(DELIVERY_INCLUDES)/
 
uninstall:
	@echo Uninstalling BFCP api headers from $(PREFIX)/$(DELIVERY_INCLUDES)/:
	rm -f $(PREFIX)/$(DELIVERY_INCLUDES)/BFCPconnection.h
	rm -f  $(PREFIX)/$(DELIVERY_INCLUDES)/BFCP_fsm.h
	rm -f  $(PREFIX)/$(DELIVERY_INCLUDES)/BFCPexception.h
	rm -f  $(PREFIX)/$(DELIVERY_INCLUDES)/bfcp_threads.h
