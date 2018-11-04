CPP := g++
CPPFLAGS := -g -std=c++11 -Wl,-subsystem,windows

INCLUDE := -IC:\mingw_dev_lib\include\SDL2
LIBS := -LC:\mingw_dev_lib\lib
#-mwindows suppresses the console; remove for testing
LINKFLAGS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows
OBJS := main.o component.o entity.o resource_manager.o graphics_system.o movement_system.o graphics_components.o location_components.o physics_components.o
OBJDIR := objects
SOURCEDIR := source
TARGET := Demo

$(TARGET): $(OBJS)
	$(CPP) $^ -o $@ $(INCLUDE) $(LIBS) $(LINKFLAGS)

%.o: $(SOURCEDIR)/%.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
	
clean:
	rm -rf $(TARGET) *.o