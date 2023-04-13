#
CXXFLAGS+=-IHeader -std=c++17 -Wall -Werror
CXXSOURCE=$(wildcard Source/*.cc)
CXXOBJS=$(patsubst %.cc,%.o,$(CXXSOURCE))

SearchNewBooks: $(CXXOBJS)
	    $(CXX) $(LDFLAGS) -o $@ $^

run :
	@echo "Running the program:"
	@./SearchNewBooks newbooks.dat request.dat result.dat

edit:
	@vim Source/SearchNewBooks.cc

debug:
	@gdb ./SearchNewBooks

clean :
	@rm -f SearchNewBooks
	@rm -f request.dat
	@rm -f newbooks.dat
	@rm -f result.dat
	@rm -f Source/*.o
