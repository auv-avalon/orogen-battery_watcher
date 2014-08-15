require 'orocos'

#Orocos::CORBA.name_service = "127.0.0.1"
Orocos.initialize
Orocos::run 'battery_watcher::Task' => "task_test", "canbus::Task" => "can_test" do

  can_task = Orocos::TaskContext.get "can_test"
  can_task.device = "can0" # "can0" for front, "can1" for back
  can_task.deviceType = :SOCKET
  pp "can_task.watch: #{can_task.watch("board", 0x447, 0x7FF)}" # 0x130 = front, 0x132 = back (momentan noch 0x131 = back)
  can_task.configure
  can_task.start
  
  task = Orocos::TaskContext.get 'task_test'  

  can_task.board.connect_to task.can_in, :type => :buffer, :size => 20
#  can_task.in.connect_to task.canOut, :type => :buffer, :size => 20
  
  # set all filter parameters to 0 to get raw values
  #task.filter_param_internal_pressure = 0
  #task.filter_param_temperature = 0
  #task.filter_param_water = 0
  #task.filter_param_external_pressure = 8 
  task.configure
  task.start
  
  reader = task.battery_info.reader
  
  while true
#    if sample = reader.read
#        STDOUT.puts sample.state
#        STDOUT.puts sample.cell_voltage0
#        STDOUT.puts sample.cell_voltage1
#        STDOUT.puts sample.cell_voltage2
#        STDOUT.puts sample.cell_voltage3
#        STDOUT.puts sample.cell_voltage4
#        STDOUT.puts sample.cell_voltage5
#        STDOUT.puts sample.cell_voltage6
#        STDOUT.puts "#####################" 
#    end
    sleep(0.5)
  end
end

