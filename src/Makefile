.PHONY: all install uninstall clean dvi dist test gcov_report generate_make rebuild open_app

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
QT_MAKEFILE = MakeBuild

# =========================================== OS ===================================================


# ========================================= TARGETS ================================================

all: install

generate_make:
	@qmake $(QT_PRO) -o $(BUILD)/$(QT_MAKEFILE)

install: uninstall generate_make
	@echo "Building application..."
	@cd $(BUILD) && make -sf $(QT_MAKEFILE)
	@echo "Application build."
	@echo "Moving application to folder \"$(APP)\"..."
	@mkdir $(APP)
ifeq ($(OS), Darwin)
	@mv $(BUILD)/$(PROJECT_NAME).app ./$(APP)
else
	@mv $(BUILD)/$(PROJECT_NAME) ./$(APP)/$(PROJECT_NAME).app
endif
	@echo "Done.\n"
	@echo "Deleting build folder..."
	@rm -rf $(BUILD)
	@echo "Done.\n"
	@echo "Installation complete!"
	@make open_app

open_app:
ifeq ($(OS), Darwin)
	@open $(APP)/$(PROJECT_NAME).app
else
	@./$(APP)/$(PROJECT_NAME).app
endif

uninstall:
	@echo "Uninstalling start..."
	@-rm -rf $(APP)
	@echo "Uninstalling success"

dist: clean
	@mkdir -p $(DIST)
	@tar -cvzf $(DIST)/source_code.tar.gz .
	@echo "The archive was successfully created on the path '../dist'"

dvi:
	@doxygen Doxyfile
ifeq ($(OS), Darwin)
	@open ../documentation/html/index.html
else
	@xdg-open ../documentation/html/index.html
endif	

clean:
	@echo "Cleaning..."
	@rm -rf $(REPORT) Facade/*.gc* test $(BUILD)* $(DIST) logs $(DOCUMENTATION) $(APP)
	@echo "Clean is done"

rebuild: clean all

# ========================================== STYLE =================================================

style:
	@clang-format -n -style=google $(shell find . \( -name "*.cc" -or -name "*.h" \))
