# File:   Makefile
# Author: Ashok Fernandez
# Date:   16 July 2012
# Descr:  Makefile for mazeRobot docs

DEL = rm

all: file_dependencies.pdf module_dependencies.pdf makefile_dependencies.pdf build_dependencies.pdf callgraph.pdf

file_dependencies.pdf: files.d 
	../../../etc/graphdeps.py $< --out $@

module_dependencies.pdf: modules.d 
	../../../etc/graphdeps.py $< --modules --out $@

makefile_dependencies.pdf: ../makefile
	../../../etc/graphdeps.py $< --out $@

build_dependencies.pdf: ../makefile
	../../../etc/graphdeps.py $< --out $@ --showops

callgraph.pdf: callgraph.d
	../../../etc/graphdeps.py --calls --modules $< --out $@ --showops


files.d: ../makefile
	(cd ..;	../../etc/makemake.py --relpath --files . ./ > doc/files.d)


modules.d: ../makefile
	(cd ..;	../../etc/makemake.py --relpath --modules . ./ > doc/modules.d)


callgraph.d: ../makefile
	(cd ..;	../../etc/makemake.py --cc="avr-gcc" --cflags="-Os -mmcu=atmega8" --relpath --calls . ./ > doc/callgraph.d)


# Clean: delete derived files.
.PHONY: clean
clean: 
	-$(DEL) *.d *.pdf
