PROJ_NAME = game-test

CPP = g++
OBJ_DIR = obj

SRCS = $(wildcard src/*.cpp)
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))
DIRS = $(sort $(dir $(OBJS)))
DEPENDENCIES = $(OBJS:.o=.d)
INCLUDES = -Iinc/
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
CPPFLAGS = $(INCLUDES) -g
LDFLAGS = -g $(LIBS) -pthread -o $(PROJ_NAME)

all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJS)
	@$(CPP) $(OBJS) $(LDFLAGS)

ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEPENDENCIES)
endif

define make-depend
    $(CPP) -M \
	-MF $3 \
	-MP \
	-MT $2 \
	$(CPPFLAGS) \
	$1
endef

$(OBJ_DIR)/%.o: %.cpp
	@echo $<
	@$(call make-depend,$<,$@,$(subst .o,.d,$@))
	@$(CPP) $(CPPFLAGS) -c -o $@ $<

$(OBJS): | $(DIRS)

$(DIRS):
	@mkdir -p $@

clean:
	rm -f $(OBJS)
	rm -f $(DEPENDENCIES)
	rm -f $(PROJ_NAME)
	rm -rf $(OBJ_DIR)
