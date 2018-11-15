CC			= g++
CCLINK		= g++
LIBS		=
CCOPTIONS	= -Wall -pedantic -g
LDOPTIONS	=
HDRS		= process_list.h test_process_list.h

TEST = process_list

TESTOBJECT = process_list_test_driver.o
OBJS = process_list.o test_process_list.o shortcut.o

DOXY		= /Applications/Doxygen/Doxygen.app/Contents/Resources/doxygen

all: $(PROGRAM)
	./$(PROGRAM)

$(TEST): $(OBJS) $(TESTOBJECT)
	$(CCLINK) -o $@ $(LDOPTIONS) $(OBJS) $(TESTOBJECT)

$(PROGRAM): $(OBJS) $(MAINOBJECT)
	$(CCLINK) -o $@ $(LDOPTIONS) $(OBJS) $(MAINOBJECT)

.PHONY: clean cleanall doxy test

clean:
	rm -f $(PROGRAM) $(TEST) $(TESTOBJECT) $(MAINOBJECT) $(OBJS)

cleanall:
	rm -f $(PROGRAM) $(TEST) $(OBJS) $(TESTOBJECT) $(MAINOBJECT) index.html
	rm -R html

doxy:
	$(DOXY)
	ln -s html/index.html index.html

test: $(TEST)
	./$(TEST)

#sets project as sample solution
setsample:
	cp process_list.cpp.sample process_list.cpp
	cp process_list.h.sample process_list.h

#sets project as assignment
setassignment:
	cp process_list.cpp.assignment process_list.cpp
	cp process_list.h.assignment process_list.h

# defines current state of project as sample solution
definesample:
	cp process_list.cpp process_list.cpp.sample
	cp process_list.h process_list.h.sample

# defines current sate of project as assignment
defineassignment:
	cp process_list.cpp process_list.cpp.assignment
	cp process_list.h process_list.h.assignment

# creates a folder which can serve as a publishable assignment
assignmentfolder:
	make setsample
	make doxy
	make setassignment
	mkdir ../assignment
	cp -R * ../assignment
	rm ../assignment/*.sample
	rm ../assignment/*.assignment
	make cleanall

%.o: %.cpp $(HDRS)
	$(CC) $(CCOPTIONS) -c $<
