------------------------------------------------------------------------------
-- Example of use of i2c slave receiver
------------------------------------------------------------------------------
-- Intended target: Xilinx CoolRunner-II CPLD  (XC2C64A)
-- Development tools: XILINX ISE 7.1i webpack
-- Author:  DMITRY PETROV
-- Notes:
-- Date:     11-09-2005
-- Revision: 1.0
------------------------------------------------------------------------------ 
-- ===========================================================================
-- DISCLAIMER: This code is FREEWARE which is provided on an “as is” basis, 
-- YOU MAY USE IT ON YOUR OWN RISK, WITHOUT ANY WARRANTY. 
-- ===========================================================================




library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

------------------------------------------------------------------------------
entity top is
	port(
	   -- I2C interface
		---------------
	   i2c_clk: in std_logic;
		i2c_dat: inout std_logic;

		reset_in: in std_logic;

	   -- Data output
		--------------- 
		vdat_out: out std_logic_vector(7 downto 0)
	);
	-- Xilinx CoolRunner II - SCHMITT TRIGGER activation on the folowing inputs:
	attribute SCHMITT_TRIGGER: string;
	attribute SCHMITT_TRIGGER of i2c_clk: signal is "TRUE"; 
	attribute SCHMITT_TRIGGER of i2c_dat: signal is "TRUE";
end top;

------------------------------------------------------------------------------
architecture Behavioral of top is
	signal i2c_dout: std_logic_vector(7 downto 0);

	-- i2c COMPONENT declaration
	component i2cs_rx is
		generic(
			WR		: std_logic:='0';
			DADDR	: std_logic_vector(6 downto 0):= "0010001";		   -- 11h (22h) device address
			ADDR		: std_logic_vector(7 downto 0):= "00000000"		-- 00h	    sub address
		);
		port(
			RST		: in std_logic;
			SCL		: in std_logic;
			SDA		: inout std_logic;
			DOUT		: out std_logic_vector(7 downto 0)					-- Recepted over i2c data byte
		);
	end component;
begin

------------------------------------------------------------------------------
	-- i2c COMPONENT PORT MAP
	i2cs_rx_lab: i2cs_rx
	port map (
		SCL=>i2c_clk,
		RST=>reset_in,
		SDA=>i2c_dat,
		DOUT=>i2c_dout 
	);

------------------------------------------------------------------------------
	vdat_out <= i2c_dout;


end Behavioral;
------------------------------------------------------------------------------




































