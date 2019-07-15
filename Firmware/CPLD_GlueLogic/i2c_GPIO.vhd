----------------------------------------------------
-- I2C Slave FSM
----------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity i2c_slave_fsm is
    generic (
    SLAVE_ADDR : std_logic_vector(6 downto 0) := "0001111");
    port (
    --I2C IO Signals
    scl             : inout std_logic;
    sda             : inout std_logic;
        
    --Transaction is in progress
    in_progress     : out   std_logic;

    --READ command signals
    tx_done         : out   std_logic;
    tx_byte         : in    std_logic_vector(7 downto 0);

    --WRITE command signals
    rx_byte         : out   std_logic_vector(7 downto 0); 
    rx_data_rdy     : out   std_logic;

    --System clock
    clk             : in    std_logic);
end i2c_slave_fsm;


architecture i2c_slave_fsm of i2c_slave_fsm is
    --Output signals
    signal sda_out_en       : std_logic := '0';
    signal sda_o            : std_logic := '0';
    signal rx_data_rdy_reg  : std_logic                    := '0';
    signal tx_byte_buf      : std_logic_vector(7 downto 0) := (others => '0');
    
     --Pipelined SDA and SCL signals
    signal scl_d    : std_logic := '1';
    signal scl_d2   : std_logic := '1';
    signal sda_d    : std_logic := '1';
    signal sda_d2   : std_logic := '1';
    
    --Strobes for SCL edges and Start/Stop bits
    signal start_strobe       : std_logic := '0';
    signal stop_strobe        : std_logic := '0';
    signal scl_rising_strobe  : std_logic := '0';
    signal scl_falling_strobe : std_logic := '0';
    
     --I2C FSM control signals
    type state_t is (IDLE, READ_ADDRESS, SEND_ACK_1, WRITE_CMD,
                     READ_CMD, WAIT_ACK_1, WAIT_ACK_2, WAIT_STOP);
               
    signal state            : state_t              := IDLE;
    signal rw_command       : std_logic            := '0';  --Read or write command
    signal bit_counter      : integer range 0 to 8 := 0;    --Counts number of bits per transaction
    signal continue_read    : std_logic            := '0';

    --Signals for storing address/data from master
    signal addr_buf     : std_logic_vector(6 downto 0) := (others => '0');
    signal rx_data_buf  : std_logic_vector(7 downto 0) := (others => '0');
begin

--I2C State Machine
i2c_fsm_p : process (clk) is
begin
    if rising_edge(clk) then
        -- Default values
        sda_o       <= '0';
        sda_out_en  <= '0';
        rx_data_rdy_reg <= '0';

        case state is
            --Idle state (functionally same as STOP)
            when IDLE =>
                if start_strobe = '1' then
                    state          <= READ_ADDRESS;
                    bit_counter <= 0;
                end if;
                
            --Reading 7 bit address from master
            when READ_ADDRESS =>
                if scl_rising_strobe = '1' then
                    if bit_counter < 7 then
                        --Store the first 7 bits that are read into the address buffer
                        bit_counter             <= bit_counter + 1;
                        addr_buf(6-bit_counter) <= sda_d;
                    elsif bit_counter = 7 then
                        --The next bit indicates whether it is a read or write command
                        bit_counter     <= bit_counter + 1;
                        rw_command      <= sda_d;
                    end if;
                end if;

                if bit_counter = 8 and scl_falling_strobe = '1' then
                    bit_counter <= 0;
                    --Check if the address from the master matches the slave address. If it does, 
                    --acknowledge, otherwise wait for stop bit.
                    if addr_buf = SLAVE_ADDR then 
                        state <= SEND_ACK_1;
                        if rw_command = '1' then 
                            tx_byte_buf <= tx_byte;
                        end if;
                    else
                        state <= IDLE;
                    end if;
                end if;

            --Send ACK bit by holding SDA low through one SCL cycle
            when SEND_ACK_1 =>
                sda_out_en <= '1';
                sda_o   <= '0';
                if scl_falling_strobe = '1' then
                    if rw_command = '0' then
                        state <= WRITE_CMD;
                    else
                        state <= READ_CMD;
                    end if;
                end if;

            --Waiting for acknowledge from master
            when WAIT_ACK_1 =>
                if scl_rising_strobe = '1' then
                    state <= WAIT_ACK_2;
                    
                    if sda_d = '1' then
                        --NACK received, stop transmission and wait for STOP bit
                        continue_read <= '0';
                    else
                        --ACK received, continue transmission
                        continue_read       <= '1';
                        tx_byte_buf <= tx_byte;
                    end if;
                end if;
                
            --Waiting for acknowledge from master
            --Requires two states to wait for the entire SCL cycle to pass
            when WAIT_ACK_2 =>
                if scl_falling_strobe = '1' then
                    if continue_read = '1' then
                        if rw_command = '0' then
                            state <= WRITE_CMD;
                        else
                            state <= READ_CMD;
                        end if;
                    else
                        state <= WAIT_STOP;
                    end if;
                end if;
                
            --Write command (write from master to slave)
            when WRITE_CMD =>
                --On each rising edge, read the data bit on the SDA line and store it
                --in rx_data_buf
                if scl_rising_strobe = '1' then
                    if bit_counter <= 7 then
                        rx_data_buf(7-bit_counter)  <= sda_d;
                        bit_counter                 <= bit_counter + 1;
                    end if;
                    if bit_counter = 7 then
                        rx_data_rdy_reg     <= '1';
                    end if;
                end if;

                --When the byte is done, send an ACK
                if scl_falling_strobe = '1' and bit_counter = 8 then
                    state           <= SEND_ACK_1;
                    bit_counter     <= 0;
                end if;

            --Read command (Master reads data from slave)
            when READ_CMD =>
                sda_out_en <= '1';
                sda_o   <= tx_byte_buf(7-bit_counter);
                
                --The SDA line must be set before the rising edge of SCL.
                --Therefore, set it on the falling edge of the previous SCL cycle
                if scl_falling_strobe = '1' then
                    if bit_counter < 7 then
                        bit_counter <= bit_counter + 1;
                    elsif bit_counter = 7 then
                        --Wait for an ACK after sending a byte
                        state          <= WAIT_ACK_1;
                        bit_counter <= 0;
                    end if;
                end if;

            --NACK receiving during Read command, wait for stop bit
            when WAIT_STOP =>
                tx_done     <= '1';
                null;
        end case;

        --Reset when a transmission stops or starts
        if start_strobe = '1' then
            tx_done     <= '0';
            bit_counter <= 0;
            state       <= READ_ADDRESS;
        end if;

        if stop_strobe = '1' then
            tx_done     <= '0';
            bit_counter <= 0;
            state       <= IDLE;
        end if;

    end if;
end process;

--Strobe logic
strobe_p : process (clk) is
begin
    if rising_edge(clk) then
        --Pipelined SDA and SCL signals
        scl_d       <= scl;
        scl_d2      <= scl_d;
        sda_d       <= sda;
        sda_d2      <= sda_d;
        
        --Logic for SCL edge detection strobes
        scl_rising_strobe <= '0';
        scl_falling_strobe <= '0';
        
        if scl_d2 = '0' and scl_d = '1' then
            scl_rising_strobe <= '1';
        end if;
     
        if scl_d2 = '1' and scl_d = '0' then
            scl_falling_strobe <= '1';
        end if;

        --Logic for Start and stop bit detection 
        start_strobe <= '0';
        stop_strobe  <= '0';
        
        if scl_d = '1' and scl_d2 = '1' and sda_d2 = '1' and sda_d = '0' then
            start_strobe <= '1';
            stop_strobe  <= '0';
        end if;

        if scl_d2 = '1' and scl_d = '1' and sda_d2 = '0' and sda_d = '1' then
            start_strobe <= '0';
            stop_strobe  <= '1';
        end if;
    end if;
end process;

--SDA and SCL outputs
sda     <= sda_o when sda_out_en = '1' else 'Z';  
scl     <= 'Z';

--Local unit outputs
rx_data_rdy     <= rx_data_rdy_reg;
rx_byte         <= rx_data_buf;

--In progress signal
in_progress     <= '0' when state = IDLE else '1';

end i2c_slave_fsm;