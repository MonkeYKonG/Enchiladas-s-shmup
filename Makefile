CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		Enchiladas-s-schmup.o

LIBS =

TARGET =	Enchiladas-s-schmup

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
