CC            := clang
CCFLAGS       := -Wall -Wextra -pedantic -std=c17 -lm -g
ASSIGNMENT    := a1

.DEFAULT_GOAL := help
.PHONY: clean bin run test help


clean:                ## cleans up project folder
	@echo "[\033[36mINFO\033[0m] Cleaning up folder..."
	rm -f $(ASSIGNMENT)
	rm -f testreport.html
	rm -rf valgrind_logs

bin:                  ## compiles project to executable binary
	@echo "[\033[36mINFO\033[0m] Compiling binary..."
	$(CC) $(CCFLAGS) -o $(ASSIGNMENT) $(ASSIGNMENT).c
	chmod +x $(ASSIGNMENT)

all: clean bin        ## all of the above

run: all              ## runs the project
	@echo "[\033[36mINFO\033[0m] Executing binary..."
	./$(ASSIGNMENT)

test: all             ## runs public testcases on the project
	@echo "[\033[36mINFO\033[0m] Executing testrunner..."
	./testrunner -c test.toml

help:                 ## prints the help text
	@echo "Usage: make \033[36m<TARGET>\033[0m"
	@echo "Available targets:"
	@awk -F':.*?##' '/^[a-zA-Z_-]+:.*?##.*$$/{printf "  \033[36m%-10s\033[0m%s\n", $$1, $$2}' $(MAKEFILE_LIST)

