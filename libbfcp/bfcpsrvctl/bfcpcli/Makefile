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
#  \brief   : bfcp participant Makefile
# 
#  \version : $Revision: 2511 $
# 
#  \date    : $Date: 2015-10-31 00:09:47 +0100 (Sat, 31 Oct 2015) $
# 
#  \remarks :
# 
# ------------------------------------------------------------------------- 

#---------------------------------------------------------------------------
# File identification                                                       
#---------------------------------------------------------------------------


include ../../../Makeinclude
PREFIX=../../..

OBJS = bfcp_participant.o
BUILDOBJS = $(addprefix $(PREFIX)/$(DELIVERY_OBJS)/,$(OBJS))

$(PREFIX)/$(DELIVERY_OBJS)/%.o: %.cpp
	$(CPP)  $(INCS_DIR) -c $< -o $@ -I $(PREFIX)/$(DELIVERY_INCLUDES) $(CPP_OPTS)
	
$(PREFIX)/$(DELIVERY_OBJS)/%.o: %.c
	$(CC)  $(INCS_DIR) -c $< -o $@ -I $(PREFIX)/$(DELIVERY_INCLUDES) $(CC_OPTS)


all: $(BUILDOBJS) install

clean:
	rm -f $(BUILDOBJS)
install:
	@echo Installing BFCP participant headers to $(PREFIX)/$(DELIVERY_INCLUDES) :
	install -m 755 bfcp_participant.h $(PREFIX)/$(DELIVERY_INCLUDES)/
 
uninstall:
	@echo Uninstalling BFCP messages headers from $(PREFIX)/$(DELIVERY_INCLUDES) :
	rm -f $(PREFIX)/$(DELIVERY_INCLUDES)/bfcp_participant.h


