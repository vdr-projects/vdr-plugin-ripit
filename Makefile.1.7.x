#
# Makefile for a Video Disk Recorder plugin
#
# $Id$

# The official name of this plugin.
# This name will be used in the '-P...' option of VDR to load the plugin.
# By default the main source file also carries this name.

PLUGIN = ripit

### The version number of this plugin (taken from the main source file):

VERSION = $(shell grep 'static const char \*VERSION *=' $(PLUGIN).h | awk '{ print $$6 }' | sed -e 's/[";]//g')

### The directory environment:

# Use package data if installed...otherwise assume we're under the VDR source directory:
PKGCFG   = $(if $(VDRDIR),$(shell pkg-config --variable=$(1) $(VDRDIR)/vdr.pc),$(shell pkg-config --variable=$(1) vdr || pkg-config --variable=$(1) ../../../vdr.pc))
LIBDIR   = $(DESTDIR)$(call PKGCFG,libdir)
LOCDIR   = $(DESTDIR)$(call PKGCFG,locdir)
PLGCFG   = $(call PKGCFG,plgcfg)
BINDIR   = $(DESTDIR)$(call PKGCFG,bindir)
VIDEODIR = $(DESTDIR)$(call PKGCFG,videodir)
#
TMPDIR ?= /tmp

### Allow global user defined options to overwrite defaults:

-include \$(PLGCFG)

### Allow user defined options to overwrite defaults:

-include Make.config

### Default values:

PLUGIN_RIPIT_LOG_FILE?=/tmp/ripit.log
PLUGIN_RIPIT_LOCK_FILE?=/tmp/ripit.process
PLUGIN_RIPIT_ABORT_FILE?=/tmp/ripit.stop
PLUGIN_RIPIT_DEFAULT_TARGET_DIRECTORY?=$(VIDEODIR)/$(PLUGIN)

### The compiler options:

export CFLAGS   = $(call PKGCFG,cflags)
export CXXFLAGS = $(call PKGCFG,cxxflags)

### The version number of VDR's plugin API:

APIVERSION = $(call PKGCFG,apiversion)

### The name of the distribution archive:

ARCHIVE = $(PLUGIN)-$(VERSION)
PACKAGE = vdr-$(ARCHIVE)

### The name of the shared object file:

SOFILE = libvdr-$(PLUGIN).so

### Includes and Defines (add further entries here):

INCLUDES += -DLOG_FILE='"$(PLUGIN_RIPIT_LOG_FILE)"' -DLOCK_FILE='"$(PLUGIN_RIPIT_LOCK_FILE)"' -DABORT_FILE='"$(PLUGIN_RIPIT_ABORT_FILE)"' -DDEFAULT_RIPIT_DIR='"$(PLUGIN_RIPIT_DEFAULT_TARGET_DIRECTORY)"'

DEFINES += -DPLUGIN_NAME_I18N='"$(PLUGIN)"'

### The object files (add further files here):

OBJS = $(PLUGIN).o ripitosd.o setup.o

### The main target:

all: $(SOFILE) i18n

### Implicit rules:

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $(DEFINES) $(INCLUDES) $<

### Dependencies:

MAKEDEP = $(CXX) -MM -MG
DEPFILE = .dependencies
$(DEPFILE): Makefile
	@$(MAKEDEP) $(DEFINES) $(INCLUDES) $(OBJS:%.o=%.c) > $@

-include $(DEPFILE)

### Internationalization (I18N):

PODIR     = po
I18Npo    = $(wildcard $(PODIR)/*.po)
I18Nmo    = $(addsuffix .mo, $(foreach file, $(I18Npo), $(basename $(file))))
I18Nmsgs  = $(addprefix $(LOCDIR)/, $(addsuffix /LC_MESSAGES/vdr-$(PLUGIN).mo, $(notdir $(foreach file, $(I18Npo), $(basename $(file))))))
I18Npot   = $(PODIR)/$(PLUGIN).pot

%.mo: %.po
	msgfmt -c -o $@ $<

$(I18Npot): $(wildcard *.c *.h)
	xgettext -C -cTRANSLATORS --no-wrap --no-location -k -ktr -ktrNOOP --package-name=vdr-$(PLUGIN) --package-version=$(VERSION) --msgid-bugs-address='<see README>' -o $@ $^

%.po: $(I18Npot)
	msgmerge -U --no-wrap --no-location --backup=none -q -N $@ $<
	@touch $@

$(I18Nmsgs): $(LOCDIR)/%/LC_MESSAGES/vdr-$(PLUGIN).mo: $(PODIR)/%.mo
	install -D -m644 $< $@

.PHONY: i18n
i18n: $(I18Nmo) $(I18Npot)

install-i18n: $(I18Nmsgs)

### Targets:

$(SOFILE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -shared $(OBJS) -o $@

install-lib: $(SOFILE)
	install -D $^ $(LIBDIR)/$^.$(APIVERSION)

install-bin:
	install -D commands/vdr-ripit $(BINDIR)/vdr-ripit
	if [ ! -e $(BINDIR)/vdr-eject ]; then install -D commands/vdr-eject $(BINDIR)/vdr-eject; fi

install-bin-mo:
	mkdir -p $(LOCDIR)/de/LC_MESSAGES/
	msgfmt -o $(LOCDIR)/de/LC_MESSAGES/vdr-ripit.mo commands/po/vdr-ripit.de.po
	mkdir -p $(LOCDIR)/it/LC_MESSAGES/
	msgfmt -o $(LOCDIR)/it/LC_MESSAGES/vdr-ripit.mo commands/po/vdr-ripit.it.po
	mkdir -p $(LOCDIR)/fr/LC_MESSAGES/
	msgfmt -o $(LOCDIR)/fr/LC_MESSAGES/vdr-ripit.mo commands/po/vdr-ripit.fr.po

install-datadir:
	mkdir -p $(DEFAULT_TARGET_DIRECTORY)
	chmod ugo+rwx $(DEFAULT_TARGET_DIRECTORY)
	touch $(DEFAULT_TARGET_DIRECTORY)/.$(PLUGIN)

install: install-lib install-i18n install-bin install-bin-mo install-datadir

dist: $(I18Npo) clean
	@-rm -rf $(TMPDIR)/$(ARCHIVE)
	@mkdir $(TMPDIR)/$(ARCHIVE)
	@cp -a * $(TMPDIR)/$(ARCHIVE)
	@tar czf $(PACKAGE).tgz -C $(TMPDIR) $(ARCHIVE)
	@-rm -rf $(TMPDIR)/$(ARCHIVE)
	@echo Distribution package created as $(PACKAGE).tgz

clean:
	@-rm -f $(PODIR)/*.mo $(PODIR)/*.pot
	@-rm -f $(OBJS) $(DEPFILE) *.so *.tgz core* *~

reformat:
	@uncrustify -c source-format.cfg --replace --no-backup $$(find . -name "*.[ch]")
