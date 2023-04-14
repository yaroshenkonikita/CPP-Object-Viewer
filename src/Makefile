.PHONY: all install uninstall clean dvi dist test gcov_report generate_make
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
	@echo "Done."
	@echo "Deleting build folder..."
	@rm -rf $(BUILD)
	@echo "Done."
	@echo "Installation complete!"
	@make open_app

open_app:
	@open $(APP)/$(PROJECT_NAME).app


uninstall:
	@echo "Uninstalling start..."
	@-rm -rf $(APP)
	@echo "Uninstalling success"

dist: clean
	@mkdir -p $(DIST)
	tar -cvzf $(DIST)/source_code.tar.gz .


dvi:
	doxygen Doxyfile

clean:
	@echo "Cleaning..."
	@rm -rf $(REPORT) Facade/*.gc* test $(BUILD)* $(DIST) logs $(DOCUMENTATION) $(APP)
	@echo "Clean is done"

rebuild: clean all

# ========================================== STYLE =================================================

style:
	@clang-format -n -style=google $(shell find . \( -name "*.cc" -or -name "*.h" \))
