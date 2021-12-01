# Project Information and Contact Details
GITHUB_ID := alanbixby
B_NUMBER := B00769751
COURSE := CS375
CP := 3
EXECUTABLE := group-project
WORKING_DIR := src
TAR_FORMAT := abixby1

# Flags
CXXFLAGS := -Wall -Wextra -std=c++17 -O3
DEBUG := -DNDEBUG
LDFLAGS :=
LDLIBS :=

# Tar Flags
TAR_IGNORES := --exclude-vcs --exclude-vcs-ignores --exclude=.vscode --exclude=spec

# Source Files
SRC_FILES = $(shell find $(WORKING_DIR)/ -type f -name '*.cpp')
OBJ_FILES := $(patsubst %.cpp,%.o,$(SRC_FILES))
DEP_FILES := $(patsubst %.cpp,%.d,$(SRC_FILES))

# Makefile Rules
$(EXECUTABLE): $(OBJ_FILES)
		$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)
# Update .gitignore to exclude executable name; ignore if .gitignore is absent
		-sed -i "1c $(EXECUTABLE)" .gitignore 2> /dev/null

-include $(DEP_FILES)

%.o: %.cpp
		$(CXX) $(CXXFLAGS) $(LDFLAGS) $(DEBUG) -MMD -MP -c $< -o $@ $(LDLIBS)

debug: 
	$(MAKE) DEBUG="" rebuild

new: clean run

run: $(EXECUTABLE)
		./$(EXECUTABLE)

all: $(EXECUTABLE)

rebuild: clean $(EXECUTABLE)

tar: clean
		cd .. \
		&& ln -sf $(notdir $(CURDIR)) $(TAR_FORMAT) \
		&& tar $(TAR_IGNORES) --dereference -cvzf $(TAR_FORMAT).tar.gz $(TAR_FORMAT) \
		&& mv $(TAR_FORMAT).tar.gz $(notdir $(CURDIR))/$(TAR_FORMAT).tar.gz \
		; rm $(TAR_FORMAT)

clean:
		find . -type f -name '*.o' -delete -o -name '*.d' -delete
		rm -f $(EXECUTABLE) *.tar.gz

.PHONY: $(EXECUTABLE) all debug run rebuild tar clean