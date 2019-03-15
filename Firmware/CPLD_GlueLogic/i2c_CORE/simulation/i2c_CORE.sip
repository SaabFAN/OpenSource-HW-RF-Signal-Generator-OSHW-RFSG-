set_global_assignment -entity "i2c_CORE" -library "lib_i2c_CORE" -name IP_TOOL_NAME "Qsys"
set_global_assignment -entity "i2c_CORE" -library "lib_i2c_CORE" -name IP_TOOL_VERSION "18.1"
set_global_assignment -entity "i2c_CORE" -library "lib_i2c_CORE" -name IP_TOOL_ENV "Qsys"
set_global_assignment -library "lib_i2c_CORE" -name SPD_FILE [file join $::quartus(sip_path) "../i2c_CORE.spd"]
set_global_assignment -library "lib_i2c_CORE" -name MISC_FILE [file join $::quartus(sip_path) "../../i2c_CORE.qsys"]

set_global_assignment -library "lib_i2c_CORE" -name MISC_FILE [file join $::quartus(sip_path) "i2c_CORE.vhd"]
set_global_assignment -library "lib_i2c_CORE" -name MISC_FILE [file join $::quartus(sip_path) "submodules/i2c_CORE_ufm_i2c_0.v"]
