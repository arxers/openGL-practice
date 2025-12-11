NAME = openGLTutorial
SRC = src/main.cpp src/glad.c src/Shader.cpp src/VAO.cpp src/VBO.cpp src/EBO.cpp

OBJ = $(patsubst %.cpp,%.o, $(patsubst %.c,%.o,$(SRC)))
DEP = $(patsubst %.cpp,%.d, $(patsubst %.c,%.d,$(SRC)))

CXX = g++
CC 	= gcc
CXXFLAGS = -Wall -Wextra -Werror -MMD -Ilib/include -Ilib/glfw/include
LDFLAGS = -Llib/lib -lglfw3 -lGL -lm -ldl -lpthread

RED		= \033[1;31m
GREEN	= \033[1;32m
RESET	= \033[0m

GLFW_DIR = lib/glfw
GLFW_INSTALL_DIR = lib

all: glfw-build $(NAME)

$(NAME): $(OBJ)
	@echo "Compiler flags:		$(GREEN)$(CXXFLAGS)$(RESET)"
	@echo "\nCreated binary file:	$(GREEN)(+) $(NAME)$(RESET)"
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

glfw-clone:
	@if [ ! -d $(GLFW_DIR) ]; then \
		git clone https://github.com/glfw/glfw.git $(GLFW_DIR); \
	fi

glfw-build: glfw-clone
	@if [ ! -f $(abspath $(GLFW_INSTALL_DIR))/lib/libglfw3.a ]; then \
        echo "Building and installing GLFW..."; \
        cd $(GLFW_DIR) && mkdir -p build && cd build && \
        cmake .. -DGLFW_BUILD_WAYLAND=OFF -DCMAKE_INSTALL_PREFIX=$(abspath $(GLFW_INSTALL_DIR)) && \
        make && make install; \
    fi
	cp -r $(GLFW_DIR)/include/GLFW $(abspath $(GLFW_INSTALL_DIR))/include/ 2>/dev/null || true

%.o: %.c
	@echo "Compiling .o file:	$(GREEN)(+) $@$(RESET)"
	@$(CC) $(CXXFLAGS) -c $< -o $@

%.o: %.cpp
	@echo "Compiling .o file:	$(GREEN)(+) $@$(RESET)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Removing dependancies:	$(RED)(-) $(OBJ) $(DEP)$(RESET)"
	@rm -f $(OBJ) $(DEP)

clean-binary: clean
	@echo "Removing binary file:	$(RED)(-) $(NAME)$(RESET)"
	@rm -f $(NAME)

fclean: clean-binary clean-glfw

clean-glfw:
	@echo "Removing GLFW install and source:	$(RED)(-) $(GLFW_DIR)$(RESET)"
	@rm -rf $(GLFW_DIR)
	@rm -rf $(GLFW_INSTALL_DIR)/include/GLFW
	@rm -rf $(GLFW_INSTALL_DIR)/lib

g: CXXFLAGS += -g
g: re

re: clean-binary all

-include $(DEP)

.PHONY: all clean clean-binary fclean clean-glfw g re
