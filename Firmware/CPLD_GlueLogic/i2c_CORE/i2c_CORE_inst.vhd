	component i2c_CORE is
		port (
			a0           : in    std_logic := 'X'; -- a0
			a1           : in    std_logic := 'X'; -- a1
			a2           : in    std_logic := 'X'; -- a2
			scl          : inout std_logic := 'X'; -- scl
			sda          : inout std_logic := 'X'; -- sda
			osc          : out   std_logic;        -- osc
			global_reset : in    std_logic := 'X'  -- global_reset
		);
	end component i2c_CORE;

	u0 : component i2c_CORE
		port map (
			a0           => CONNECTED_TO_a0,           --           a0.a0
			a1           => CONNECTED_TO_a1,           --           a1.a1
			a2           => CONNECTED_TO_a2,           --           a2.a2
			scl          => CONNECTED_TO_scl,          --          scl.scl
			sda          => CONNECTED_TO_sda,          --          sda.sda
			osc          => CONNECTED_TO_osc,          --          osc.osc
			global_reset => CONNECTED_TO_global_reset  -- global_reset.global_reset
		);

