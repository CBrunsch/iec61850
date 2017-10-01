SRC_DIRS = enum
SRC_DIRS += nuke
SRC_DIRS += read

all:	src

src:
	-for d in $(SRC_DIRS); do(cd $$d && $(MAKE)); done

clean:
	-for d in $(SRC_DIRS); do(cd $$d && $(MAKE) clean); done

install:
	-for d in $(SRC_DIRS); do(cd $$d && cp iec61850_$$d /usr/local/bin/); done

uninstall:
	-for d in $(SRC_DIRS); do(rm /usr/local/bin/iec61850_$$d); done
