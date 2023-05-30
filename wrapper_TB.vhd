
-- wrapper_TB:
-- * architecture structure_driver_out:
	-- + test wrapper with only the driver out instantiated
-- * architecture structure_driver_example_3:
	-- + test wrapper with example 3: drivers in and out instantiated and interconnected


library IEEE;
use IEEE.std_logic_1164.ALL;
--use IEEE.std_logic_arith.ALL;
--use IEEE.std_logic_unsigned.ALL;
use IEEE.numeric_std.all;

entity wrapper_TB is
end wrapper_TB;


-- * architecture structure_driver_out:
	-- + test wrapper with only the driver out  instantiated

architecture structure_driver_out of wrapper_TB is
	constant PERIOD : time := 20 ns;
	signal CLK	  	: std_logic := '0';
	signal RST	  	: std_logic := '1';
	component wrapper is
		port (		
			CLK					: in std_logic;
			RST					: in std_logic;
			LED					: out std_logic_vector(7 downto 0);
			SW					: in std_logic_vector(3 downto 0);
			KEY					: in std_logic_vector(1 downto 0);
			from_GPIO_0_1_in	: in std_logic;
			from_GPIO_0_0_inout	: in std_logic;	
			to_GPIO_0_0_inout	: out std_logic;	
			to_gpio_1_0_out		: out std_logic;
			from_pio_reg_out	: in std_logic_vector(7 downto 0);
			from_pio_reg_inout	: in std_logic_vector(7 downto 0);
			to_pio_reg_in		: out std_logic_vector(7 downto 0);
			to_pio_reg_inout	: out std_logic_vector(7 downto 0) 
		);
	end component;
	for DUT: wrapper use entity work.wrapper( structure_driver_out );
		
	signal LED				: std_logic_vector(7 downto 0);
	signal SW				: std_logic_vector(3 downto 0) := "1010";
	signal KEY				: std_logic_vector(1 downto 0) := "10";
	signal GPIO_0_0_inout	: std_logic;
	signal to_GPIO_0_0_inout: std_logic;
	signal GPIO_0_1_in		: std_logic;	
	signal GPIO_1_0_out		: std_logic;	
	signal HPS_reg_out		: std_logic_vector(7 downto 0);
	signal HPS_reg_in		: std_logic_vector(7 downto 0);
	signal HPS_reg_inout	: std_logic_vector(7 downto 0);
	signal to_pio_reg_inout	: std_logic_vector(7 downto 0);
begin	
	DUT: wrapper 
		port map ( 
					
			CLK					=> CLK,
			RST					=> RST,
			LED					=> LED,
			SW					=> SW,
			KEY					=> KEY,
			from_GPIO_0_1_in	=> GPIO_0_1_in,
			from_GPIO_0_0_inout	=> GPIO_0_0_inout,	
			to_GPIO_0_0_inout	=> to_GPIO_0_0_inout,	
			to_GPIO_1_0_out		=> GPIO_1_0_out,
			from_pio_reg_out	=> HPS_reg_out,
			from_pio_reg_inout	=> HPS_reg_inout,
			to_pio_reg_in		=> HPS_reg_in,
			to_pio_reg_inout	=> to_pio_reg_inout
	);
	
	GPIO_0_0_inout <= '0' when to_GPIO_0_0_inout = '0' else 'Z';
	HPS_reg_inout(1) <= to_pio_reg_inout(1);
	
	P_HPS_reg_out: process
		variable i : natural := 0;
	begin 
		HPS_reg_inout(0) <= '1'; -- no output data 
		if RST = '1' then
			wait until RST = '0';
		end if;
		if HPS_reg_inout(2) = '0' then 
			-- wait device ready
			wait until HPS_reg_inout(2) = '0';
		end if;
		-- write data 
		HPS_reg_out <= std_logic_vector(to_unsigned(i,8));
		HPS_reg_inout(0) <= '0'; -- signal new data 
		-- wait ack
		wait until HPS_reg_inout(1) = '0';
		i := i + 1; 
		HPS_reg_inout(0) <= '1'; -- release output 
		-- wait no ack
		wait until HPS_reg_inout(1) /= '0';
	end process;
	
	P_data_in_from_wrapper: process
	begin 
		wait until to_pio_reg_inout(1) = '0';
		wait until to_pio_reg_inout(1) /= '0';
	end process;
	
	P_CLK: process
	begin -- 50MHz clock
		CLK <= not CLK;
		wait for PERIOD/2;
	end process;

	P_RST: process
	begin -- generate active 1 reset
		RST <= '1';
		wait for 3*PERIOD;
		RST <= '0';
		wait;
	end process;
	
end structure_driver_out;

library IEEE;
use IEEE.std_logic_1164.ALL;
--use IEEE.std_logic_arith.ALL;
--use IEEE.std_logic_unsigned.ALL;
use IEEE.numeric_std.all;


-- * architecture structure_driver_example_3:
	-- + test wrapper with example 3 drivers (in and out) instantiated and interconnected

architecture structure_driver_example_3 of wrapper_TB is
	constant PERIOD : time := 20 ns;
	constant DATA_WIDTH : natural := 8;
	constant VALUES: natural := 2**DATA_WIDTH;
	constant VALUE_MAX: natural := VALUES - 1;
	constant MULTIPLIER: natural := 1;
    
	signal CLK	  	: std_logic := '0';
	signal RST	  	: std_logic := '1';
	component wrapper is
		port (		
			CLK					: in std_logic;
			RST					: in std_logic;
			LED					: out std_logic_vector(7 downto 0);
			SW					: in std_logic_vector(3 downto 0);
			KEY					: in std_logic_vector(1 downto 0);
			from_GPIO_0_1_in	: in std_logic;
			from_GPIO_0_0_inout	: in std_logic;	
			to_GPIO_0_0_inout	: out std_logic;	
			to_gpio_1_0_out		: out std_logic;
			from_pio_reg_out	: in std_logic_vector(7 downto 0);
			from_pio_reg_inout	: in std_logic_vector(7 downto 0);
			to_pio_reg_in		: out std_logic_vector(7 downto 0);
			to_pio_reg_inout	: out std_logic_vector(7 downto 0) 
		);
	end component;
	for DUT: wrapper use entity work.wrapper( structure_driver_example_3 );
		
	signal LED				          : std_logic_vector(7 downto 0);
	signal SW				          : std_logic_vector(3 downto 0) := "1010";
	signal KEY				          : std_logic_vector(1 downto 0) := "10";
	signal sGPIO_0_1_in		          : std_logic := 'Z';
	signal sGPIO_0_0_inout	          : std_logic := 'Z';
	signal sWrapper_to_GPIO_0_0_inout : std_logic := 'Z';	
	signal sGPIO_1_0_out		      : std_logic;	
	signal sPIO_reg_out_DATA_out      : std_logic_vector(7 downto 0);
	signal sPIO_reg_in_DATA_in        : std_logic_vector(7 downto 0);
	signal s_uData_in                 : unsigned(7 downto 0);
	signal sPIO_reg_inout	          : std_logic_vector(7 downto 0) := ( others => 'Z' );
	signal sWrapper_to_PIO_reg_inout  : std_logic_vector(7 downto 0) := ( others => 'Z' );
	
	signal sWRn_to_PIO_reg_inout_0                : std_logic := 'Z';
	signal sDriver_out_ACKn_to_PIO_reg_inout_1    : std_logic := 'Z';
	signal sDriver_out_RDY_to_PIO_reg_inout_2     : std_logic := 'Z';
	signal sDriver_in_BUSY_to_PIO_reg_inout_3     : std_logic := 'Z';
	signal sDriver_in_DATA_RDY_to_PIO_reg_inout_4 : std_logic := 'Z';
	signal sDriver_in_OVERFLOW_to_PIO_reg_inout_5 : std_logic := 'Z';

	signal data_out : natural range 0 to VALUE_MAX := 0;
begin	
	DUT: wrapper 
		port map ( 
					
			CLK					=> CLK,
			RST					=> RST,
			LED					=> LED,
			SW					=> SW,
			KEY					=> KEY,
			from_GPIO_0_1_in	=> sGPIO_0_1_in,
			from_GPIO_0_0_inout	=> sGPIO_0_0_inout,	
			to_GPIO_0_0_inout	=> sWrapper_to_GPIO_0_0_inout,	
			to_GPIO_1_0_out		=> sGPIO_1_0_out,
			from_pio_reg_out	=> sPIO_reg_out_DATA_out,
			from_pio_reg_inout	=> sPIO_reg_inout,
			to_pio_reg_in		=> sPIO_reg_in_DATA_in,
			to_pio_reg_inout	=> sWrapper_to_PIO_reg_inout
	);
	sGPIO_0_0_inout                        <= '0' when ( sWrapper_to_GPIO_0_0_inout = '0' ) else 'Z';
	-- to Wrapper
	sPIO_reg_inout(0)                      <= '0' when sWRn_to_PIO_reg_inout_0 = '0' else 'Z';
	-- from Wrapper
	sDriver_out_ACKn_to_PIO_reg_inout_1    <= sWrapper_to_PIO_reg_inout(1);
	--sPIO_reg_inout(1)                      <= sWrapper_to_PIO_reg_inout(1);
	sDriver_out_RDY_to_PIO_reg_inout_2     <= sWrapper_to_PIO_reg_inout(2);
	--sPIO_reg_inout(2)                      <= sWrapper_to_PIO_reg_inout(2);
	sDriver_in_BUSY_to_PIO_reg_inout_3     <= sWrapper_to_PIO_reg_inout(3);
	--sPIO_reg_inout(3)                      <= sWrapper_to_PIO_reg_inout(3);
	sDriver_in_DATA_RDY_to_PIO_reg_inout_4 <= sWrapper_to_PIO_reg_inout(4); 
	--sPIO_reg_inout(4)                      <= sWrapper_to_PIO_reg_inout(4);
	sDriver_in_OVERFLOW_to_PIO_reg_inout_5 <= sWrapper_to_PIO_reg_inout(5);
	--sPIO_reg_inout(5)                      <= sWrapper_to_PIO_reg_inout(5);
	
	P_Data_out: process
		variable i : natural range 0 to VALUE_MAX := 0;
	begin 
		sWRn_to_PIO_reg_inout_0 <= '1'; -- no write  
		if RST = '1' then wait until RST /= '1'; end if;
		if sDriver_out_RDY_to_PIO_reg_inout_2 = '0' then 
			-- wait device ready
			wait until sDriver_out_RDY_to_PIO_reg_inout_2 /= '0';
		end if;
		-- write data 
		sPIO_reg_out_DATA_out <= std_logic_vector( to_unsigned( i, DATA_WIDTH ));
		data_out <= i;
		sWRn_to_PIO_reg_inout_0 <= '0'; -- write active low 
		-- wait ack
		wait until sDriver_out_ACKn_to_PIO_reg_inout_1 = '0';
		sWRn_to_PIO_reg_inout_0 <= '1'; -- stop write
		-- wait ready 
		wait until sDriver_out_RDY_to_PIO_reg_inout_2 = '1';
		if i = VALUE_MAX then
			wait; -- stop simulation forever
		end if;
		i := ( i + 1 ) mod VALUES; -- increase counter
	end process;
		
	P_Data_in_from_Wrapper: process
		variable data_in : natural range 0 to VALUE_MAX := 0;
	begin 
		if RST = '1' then
			wait until RST /= '1';
		end if;
		if sDriver_in_BUSY_to_PIO_reg_inout_3 = '1' then 		
			wait until sDriver_in_BUSY_to_PIO_reg_inout_3 = '0';
		end if;		
		wait until sDriver_in_DATA_RDY_to_PIO_reg_inout_4 = '1';
		data_in := to_integer( unsigned( sPIO_reg_in_DATA_in ));	
		if  data_in /= 0 then 
			assert data_in = data_out 
			report "Assertion " & integer'image( data_in ) & " /= " & integer'image( data_out ) 
			severity error;
		end if;		
	end process;
	
	P_CLK: process
	begin -- 50MHz clock
		CLK <= not CLK;
		wait for PERIOD/2;
	end process;

	P_RST: process
	begin -- generate active 1 reset
		RST <= '1';
		wait for 3*PERIOD;
		RST <= '0';
		wait;
	end process;
	
end structure_driver_example_3;


