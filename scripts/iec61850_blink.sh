#! /bin/bash

IP="localhost"
GGIO="simpleIOGenericIO/GGIO1."
SNOOZE=1

while true; do
    iec61850_nuke $IP $GGIO"SPCSO2" false
    iec61850_nuke $IP $GGIO"SPCSO1" true
    sleep $SNOOZE
    iec61850_nuke $IP $GGIO"SPCSO1" false
    iec61850_nuke $IP $GGIO"SPCSO2" true
    sleep $SNOOZE 
done
