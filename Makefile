NAME = openGLTutorial
SRC = src/main.cpp src/glad.c src/Shader.cpp src/VAO.cpp src/VBO.cpp src/EBO.cpp

OBJ = $(patsubst %.cpp,%.o, $(patsubst %.c,%.o,$(SRC)))
DEP = $(patsubst %.cpp,%.d, $(patsubst %.c,%.d,$(SRC)))

CXX = @c++
CC 	= gcc
CXXFLAGS = -Wall -Wextra -Werror -MMD -Ilib/glfw/include -Iinc -Ilib/glfw/include
LDFLAGS = -Llib/glfw/build/src -lglfw3 -lGL -lm -ldl -lpthread

RED		= \033[1;31m
GREEN	= \033[1;32m
RESET	= \033[0m

GLFW_DIR = lib/glfw
GLFW_BUILD = $(GLFW_DIR)/build/src/libglfw3.a

all: glfw $(NAME)

$(NAME): $(OBJ)
	@echo "Compiler flags:		$(GREEN)$(CXXFLAGS)$(RESET)"
	@echo "\nCreated binary file:	$(GREEN)(+) $(NAME)$(RESET)"
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

glfw:
	@if [ ! -d $(GLFW_DIR) ]; then \
		git clone https://github.com/glfw/glfw.git $(GLFW_DIR); \
	fi
	@if [ ! -f $(GLFW_BUILD) ]; then \
		echo "Building GLFW..."; \
		cd $(GLFW_DIR) && mkdir -p build && cd build && cmake .. -DGLFW_BUILD_WAYLAND=OFF && make; \
	fi

%.o: %.c
	@echo "Compiling .o file:	$(GREEN)(+) $@$(RESET)"
	@$(CC) $(CXXFLAGS) -c $< -o $@

%.o: %.cpp
	@echo "Compiling .o file:	$(GREEN)(+) $@$(RESET)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Removing dependancies:	$(RED)(-) $(OBJ) $(DEP)$(RESET)"
	@rm -f $(OBJ) $(DEP)

clean_binary: clean
	@echo "Removing binary file:	$(RED)(-) $(NAME)$(RESET)"
	@rm -f $(NAME)

fclean: clean_binary clean_glfw

clean_glfw:
	@echo "Removing GLFW folder:	$(RED)(-) $(GLFW_DIR)$(RESET)"
	@rm -rf $(GLFW_DIR)

g: CXXFLAGS += -g
g: re

re: clean_binary all

-include $(DEP)

.PHONY: all clean clean_binary fclean clean_glfw g re
