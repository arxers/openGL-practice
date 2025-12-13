ROOT := $(CURDIR)

NAME = openGLTutorial

SRCS_APP := src/main.cpp src/Shader.cpp src/VAO.cpp src/VBO.cpp src/EBO.cpp src/stb.cpp src/Texture.cpp
SRCS_C   := lib/glad/glad.c

OBJ	:= $(SRCS_APP:.cpp=.o)
DEP := $(SRCS_APP:.cpp=.d)

CXX = g++
CC  = gcc

CXXFLAGS = -Wall -Wextra -Werror -MMD -I$(ROOT)/lib/include -I$(ROOT)/lib/glfw/include -I$(ROOT)/lib/glad/include
CFLAGS   = -Wall -Wextra -Werror -I$(ROOT)/lib/include -I$(ROOT)/lib/glfw/include -I$(ROOT)/lib/glad/include

GLFW_DIR = lib/glfw
GLFW_INSTALL_DIR = lib

GLM_DIR = lib/glm

LIBS_DIR := lib
LIBGLAD := $(LIBS_DIR)/libglad.a

LDFLAGS = -L$(ROOT)/$(GLFW_INSTALL_DIR)/lib -L$(LIBS_DIR) -lglad -lglfw3 -lGL -lm -ldl -lpthread

RED		= \033[1;31m
GREEN	= \033[1;32m
RESET	= \033[0m

all: glfw-build glm-clone $(LIBGLAD) $(NAME)

$(LIBGLAD): $(SRCS_C)
	@mkdir -p $(LIBS_DIR)
	@echo "Compiling glad..."
	@$(CC) -I$(ROOT)/lib/include -c $< -o $(LIBS_DIR)/glad.o
	@ar rcs $@ $(LIBS_DIR)/glad.o
	@rm -f $(LIBS_DIR)/glad.o

$(NAME): $(OBJ)
	@echo "Compiler flags:		$(GREEN)$(CXXFLAGS)$(RESET)"
	@echo "\nCreated binary file:	$(GREEN)(+) $(NAME)$(RESET)"
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

glm-clone:
	@if [ ! -d $(ROOT)/lib/glm ]; then \
		git clone https://github.com/g-truc/glm.git $(ROOT)/lib/glm; \
		cp -r $(GLM_DIR)/glm $(ROOT)/lib/include; \
	fi

glfw-clone:
	@if [ ! -d $(GLFW_DIR) ]; then \
		git clone https://github.com/glfw/glfw.git $(GLFW_DIR); \
	fi

glfw-build: glfw-clone
	@if [ ! -f $(ROOT)/$(GLFW_INSTALL_DIR)/lib/libglfw3.a ]; then \
		echo "Building and installing GLFW..."; \
		cd $(GLFW_DIR) && mkdir -p build && cd build && \
		cmake .. -DGLFW_BUILD_WAYLAND=OFF -DCMAKE_INSTALL_PREFIX=$(ROOT)/$(GLFW_INSTALL_DIR) && \
		make && make install; \
		cp -r $(GLFW_DIR)/include/GLFW $(ROOT)/$(GLFW_INSTALL_DIR)/include/ 2>/dev/null || true; \
	fi

%.o: %.cpp
	@echo "Compiling C++: $@"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	@echo "Compiling C: $@"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Removing dependancies:	$(RED)(-) $(OBJ) $(DEP) $(LIBGLAD)$(RESET)"
	@rm -f $(OBJ) $(DEP) $(LIBGLAD)

clean-binary: clean
	@echo "Removing binary:	$(RED)(-) $(NAME)$(RESET)"
	@rm -f $(NAME)

fclean: clean-binary glfw-clean glm-clean

glfw-clean:
	@echo "Removing GLFW install and source:	$(RED)(-) $(GLFW_DIR)$(RESET)"
	@rm -rf $(GLFW_DIR)
	@rm -rf $(GLFW_INSTALL_DIR)/include/GLFW
	@rm -rf $(GLFW_INSTALL_DIR)/lib

glm-clean:
	@echo "Removing GLM files"
	@rm -rf $(GLM_DIR)
	@rm -rf $(ROOT)/lib/include/glm 

g: CXXFLAGS += -g
g: re

re: clean-binary all

-include $(DEP)

.PHONY: all clean clean-binary fclean glfw-clean g re