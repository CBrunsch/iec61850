/*
 * This code is based on the libiec61850 and provides simple means to read
 * values from an intelligent electronic device (IDE). Currently, the tool
 * supports only few functional constraints (FCs).
 *
 * Supported FCs include:
 * - ST Status information of process values
 * - CO Binary process commands
 *
 * Further FCs such as listed in the IEC 61850 specs remain unsupported.
 *
 * Known bugs
 * - the read tool assumes the IED service is bound to port TCP/102
 */

// deprecated for ST and CO... check common.h for latest alternatives
#define CONFIG_PROVIDE_OLD_FC_DEFINES 1

#include "iec61850_client.h"
#include "iec61850_common.h"
#include "hal_thread.h"

#include <stdlib.h>
#include <stdio.h>

static void read(IedConnection con, IedClientError error, char* sp, FunctionalConstraint fc) {

   printf("reading: %s: ",sp);
   MmsValue* stVal = IedConnection_readObject(con, &error, sp, fc);

   if (error == IED_ERROR_OK) {
       bool state = MmsValue_getBoolean(stVal);
       MmsValue_delete(stVal);

       printf("%i\n", state);
   }
   else {
      printf("failed!\n");
   }
}

int main(int argc, char** argv) {

    char* hostname = "localhost";
    char* sp = "";
    FunctionalConstraint fc = ST;
    int tcpPort = 102;

    if (argc == 4) {
        hostname = argv[1];
        sp = argv[2];

        if (strncmp("ST", argv[3], 2) == 0)
            fc = ST;
        else if (strncmp("CO", argv[3], 2) == 0)
            fc = CO;
    }
    else {
        printf("Usage examples:\n");
        printf("%s localhost ServerLogicalDevice/GGIO1.Ind1.stVal ST\n", argv[0]);
        printf("%s localhost ServerLogicalDevice/GGIO1.SPCSO1.Oper.ctlVal CO\n", argv[0]);
        return 1;
    }

    IedClientError error;

    IedConnection con = IedConnection_create();

    IedConnection_connect(con, &error, hostname, tcpPort);

    if (error == IED_ERROR_OK) {
	read(con, error, sp, fc);
        IedConnection_close(con);
    }
    else {
    	printf("Connection failed!\n");
    }

    IedConnection_destroy(con);
}


