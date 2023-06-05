-----------------------------------------------------------------------------
-- Title           : frequency generator
-----------------------------------------------------------------------------
-- Author          : Antoine Collet & Bruno Hougardy
-- Date Created    : 17-05-23
-----------------------------------------------------------------------------
-- Description     : Description
--							
--
-----------------------------------------------------------------------------
-- Copyright 2016. All rights reserved
-----------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use IEEE.numeric_std.all;

 
entity FreqOut is 

	generic
	(
		MIN_COUNT : natural :=1000;
		MAX_COUNT : natural :=1000000;
		period: natural :=1000000000
		 
		
	);
	
	port 						-- Declares the different ports of the component
	(	clk			: in std_logic;
		reset_n			: in std_logic;
		reg0value		: in std_logic_vector(7 downto 0);
		reg1enable		: in std_logic;
		gpio0			: out std_logic
	);

end entity;

architecture rtl of FreqOut is 
	constant STEP      : natural :=(MAX_COUNT-MIN_COUNT)/255;
	signal gpiobuff	: std_logic := '0';	-- These 2 signals are the values manipulated during the process, gpiobuff is used as a buffer before outputting the frequency
	signal cnt     	: natural :=0;
	
begin 

	gpio0 <= gpiobuff; 			--gpio is constantly following the value of gpiobuff
	
	process(clk)
		variable max: natural :=0;
		variable max2: natural :=0;
	
	begin 
		if (rising_edge(clk)) then
			if reset_n='0' then
				gpiobuff<='0'; 				-- when the counter reaches the max value (desired value to obtain the good frquency), a pulse is generated
				cnt<=0; -- this formula translate the 8-bit value of reg0value to a certain counter value corresponding
											-- to a certain frequency 
			elsif reg1enable = '1' then
				cnt<=cnt+1;
				if cnt = (0) then
					gpiobuff<='0'; 				-- when the counter reaches the max value (desired value to obtain the good frquency), a pulse is generated
					max := (period/((to_integer(unsigned(reg0value))*3917+MIN_COUNT)*20)); --MIN_COUNT+to_integer(unsigned(reg0value))*STEP
					max2 := max/2;
				elsif cnt = max2 then
					gpiobuff<='1'; 				-- when the counter reaches the max value (desired value to obtain the good frquency), a pulse is generated
				elsif cnt = max then
					cnt<=0;
				end if; 
			else
				cnt<=0;
			end if;
		end if;	
	end process;
	
end rtl;




-- Quartus Prime VHDL Template
-- Binary Counter


