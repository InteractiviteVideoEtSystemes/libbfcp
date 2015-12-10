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
#  \brief   : bfcp message codec Makefile
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


PREFIX=../..
include ../../Makeinclude
OBJS = bfcp_messages.o bfcp_messages_build.o bfcp_messages_parse.o bfcp_strings.o
BUILDOBJS = $(addprefix $(PREFIX)/$(DELIVERY_OBJS)/,$(OBJS))

all: $(BUILDOBJS) install

clean:
	rm -f $(BUILDOBJS)

$(PREFIX)/$(DELIVERY_OBJS)/%.o: %.cpp
	$(CPP)  $(INCS_DIR) -c $< -o $(PREFIX)/$(DELIVERY_OBJS)/$@ $(CPP_OPTS)
	
$(PREFIX)/$(DELIVERY_OBJS)/%.o: %.c
	$(CC)  $(INCS_DIR) -c $< -o $(PREFIX)/$(DELIVERY_OBJS)/$@ $(CC_OPTS)

install:
	@echo Installing BFCP messages headers to $(PREFIX)/$(DELIVERY_INCLUDES)/:
	install -m 755 bfcp_messages.h $(PREFIX)/$(DELIVERY_INCLUDES)/
	install -m 755 bfcp_strings.h $(PREFIX)/$(DELIVERY_INCLUDES)/
 
uninstall:
	@echo Uninstalling BFCP messages headers from $(PREFIX)/$(DELIVERY_INCLUDES)/:
	rm -f $(PREFIX)/$(DELIVERY_INCLUDES)/bfcp_messages.h
	rm -f $(PREFIX)/$(DELIVERY_INCLUDES)/bfcp_strings.h
