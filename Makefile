iGREEN   := \033[0;32m
CYAN    := \033[0;36m
RED     := \033[0;31m
YELLOW  := \033[0;33m
BOLD    := \033[1m
RESET   := \033[0m

# Auto-discover all exercise directories that have a Makefile
EXERCISES := $(sort $(wildcard ex0*))

all:
	@success=0; fail=0; \
	for dir in $(EXERCISES); do \
		printf "$(CYAN)$(BOLD)▶ Building $$dir...$(RESET)\n"; \
		if $(MAKE) -C $$dir --no-print-directory; then \
			printf "$(GREEN)  ✔ $$dir compiled successfully$(RESET)\n"; \
			success=$$((success + 1)); \
		else \
			printf "$(RED)  ✘ $$dir FAILED to compile$(RESET)\n"; \
			fail=$$((fail + 1)); \
			exit 1; \
		fi; \
	done; \
	printf "$(BOLD)$(GREEN)\n  ✔ $$success exercise(s) built successfully.$(RESET)\n"

# Run all test.sh scripts found in exercise directories
test:
	@passed=0; failed=0; skipped=0; \
	for dir in $(EXERCISES); do \
		if [ -f "$$dir/test.sh" ]; then \
			printf "$(CYAN)$(BOLD)▶ Testing $$dir...$(RESET)\n"; \
			chmod +x $$dir/test.sh; \
			if $(MAKE) -C $$dir --no-print-directory && (cd $$dir && ./test.sh); then \
				printf "$(GREEN)  ✔ $$dir tests passed$(RESET)\n"; \
				passed=$$((passed + 1)); \
			else \
				printf "$(RED)  ✘ $$dir tests FAILED$(RESET)\n"; \
				failed=$$((failed + 1)); \
			fi; \
		else \
			printf "$(YELLOW)  ⚠ $$dir has no test.sh – skipped$(RESET)\n"; \
			skipped=$$((skipped + 1)); \
		fi; \
	done; \
	printf "$(BOLD)\n  Results: $(GREEN)$$passed passed$(RESET), $(RED)$$failed failed$(RESET), $(YELLOW)$$skipped skipped$(RESET)\n"; \
	[ "$$failed" -eq 0 ]

clean:
	@for dir in $(EXERCISES); do \
		printf "$(CYAN)  Cleaning $$dir...$(RESET)\n"; \
		$(MAKE) -C $$dir clean --no-print-directory || exit 1; \
	done

fclean:
	@for dir in $(EXERCISES); do \
		printf "$(CYAN)  Full clean $$dir...$(RESET)\n"; \
		$(MAKE) -C $$dir fclean --no-print-directory || exit 1; \
	done

re: fclean all

# Apply .clang-format to all .cpp/.hpp files in every exercise directory
format:
	@printf "$(CYAN)$(BOLD)▶ Formatting sources...$(RESET)\n"; \
	files=$$(find $(EXERCISES) -type f \( -name '*.cpp' -o -name '*.hpp' \)); \
	if [ -z "$$files" ]; then \
		printf "$(YELLOW)  ⚠ No .cpp/.hpp files found – nothing to format$(RESET)\n"; \
	else \
		echo "$$files" | xargs clang-format -i --style=file; \
		printf "$(GREEN)  ✔ All files formatted$(RESET)\n"; \
	fi

# List exercises found by the wildcard
list:
	@printf "$(BOLD)Exercises in this module:$(RESET)\n"; \
	for dir in $(EXERCISES); do \
		printf "  • $$dir\n"; \
	done

.PHONY: all test clean fclean re list format
