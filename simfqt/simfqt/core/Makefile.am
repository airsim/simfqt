# simfqt/core
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS =


# Library
lib_LTLIBRARIES = libsimfqt.la

libsimfqt_la_SOURCES = $(service_h_sources) $(service_cc_sources)
libsimfqt_la_LIBADD = \
	$(top_builddir)/simfqt/basic/libbas.la \
	$(top_builddir)/simfqt/bom/libbom.la \
	$(top_builddir)/simfqt/factory/libfac.la \
	$(top_builddir)/simfqt/command/libcmd.la \
	$(top_builddir)/simfqt/service/libsvc.la
libsimfqt_la_LDFLAGS = \
	$(BOOST_DATE_TIME_LIB) $(BOOST_PROGRAM_OPTIONS_LIB) \
	-version-info $(GENERIC_LIBRARY_VERSION)

# Header files
#pkginclude_HEADERS = $(service_h_sources)
#nobase_nodist_pkginclude_HEADERS = $(top_builddir)/simfqt/config.h

