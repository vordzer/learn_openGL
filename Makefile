CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		hello_opengl.o

LIBS = -lGL -lglfw -lGLEW

TARGET =	hello_opengl

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
