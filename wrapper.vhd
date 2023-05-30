-- wrapper

-- architectures:
-- RTL_test: example testing HPS inout register used as control signals
-- structure_driver_out_example_3: example using a driver output to generate variable width pulses
-- structure_driver_in_example_3: example using a driver input to read the width of an input pulse
-- structure_driver_example_3: example using both drivers in/out 

-- configuration:
-- use the configuration at the end of the file to select the architecture to implement.
-- Just change the architecture name.

library ieee;
use ieee.std_logic_1164.all;

entity wrapper is
	port (		
		CLK					: in std_logic;
		RST					: in std_logic;
		LED					: out std_logic_vector(7 downto 0);
		SW					: in std_logic_vector(3 downto 0);
		KEY					: in std_logic_vector(1 downto 0);
		from_GPIO_0_1_in	: in std_logic; -- peripheral input (RX)
		from_GPIO_0_0_inout	: in std_logic;	-- bidirectional peripheral input (S2C data)
		to_GPIO_0_0_inout	: out std_logic; -- bidirectional peripheral output (S2C data) 
		to_gpio_1_0_out		: out std_logic; -- peripheral output (TX)
		from_pio_reg_out	: in std_logic_vector(7 downto 0);
		from_pio_reg_inout	: in std_logic_vector(7 downto 0);
		to_pio_reg_in		: out std_logic_vector(7 downto 0);
		to_pio_reg_inout	: out std_logic_vector(7 downto 0) 
	);
end wrapper;

architecture FreqOut of wrapper is
	
component FreqOut is
    Port ( 	   
         clk			: in std_logic;
		reset_n			: in std_logic;
		reg0value		: in std_logic_vector(7 downto 0);
		reg1enable		: in std_logic;
		gpio0			: out std_logic);
end component;
 
	for I_FreqOut: FreqOut use entity work.FreqOut(rtl);
	
	signal LED_0 : std_logic; -- state s0
	signal LED_1 : std_logic; -- state s1
	
	signal WRn_from_pio_reg_inout_0	: std_logic;
	signal ACKn_to_pio_reg_inout_1	: std_logic; -- ACKn 
	signal RDY_to_pio_reg_inout_2	: std_logic; -- ready	
			
begin	
	--LED <= '0';
	to_GPIO_0_0_inout <= '0';
	to_pio_reg_in <= (others => '0');
	to_pio_reg_inout <= (others => '0');
	
	I_FreqOut: FreqOut 
		port map ( 					
			clk							=> CLK,
			reset_n							=> '1',	
			gpio0			=> to_GPIO_1_0_out,			
			reg0value		=> from_pio_reg_out,
			reg1enable => '1'
	);
end FreqOut;
