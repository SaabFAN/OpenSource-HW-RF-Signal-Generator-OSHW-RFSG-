## Generated SDC file "ARSG_GlueLogic.out.sdc"

## Copyright (C) 2018  Intel Corporation. All rights reserved.
## Your use of Intel Corporation's design tools, logic functions 
## and other software and tools, and its AMPP partner logic 
## functions, and any output files from any of the foregoing 
## (including device programming or simulation files), and any 
## associated documentation or information are expressly subject 
## to the terms and conditions of the Intel Program License 
## Subscription Agreement, the Intel Quartus Prime License Agreement,
## the Intel FPGA IP License Agreement, or other applicable license
## agreement, including, without limitation, that your use is for
## the sole purpose of programming logic devices manufactured by
## Intel and sold by Intel or its authorized distributors.  Please
## refer to the applicable agreement for further details.


## VENDOR  "Altera"
## PROGRAM "Quartus Prime"
## VERSION "Version 18.1.0 Build 625 09/12/2018 SJ Lite Edition"

## DATE    "Fri Mar 15 17:13:04 2019"

##
## DEVICE  "5M1270ZT144C5"
##


#**************************************************************
# Time Information
#**************************************************************

set_time_format -unit ns -decimal_places 3



#**************************************************************
# Create Clock
#**************************************************************

create_clock -name {SPI_CLK} -period 20.000 -waveform { 0.000 10.000 } [get_ports { SPI_CLK }]
create_clock -name {SCL} -period 100.000 -waveform { 0.000 50.000 } [get_ports { SCL }]
create_clock -name {SDA} -period 100.000 -waveform { 0.000 50.000 } [get_ports { SDA }]
create_clock -name {ADF4351_CLK} -period 20.000 -waveform { 0.000 10.000 } [get_ports { ADF4351_CLK}]
create_clock -name {ADF5355_CLK} -period 20.000 -waveform { 0.000 10.000 } [get_ports { ADF5355_CLK }]
create_clock -name {ADF4351_MOSI} -period 20.000 -waveform { 0.000 10.000 } [get_ports { ADF4351_MOSI}]
create_clock -name {ADF5355_MOSI} -period 20.000 -waveform { 0.000 10.000 } [get_ports { ADF5355_MOSI }]
create_clock -name {TFT_CLK} -period 20.000 -waveform { 0.000 10.000 } [get_ports { TFT_CLK }]


#**************************************************************
# Create Generated Clock
#**************************************************************



#**************************************************************
# Set Clock Latency
#**************************************************************



#**************************************************************
# Set Clock Uncertainty
#**************************************************************



#**************************************************************
# Set Input Delay
#**************************************************************



#**************************************************************
# Set Output Delay
#**************************************************************



#**************************************************************
# Set Clock Groups
#**************************************************************



#**************************************************************
# Set False Path
#**************************************************************



#**************************************************************
# Set Multicycle Path
#**************************************************************



#**************************************************************
# Set Maximum Delay
#**************************************************************



#**************************************************************
# Set Minimum Delay
#**************************************************************



#**************************************************************
# Set Input Transition
#**************************************************************

