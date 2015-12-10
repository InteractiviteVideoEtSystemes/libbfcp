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
#  \brief   : bfcp server Makefile
# 
#  \version : $Revision: 2507 $
# 
#  \date    : $Date: 2015-10-30 19:43:17 +0100 (Fri, 30 Oct 2015) $
# 
#  \remarks :
# 
# ------------------------------------------------------------------------- 

#---------------------------------------------------------------------------
# File identification                                                       
#---------------------------------------------------------------------------


include ../../../Makeinclude
PREFIX=../../..

OBJS = bfcp_floor_list.o bfcp_link_list.o bfcp_server.o bfcp_user_list.o
BUILDOBJS = $(addprefix $(PREFIX)/$(DELIVERY_OBJS)/,$(OBJS))

$(PREFIX)/$(DELIVERY_OBJS)/%.o: %.cpp
	$(CPP)  $(INCS_DIR) -c $< -o $@ -I $(PREFIX)/$(DELIVERY_INCLUDES)  $(CPP_OPTS)
	
$(PREFIX)/$(DELIVERY_OBJS)/%.o: %.c
	$(CC)  $(INCS_DIR) -c $< -o $@  -I$(PREFIX)/$(DELIVERY_INCLUDES) $(CC_OPTS)

all: $(BUILDOBJS) install

install:
	@echo Installing BFCP server headers to $(PREFIX)/$(DELIVERY_INCLUDES)/:
	install -m 755 bfcp_floor_list.h $(PREFIX)/$(DELIVERY_INCLUDES)/
	install -m 755 bfcp_link_list.h $(PREFIX)/$(DELIVERY_INCLUDES)/
	install -m 755 bfcp_server.h $(PREFIX)/$(DELIVERY_INCLUDES)/
	install -m 755 bfcp_user_list.h $(PREFIX)/$(DELIVERY_INCLUDES)/
 
uninstall:
	@echo Uninstalling BFCP server headers from $(PREFIX)/$(DELIVERY_INCLUDES)/:
	rm -f $(PREFIX)/$(DELIVERY_INCLUDES)/bfcp_floor_list.h
	rm -f $(PREFIX)/$(DELIVERY_INCLUDES)/bfcp_link_list.h
	rm -f $(PREFIX)/$(DELIVERY_INCLUDES)/bfcp_server.h
	rm -f $(PREFIX)/$(DELIVERY_INCLUDES)/bfcp_user_list.h

clean:
	rm -f $(BUILDOBJS)
