# IEC 61850 Demo Tools

This repository is used to maintain IEC 61850 demos. It features tools for intelligent electronic device (IED) enumeration, data reading and device control. The tools largely base on libiec61850. If you need a demo device its suggested to have a look at libiec61850/examples/server_example* first.

## Tools and Scripts
The repo is split in two folders
* src contains all relevant tool sources
* scripts provides example bash scripts that automate SPCs on/off and toggling two SPCs in the same intelligent electronc device (IED)

### Enum Tool
The tool takes the hostname and port of an IEC 61850 enabled device and enumerates over the data model. Watch out for inputs (e.g. Ind stands for indicators) and outputs (e.g. SPC - single point control - which usually represents an output that can be switched on/off). Check the IEC 61850 specs for a full list of data classes and types.

### Read Tool
The read tool provides simple means to read values from an intelligent electronic device (IDE). Currently, the tool supports only few functional constraints (FCs).

Supported FCs include:
* ST Status information of process values
* CO Binary process commands

Further FCs such as listed in the IEC 61850 specs are currently unsupported.

### Nuke Tool
The nuke tool supports switching outputs of intelligent electronic devices (IEDs). Specifically, any controllable point that can be operated with boolean (true/false) can be switched. This has been tested on IEDs that provide single point controls (SPCs) within their generic logical input/output node (GGIO).


_!!! Switching might affect the related process, cause severe damage to devices, the environment or life_

## Build Demo Tools

Clone this repo and check whether pre-requisites are fullfilled.
```
git clone https://github.com/CBrunsch/iec61850.git
cd iec61850/src
sudo make install
```

## Pre-requisites

Make sure libiec61850 is installed. Otherwise grab a copy from their git and install the library.
```
git clone https://github.com/mz-automation/libiec61850.git
cd libiec61850
sudo INSTALL_PREFIX=/usr/local make install
```
