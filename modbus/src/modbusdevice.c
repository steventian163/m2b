#include "modbusdevice.h"
#include "mylogging.h"
#include "modbus-rtu.h"
#include "modbus-tcp.h"

// boxihua
#define modbus_baud_rate_device_water_cool_boxihua (9600)
#define modbus_slave_address_device_water_cool_boxihua (2)
#define modbus_parity_device_water_cool_boxihua 'E'
#define modbus_databit_device_water_cool_boxihua 8
#define modbus_stopbit_device_water_cool_boxihua 1


#define modbus_serial_mode_device_water_cool_boxihua MODBUS_RTU_RS485

modbus_t* P_Modbus_device[MaxDeviceCount];

int LastDeviceId = -1;

modbus_t* modbus_new_tcp_device()
{
	// ignore this. IP address.
	modbus_t* pContext = modbus_new_tcp("192.168.1.12", 502);
	modbus_set_slave(pContext, 2);

	if (modbus_connect(pContext) < 0)
	{
		my_log_error("modbus_connect");
		return NULL;
	}


	return pContext;

}

int Modbus_Init()
{

	int i = 0;
	for (; i< MaxDeviceCount; ++i)
	{
		P_Modbus_device[i] = NULL;
	}
	return 0;
}

modbus_t* GetModbus_Client(int deviceAddress)
{
	if (deviceAddress > MaxDeviceCount)
	{
		return NULL;
	}

	if (P_Modbus_device[deviceAddress] == NULL)
	{
		// close last device first
		if (LastDeviceId >=0 && P_Modbus_device[LastDeviceId] != NULL)
		{
			modbus_close_device(P_Modbus_device[LastDeviceId]);			
			P_Modbus_device[LastDeviceId] = NULL;
		}

		//TODO: Put the serial port to configuration file. 
#ifdef _WIN32
		P_Modbus_device[deviceAddress] = modbus_new_rtu_device("COM2", deviceAddress);
#else
		P_Modbus_device[deviceAddress] = modbus_new_rtu_device("/dev/ttyO1", deviceAddress);
#endif
		LastDeviceId = deviceAddress;
		
	}

	return P_Modbus_device[deviceAddress];
}

modbus_t* modbus_new_rtu_device(const char* serial_port, int slaveAddr)
{
	modbus_t* context = modbus_new_rtu(serial_port, 
		modbus_baud_rate_device_water_cool_boxihua,
		modbus_parity_device_water_cool_boxihua,
		modbus_databit_device_water_cool_boxihua,
		modbus_stopbit_device_water_cool_boxihua);

	if (context == NULL)
	{
		my_log_error("modbus_new_rtu");
		return NULL;
	}

#ifdef HAVE_DECL_TIOCSRS485
	if (modbus_rtu_set_serial_mode(context, modbus_serial_mode_device_water_cool_boxihua) < 0)
	{
		my_log_error("modbus_rtu_set_serial_mode");
		return NULL;
	}

#endif 

	if (modbus_set_slave(context, slaveAddr) < 0)
	{
		my_log_error("modbus_set_slave");
		return NULL;
	}

	if (modbus_connect(context) < 0)
	{
		my_log_error("modbus_connect");
		return NULL;
	}

	return context;
}

int modbus_close_device(modbus_t* context)
{
	if (modbus_flush(context) < 0)
	{
		my_log_error("modbus_close_rtu_device");
		return -1;
	}
	modbus_close(context);
	modbus_free(context);

	return 0;
}


