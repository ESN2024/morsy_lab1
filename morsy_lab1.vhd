library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity morsy_lab1 is port (
        clk : in std_logic := '0' ;
        reset_n : in std_logic :='0';
        Switch  : in  std_logic_vector(7 downto 0);
        Led : out std_logic_vector(7 downto 0);
		  p_btn: in std_logic_vector(1 downto 0));
end entity;

architecture arch of morsy_lab1 is
    
    component conf is
        port (
            blinked_led_external_connection_export : out std_logic_vector(7 downto 0);                    -- export
            clk_clk                                : in  std_logic                    := 'X';             -- clk
            reset_reset_n                          : in  std_logic                    := 'X';             -- reset_n
            switch_external_connection_export      : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
            push_btn_external_connection_export    : in  std_logic_vector (1 downto 0)       := (others => 'X')             -- export
        );
    end component conf;
begin
    u0 : component conf
        port map (
            blinked_led_external_connection_export => Led, -- blinked_led_external_connection.export
            clk_clk                                => clk,                                --                             clk.clk
            reset_reset_n                          => reset_n,                          --                           reset.reset_n
            switch_external_connection_export      => Switch,      --      switch_external_connection.export
            push_btn_external_connection_export    => p_btn     --    push_btn_external_connection.export
        );

end architecture;