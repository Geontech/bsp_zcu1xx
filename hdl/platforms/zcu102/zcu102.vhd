-- THIS FILE WAS ORIGINALLY GENERATED ON Thu Dec  6 14:15:22 2018 EST
-- BASED ON THE FILE: zcu102.xml
-- YOU *ARE* EXPECTED TO EDIT IT
-- This file initially contains the architecture skeleton for worker: zcu102

library IEEE; use IEEE.std_logic_1164.all; use ieee.numeric_std.all;
library ocpi; use ocpi.types.all; -- remove this to avoid all ocpi name collisions
library platform; use platform.platform_pkg.all;
library zynq_ultra; use zynq_ultra.zynq_ultra_pkg.all;
library axi; use axi.axi_pkg.all;
library unisim; use unisim.vcomponents.all;
library bsv;
library sdp; use sdp.sdp.all, sdp.sdp_axi.all;
architecture rtl of zcu102_worker is
  constant whichGP : natural := to_integer(unsigned(from_bool(useGP1)));
  signal ps_m_axi_hp_in  : m_axi_hp_in_array_t(0 to C_M_AXI_HP_COUNT-1);  -- s2m
  signal ps_m_axi_hp_out : m_axi_hp_out_array_t(0 to C_M_AXI_HP_COUNT-1); -- m2s

  signal ps_m_axi_gp_in  : m_axi_gp_in_array_t(0 to C_M_AXI_HP_COUNT-1);  -- s2m
  signal ps_m_axi_gp_out : m_axi_gp_out_array_t(0 to C_M_AXI_HP_COUNT-1); -- m2s

  signal ps_s_axi_hp_in  : s_axi_hp_in_array_t(0 to C_S_AXI_HP_COUNT-1);  -- m2s
  signal ps_s_axi_hp_out : s_axi_hp_out_array_t(0 to C_S_AXI_HP_COUNT-1); -- s2m
  signal fclk             : std_logic_vector(3 downto 0);
  signal clk              : std_logic;
  signal raw_rst_n     : std_logic;     -- FCLKRESET_Ns need synchronization
  signal rst_n         : std_logic;     -- the synchronized negative reset
  signal reset            : std_logic; -- our positive reset
  signal count         : unsigned(25 downto 0);
  signal my_zynq_ultra_out      : zynq_ultra_out_array_t;
  signal my_zynq_ultra_out_data : zynq_ultra_out_data_array_t;
  signal dbg_state        : ulonglong_array_t(0 to 3);
  signal dbg_state1       : ulonglong_array_t(0 to 3);
  signal dbg_state2       : ulonglong_array_t(0 to 3);
  signal dbg_state_r      : ulonglong_array_t(0 to 3);
  signal dbg_state1_r     : ulonglong_array_t(0 to 3);
  signal dbg_state2_r     : ulonglong_array_t(0 to 3);
  signal ledbuf           : std_logic_vector(2 downto 0) := (others => '0');
  signal cp_out_buf       : occp_in_t;

  signal cnt_t    : STD_LOGIC_VECTOR(31 DOWNTO 0) := x"0000_0000";
begin
  timebase_out.clk   <= clk;
  timebase_out.reset <= reset;
  timebase_out.ppsIn <= '0';

  led(3) <= cp_out_buf.data(0);
  cp_out <= cp_out_buf;
  led(4) <= reset;
  led(5) <= '0';
  led(6) <= '1';
  led(7) <= '1';

process (clk) is
begin
    if rising_edge(clk)  then
        if (reset ='1') then
          cnt_t <= x"0000_0000";
          ledbuf(0) <= '0';
          ledbuf(1) <= '0';
          ledbuf(2) <= '0';
        elsif (cnt_t = x"02FA_F080") then -- 0.5 second
            cnt_t <= std_logic_vector(unsigned(cnt_t) + 1);
            ledbuf(0) <= not ledbuf(0);
        elsif (cnt_t = x"05F5_E100") then --   1 second
            cnt_t <= std_logic_vector(unsigned(cnt_t) + 1);
            ledbuf(0) <= not ledbuf(0);
            ledbuf(1) <= not ledbuf(1);
        elsif (cnt_t = x"08F0_D180") then -- 1.5 second
            cnt_t <= std_logic_vector(unsigned(cnt_t) + 1);
            ledbuf(0) <= not ledbuf(0);
        elsif (cnt_t = x"0BEB_C200") then --   2 second
            cnt_t <= x"0000_0000";
            ledbuf(0) <= not ledbuf(0);
            ledbuf(1) <= not ledbuf(1);
            ledbuf(2) <= not ledbuf(2);
        else
            cnt_t <= std_logic_vector(unsigned(cnt_t) + 1);
        end if;
    end if;
end process;

  clkbuf : BUFG
    port map(
      I => fclk(0),
      O => clk);
  -- The FCLKRESET signals from the PS are documented as asynchronous with the
  -- associated FCLK for whatever reason.  Here we make a synchronized reset from it.
  sr : bsv.bsv.SyncResetA
    generic map(RSTDELAY => 17)
    port map(
      IN_RST  => raw_rst_n,
      CLK     => clk,
      OUT_RST => rst_n);
  reset <= not rst_n;
  -- Instantiate the processor system (i.e. the interface to it).
  ps : zynq_ultra_ps_e
    port map(
      -- Signals from the PS used in the PL
      ps_in.debug           => (31 => useGP1,
                                others => '0'),
      ps_out.FCLK           => fclk,
      ps_out.FCLKRESET_N    => raw_rst_n,
      m_axi_hp_in           => ps_m_axi_hp_in,
      m_axi_hp_out          => ps_m_axi_hp_out,
      s_axi_hp_in           => ps_s_axi_hp_in,
      s_axi_hp_out          => ps_s_axi_hp_out);

  -- Adapt the control plane's M_AXI_GP to ZynqMP's M_AXI_HP
  m : for i in 0 to C_M_AXI_HP_COUNT-1 generate
    g2h : m_axi_gp2hp
    port map(
      gp_in  => ps_m_axi_gp_in(i),
      gp_out => ps_m_axi_gp_out(i),
      hp_in  => ps_m_axi_hp_in(i),
      hp_out => ps_m_axi_hp_out(i));
  end generate;

  -- Adapt the axi master from the PS to be a CP Master
  cp : axi2cp
    port map(
      clk     => clk,
      reset   => reset,
      axi_in  => ps_m_axi_gp_out(whichGP),
      axi_out => ps_m_axi_gp_in(whichGP),
      cp_in   => cp_in,
      cp_out  => cp_out_buf);
  zynq_ultra_out               <= my_zynq_ultra_out;
  zynq_ultra_out_data          <= my_zynq_ultra_out_data;
  props_out.sdpDropCount <= zynq_ultra_in(0).dropCount;
  props_out.debug_state  <= dbg_state_r;
  props_out.debug_state1 <= dbg_state1_r;
  props_out.debug_state2 <= dbg_state2_r;
  g : for i in 0 to 3 generate
    dp : sdp2axi
      generic map(ocpi_debug => true,
                  sdp_width  => to_integer(sdp_width),
                  axi_width  => ps_s_axi_hp_in(0).W.DATA'length/dword_size)
      port map(   clk          => clk,
                  reset        => reset,
                  sdp_in       => zynq_ultra_in(i),
                  sdp_in_data  => zynq_ultra_in_data(i),
                  sdp_out      => my_zynq_ultra_out(i),
                  sdp_out_data => my_zynq_ultra_out_data(i),
                  axi_in       => ps_s_axi_hp_out(i),
                  axi_out      => ps_s_axi_hp_in(i),
                  axi_error    => props_out.axi_error(i),
                  dbg_state    => dbg_state(i),
                  dbg_state1   => dbg_state1(i),
                  dbg_state2   => dbg_state2(i));
  end generate;

  -- Output/readable properties
  props_out.dna             <= (others => '0');
  props_out.nSwitches       <= (others => '0');
  props_out.switches        <= (others => '0');
  props_out.memories_length <= to_ulong(1);
  props_out.memories        <= (others => to_ulong(0));
  props_out.nLEDs           <= to_ulong(0);  --led'length);
  props_out.UUID            <= metadata_in.UUID;
  props_out.romData         <= metadata_in.romData;
  metadata_out.clk          <= clk;
  metadata_out.romAddr      <= props_in.romAddr;
  metadata_out.romEn        <= props_in.romData_read;

  work : process(clk)
  begin
    if rising_edge(clk) then
      if reset = '0' then
        dbg_state_r <= dbg_state;
        dbg_state1_r <= dbg_state1;
        dbg_state2_r <= dbg_state2;
      end if;
    end if;
  end process;
end rtl;
