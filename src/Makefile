.PHONY: all install uninstall clean dvi dist tests gcov_report rebuild open_app tar_dependence

# =========================================== VAR ==================================================

CXX = g++
CXX_FLAGS = -Wall -Werror -Wextra -std=c++17 -lgtest -lgtest_main --coverage
OS = $(shell uname -s)
PROJECT_NAME = 3DViewer
APP = ../app
BUILD = ../build
REPORT = ../report
DOCUMENTATION = ../documentation
DIST = ../dist
ifeq ($(OS), Darwin)
	OPEN = open
else
	OPEN = xdg-open
endif

# ========================================= TARGETS ================================================

all: install open_app

tar_dependence:
	@tar xvzf GIFCreation.tar.gz

install: uninstall tar_dependence
	@echo "Building application..."
	@cmake -B $(BUILD)
	@cd $(BUILD) && make
	@echo "Application build."
	@echo "Moving application to folder '$(APP)'..."
	@mkdir -p $(APP)
	@mv $(BUILD)/$(PROJECT_NAME) ./$(APP)/$(PROJECT_NAME).app
	@echo "Done.\n"
	@echo "Deleting build folder..."
	@rm -rf $(BUILD)
	@echo "Done.\n"
	@-ln $(APP)/$(PROJECT_NAME).app ~/Desktop/
	@echo "Installation complete!"

open_app:
ifeq ($(OS), Darwin)
	@open $(APP)/$(PROJECT_NAME).app
else
	@./$(APP)/$(PROJECT_NAME).app
endif

uninstall:
	@echo "Uninstalling start..."
	@-rm -rf $(APP) ~/Desktop/$(PROJECT_NAME).app
	@echo "Uninstalling success"

tests: clean
	@echo "Tests start..."
	$(CXX) $(shell find Facade tests -name "*.cc") $(CXX_FLAGS) -o test
	@./test
	@-mv *.gc* Facade
	@echo "Tests done"

gcov_report: tests
	@echo "Make report..."
	@mkdir -p $(REPORT)
	@lcov -t ./test -o $(REPORT)/test.info --no-external -c -d Facade
	@genhtml -o $(REPORT)/report_html $(REPORT)/test.info
	@echo "Report is complete"
	@$(OPEN) $(REPORT)/report_html/index.html

dist: clean
	@mkdir -p $(DIST)
	@tar -cvzf $(DIST)/source_code.tar.gz .
	@echo "The archive was successfully created on the path '$(DIST)'"

dvi:
	@doxygen Doxyfile
	@cp -r images $(DOCUMENTATION)/html
	@$(OPEN) $(DOCUMENTATION)/html/index.html

clean:
	@echo "Cleaning..."
	@rm -rf $(REPORT) Facade/*.gc* test $(BUILD)* $(DIST) logs $(DOCUMENTATION) $(APP) *.gc* Facade/*.gc*
	@echo "Clean is done"

rebuild: clean all

# ========================================== STYLE =================================================

style:
	@clang-format -n -style=google $(shell find . \( -name "*.cc" -or -name "*.h"  -or -name "*.c" -or -name "*.cpp" \))
