#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>devkitPro)
endif

ifeq ($(strip $(DEVKITPPC)),)
$(error "Please set DEVKITPPC in your environment. export DEVKITPPC=<path to>devkitPPC)
endif

ifeq ($(PLATFORM),cube)
ifeq ($(LIBOGC),libogc)
include $(DEVKITPPC)/gamecube_rules

INSTALL_INC	:=	$(DESTDIR)$(DEVKITPRO)/portlibs/gamecube/include
INSTALL_LIB	:=	$(DESTDIR)$(DEVKITPRO)/portlibs/gamecube/lib
else
include $(DEVKITPRO)/libogc-mod/gamecube_rules

INSTALL_INC	:=	$(DESTDIR)$(DEVKITPRO)/libogc-mod/portlibs/gamecube/include
INSTALL_LIB	:=	$(DESTDIR)$(DEVKITPRO)/libogc-mod/portlibs/gamecube/lib
endif

MACHDEP		+=	-DHW_DOL
else
ifeq ($(LIBOGC),libogc)
include $(DEVKITPPC)/wii_rules

INSTALL_INC	:=	$(DESTDIR)$(DEVKITPRO)/portlibs/wii/include
INSTALL_LIB	:=	$(DESTDIR)$(DEVKITPRO)/portlibs/wii/lib
else
include $(DEVKITPRO)/libogc-mod/wii_rules

INSTALL_INC	:=	$(DESTDIR)$(DEVKITPRO)/libogc-mod/portlibs/wii/include
INSTALL_LIB	:=	$(DESTDIR)$(DEVKITPRO)/libogc-mod/portlibs/wii/lib
endif

MACHDEP		+=	-DHW_RVL
endif

NULLSTR :=
PWD     := $(subst $(NULLSTR) ,\ ,$(shell pwd))

INCLUDE	:= -I../lib/pngu-mod -I$(PWD) -I$(LIBOGC_INC) -I$(DEVKITPRO)/portlibs/ppc/include -I$(DEVKITPRO)/portlibs/ppc/include/freetype2
CFLAGS  := -O2 -Wall $(MACHDEP) $(INCLUDE)

LIB		:= grrlib-mod
CFILES	:= $(wildcard *.c)
OFILES	:= $(CFILES:.c=.o)
DEPENDS	:= $(OFILES:.o=.d)
ARC		:= lib$(LIB).a
HDR		:= $(LIB).h
INL		:= $(wildcard $(LIB)/*.h)

export DEPSDIR := $(CURDIR)

all : $(OFILES)
	$(AR) -r $(ARC) $(OFILES)

clean :
	rm -f $(OFILES) $(DEPENDS) $(ARC)

install :
	mkdir -p  $(INSTALL_LIB)  $(INSTALL_INC)  $(INSTALL_INC)/grrlib-mod
	cp -f $(ARC) $(INSTALL_LIB)/
	cp -f $(HDR) $(INSTALL_INC)/
	cp -f $(INL) $(INSTALL_INC)/grrlib-mod
