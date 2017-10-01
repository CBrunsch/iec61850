#! /bin/bash

IP="localhost"
GGIO="simpleIOGenericIO/GGIO1."

iec61850_nuke $IP $GGIO"SPCSO2" false
iec61850_nuke $IP $GGIO"SPCSO1" true
