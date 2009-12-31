## test/simfqt sub-directory
include $(top_srcdir)/Makefile.common

MAINTAINERCLEANFILES = Makefile.in

##
SUBDIRS =

EXTRA_DIST =

##
check_PROGRAMS = priceQuote
TESTS = $(check_PROGRAMS)
XFAIL_TESTS = #

#InventoryTestSuite_SOURCES = InventoryTestSuite.hpp \
				InventoryTestSuite.cpp
#InventoryTestSuite_CXXFLAGS= $(CPPUNIT_CFLAGS) $(BOOST_CFLAGS)
#InventoryTestSuite_LDADD = $(top_builddir)/test/com/libcppunitcore.la
#InventoryTestSuite_LDFLAGS = \
#		$(BOOST_LIBS) $(CPPUNIT_LIBS) \
#		$(top_builddir)/simfqt/libsimfqt.la

priceQuote_SOURCES = priceQuote.cpp
priceQuote_CXXFLAGS= $(CPPUNIT_CFLAGS) $(BOOST_CFLAGS)
priceQuote_LDADD =
priceQuote_LDFLAGS = $(BOOST_LIBS) \
		$(top_builddir)/simfqt/core/libsimfqt.la
