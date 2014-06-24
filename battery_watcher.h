#ifndef _BATTERY_PROTOCOL_H
#define _BATTERY_PROTOCOL_H

struct battery_data{
    unsigned state:8;
    unsigned cell_voltage0:16;
    unsigned cell_voltage1:16;
    unsigned cell_voltage2:16;
    unsigned cell_voltage3:16;
    unsigned cell_voltage4:16;
    unsigned cell_voltage5:16;
    unsigned cell_voltage6:16;
    unsigned cell_voltage7:16;
    unsigned temperature:16;
    unsigned error_state:8;
} __attribute__ ((packed)) __attribute__((__may_alias__));
	
#endif
