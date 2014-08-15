/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"

using namespace battery_watcher;

Task::Task(std::string const& name, TaskCore::TaskState initial_state)
    : TaskBase(name, initial_state)
{
}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : TaskBase(name, engine, initial_state)
{
}

Task::~Task()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Task.hpp for more detailed
// documentation about them.

bool Task::configureHook()
{
    if (! TaskBase::configureHook())
        return false;
    return true;
}
bool Task::startHook()
{
    if (! TaskBase::startHook())
        return false;
    read_pointer = 0;
    return true;
}
void Task::updateHook()
{
    TaskBase::updateHook();
    canbus::Message msg;
    if(readCanMsg(msg)){
    //    printf("Got message\n");
        for(uint8_t i=0;i<msg.size;i++){
            if(read_pointer == 0 && msg.data[i] != '@'){
  //              printf("Could not find start char it is %02x\n",msg.data[i]);
            }else{
                buffer[read_pointer++] = msg.data[i];
            }
        }
        if(read_pointer == sizeof(battery_data)+2){
//            printf("The size is full and the contend is: %02x %02x \n",buffer[0], buffer[sizeof(battery_data)+1]);
            if(buffer[0] == '@' && buffer[sizeof(battery_data)+1] == '\n'){
                battery_data d;
                memcpy(&d,buffer+1,sizeof(battery_data));
                /*
                printf("State: %i\n",d.state);
                printf("%i ", d.cell_voltage0);
                printf("%i ", d.cell_voltage1);
                printf("%i ", d.cell_voltage2);
                printf("%i ", d.cell_voltage3);
                printf("%i ", d.cell_voltage4);
                printf("%i ", d.cell_voltage5);
                printf("%i ", d.cell_voltage6);
                printf("%i ", d.cell_voltage7);
                printf("\n");
                */
                BatteryData da;
                da.cell_voltage[0] = d.cell_voltage0;
                da.cell_voltage[1] = d.cell_voltage1;
                da.cell_voltage[2] = d.cell_voltage2;
                da.cell_voltage[3] = d.cell_voltage3;
                da.cell_voltage[4] = d.cell_voltage4;
                da.cell_voltage[5] = d.cell_voltage5;
                da.cell_voltage[6] = d.cell_voltage6;
                da.cell_voltage[7] = d.cell_voltage7;
                da.state = d.state;
                da.temperature = d.temperature;
                da.error_state = d.error_state;
                _battery_info.write(da);
            }
            read_pointer=0;
        }
    }
}
void Task::errorHook()
{
    TaskBase::errorHook();
}
void Task::stopHook()
{
    TaskBase::stopHook();
}
void Task::cleanupHook()
{
    TaskBase::cleanupHook();
}
