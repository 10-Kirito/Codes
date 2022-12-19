# CSCI 2021 Project 3 Makefile
AN = p3
CLASS = 2021

# url and files for sanity checks
URL = https://www-users.cse.umn.edu/~kauffman/2021
CHECK_FILES = batt.h batt_sim.c batt_main.c test_batt_update.c test_batt_update.org test_hybrid.org testy

# -Wno-comment: disable warnings for multi-line comments, present in some tests
CFLAGS = -Wall -Wno-comment -Werror -g 
CC     = gcc $(CFLAGS)
SHELL  = /bin/bash
CWD    = $(shell pwd | sed 's/.*\///g')

PROGRAMS = \
	batt_main \

TESTPROGRAMS = \
	hybrid_main \
	test_batt_update \
	test_hybrid_batt_update


all : $(PROGRAMS)

clean :
	rm -f $(PROGRAMS) *.o $(TESTPROGRAMS)
	rm -rf sanity

help :
	@echo 'Typical usage is:'
	@echo '  > make                          # build all programs'
	@echo '  > make clean                    # remove all compiled items'
	@echo '  > make zip                      # create a zip file for submission'
	@echo '  > make prob1                    # built targets associated with problem 1'
	@echo '  > make prob1 testnum=5          # run problem 1 test #5 only'
	@echo '  > make test                     # run all tests'
	@echo '  > make sanity-check             # check that provided files are up to date / unmodified'
	@echo '  > make sanity-restore           # restore provided files to current norms'
	@echo 'SPECIAL TARGETS for this Project'      
	@echo '  > make hybrid_main              # build the combined C/assembly program'
	@echo '  > make test-hybrid              # run tests on the hybrid executable'

################################################################################
# 'make zip' to create p2-code.zip for submission
zip : clean clean-tests
	rm -f $(AN)-code.zip
	cd .. && zip "$(CWD)/$(AN)-code.zip" -r "$(CWD)"
	@echo Zip created in $(AN)-code.zip
	@if (( $$(stat -c '%s' $(AN)-code.zip) > 10*(2**20) )); then echo "WARNING: $(AN)-code.zip seems REALLY big, check there are no abnormally large test files"; du -h $(AN)-code.zip; fi
	@if (( $$(unzip -t $(AN)-code.zip | wc -l) > 256 )); then echo "WARNING: $(AN)-code.zip has 256 or more files in it which may cause submission problems"; fi


################################################################################
# sanity targets
sanity-dir :
	@rm -rf sanity
	@mkdir -p sanity
	@cd sanity && wget -q $(URL)/$(AN)-code.zip && unzip -qq $(AN)-code.zip && mv $(AN)-code/* .

sanity-check : sanity-dir
	@cd sanity; n=0; \
	  for f in $(CHECK_FILES); do diff -q $$f ../$$f; ((n += $$?)); done;  \
	  if ((n>0)); then echo 'ERROR: Stock Files Changed, Run `make sanity-restore` to fix this'; else echo 'Stock Files Sane'; fi

sanity-restore : sanity-dir
	@mkdir -p sanity-backups
	@cd sanity && n=0 && \
	  for f in $(CHECK_FILES); do cp --backup=numbered ../$$f ../sanity-backups; mv $$f ..; done && \
	  echo 'Restored original files, backed up copies in directory sanity-backups'

################################################################################
# battery problem

# build .o files from corresponding .c files
%.o : %.c batt.h
	$(CC) -c $<

# build assembly object via gcc + debug flags
batt_update_asm.o : batt_update_asm.s batt.h
	$(CC) -c $< 

batt_main : batt_main.o batt_sim.o batt_update_asm.o 
	$(CC) -o $@ $^

# batt_update functions testing program
test_batt_update : test_batt_update.o batt_sim.o batt_update_asm.o
	$(CC) -o -g $@ $^

# uses both assmebly and C update functions for incremental testing
hybrid_main : batt_main.o batt_sim.o batt_update_asm.o batt_update.o
	$(CC) -g -o $@ $^

# hybrid test program
test_hybrid_batt_update : test_batt_update.o batt_sim.o batt_update_asm.o batt_update.o
	$(CC) -o $@ $^

################################################################################
# Testing Targets
test-setup :
	@chmod u+rx testy bomb_download.sh

test: test-prob1 

test-prob1: batt_main test_batt_update test-setup
	./testy test_batt_update.org $(testnum)

test-hybrid: hybrid_main test_hybrid_batt_update test-setup
	./testy test_hybrid.org $(testnum)
	@echo
	@echo "WARNING: These are the hybrid tests used for incremental development."
	@echo "         Make sure to run 'make test' to run the full tests before submitting."

clean-tests : 
	rm -rf test-results/ test_batt_update test_hybrid_batt_update

