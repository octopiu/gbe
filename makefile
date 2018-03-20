CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
CC_FLAGS += -MMD -std=c++11 -O3 -s -DNDEBUG
-include $(OBJFILES:.o=.d)
LDLIBS=-L/usr/lib/x86_64-linux-gnu/ -lsfml-graphics -lsfml-system -lsfml-window -ljsoncpp

INC=-Iinclude

gbemulator: $(OBJ_FILES)
	g++ $(CC_FLAGS) $(INC) -o $@ $^ main.cpp $(LDLIBS)

obj/%.o: src/%.cpp
	g++ $(INC) $(CC_FLAGS) -c -o $@ $<

clean:
	rm gbemulator
	rm gbemulator.d
	rm obj/*.o
	rm obj/*.d
