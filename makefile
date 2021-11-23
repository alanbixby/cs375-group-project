# Project Information and Contact Details
GITHUB_ID := alanbixby
B_NUMBER := B00769751
COURSE := CS375
CP := 3
EXECUTABLE := group-project
WORKING_DIR := $(notdir $(CURDIR))
TAR_FORMAT := abixby1

# Source Files
SRC_FILES := ${wildcard src/*.cpp}
OBJ_FILES := $(subst .cpp,.o,$(SRC_FILES))

# Flags
CC := g++
FLAGS := -Wall -Wextra -std=c++17 -g -O3
LDFLAGS := -lGL -lglut -lpng -lz -lm

# Tar Flags
TAR_IGNORES := --exclude-vcs --exclude-vcs-ignores --exclude=.vscode --exclude=spec

$(EXECUTABLE): $(SRC_FILES) $(OBJ_FILES)
		$(CC) $(FLAGS) $(subst .cpp,.o,$(SRC_FILES)) -o $@
# Update .gitignore to exclude executable name
# Ignore error if gitignore isnt made (usually tar submission has this excluded- hi TA debugging this error!)
		-sed -i "1c $(EXECUTABLE)" .gitignore 2> /dev/null

.cpp.o:
		$(CC) $(FLAGS) -c $< -o $@

run: $(EXECUTABLE)
		./$(EXECUTABLE)

new: rebuild
		./$(EXECUTABLE)

rebuild: clean $(EXECUTABLE)

memcheck: $(EXECUTABLE)
		valgrind ./$(EXECUTABLE)

tar: clean
		cd .. \
		&& ln -sf $(WORKING_DIR) $(TAR_FORMAT) \
		&& tar $(TAR_IGNORES) --dereference -cvzf $(TAR_FORMAT).tar.gz $(TAR_FORMAT) \
		&& mv $(TAR_FORMAT).tar.gz $(WORKING_DIR)/$(TAR_FORMAT).tar.gz \
		;  rm $(TAR_FORMAT)

clean:
		rm -f src/*.o $(EXECUTABLE) *.tar.gz

.PHONY: run new rebuild memcheck tar clean