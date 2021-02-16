# this is for the default make command
# it will build the Project2 target
EXEC = Project2
HEADERS = card.h deck.h pokerhand.h SortedLinkedList.h rank.h
OBJECTS = card.o deck.o pokerhand.o SortedLinkedList.o rank.o Project2.o
# these are the object dependencies for testPA2
# the headers are shared between this and the main headers
testPA2_OBJECTS = card.o deck.o pokerhand.o SortedLinkedList.o rank.o testPA2.o
# default target
$(EXEC): $(OBJECTS)
	g++ $^ -o $@
# testPA2 target
testPA2:  $(testPA2_OBJECTS)
	g++ $^ -o $@
# build the .o files for the .cpp
%.0: %.cpp $(HEADERS)
	g++ -c $< -o $@	
# clean up!
clean:
	rm -f *.o testPA2 $(EXEC)