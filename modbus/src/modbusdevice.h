#ifndef my_modbusdevice_H_
#define my_modbusdevice_H_

#include "modbus.h"

MODBUS_BEGIN_DECLS

extern modbus_t* P_Modbus_device;
 

typedef
enum {
	device_water_cool_boxihua
} rtu_device;

modbus_t* modbus_new_rtu_device(const char* serial_port, rtu_device device);


modbus_t* modbus_new_tcp_device();

int modbus_close_device(modbus_t* context);


MODBUS_END_DECLS

#endif