@echo off


GOTO EndUsageComment
rem the test command, the command looks like:
rem Usage: bacrp.exe device-instance object-type object-instance property [index]

rem the device-instance is 29001
rem the object-type is <0, analog input> <3, binary input>
rem the object-instance <0-23 for analog input>, <0-96 for binary input>
    OBJECT_ANALOG_INPUT = 0,
    OBJECT_BINARY_INPUT = 3,
    OBJECT_DEVICE = 8,
    MAX_BACNET_OBJECT_TYPE = 1024
rem the property is: 
    PROP_OBJECT_IDENTIFIER = 75,
    PROP_OBJECT_NAME = 77,
    PROP_OBJECT_TYPE = 79,
    PROP_PRESENT_VALUE = 85,
    PROP_STATUS_FLAGS = 111,
    PROP_UNITS = 117,
	
:EndUsageComment

set /a objectInstanceStart=12
set /a objectInstanceEnd=17

set /a property=85
set /a objectType=0



set /a objectInstance=%objectInstanceStart%

:objectInstanceLoop
bacrp.exe 29001 %objectType%  %objectInstance% %property%

if %objectInstance% LSS %objectInstanceEnd% (
		set /a objectInstance+=1
		goto objectInstanceLoop
	) 

