#include "bl.hpp"
#include <format>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace pybind11::literals;

PYBIND11_MODULE(pybl, m) {
	m.doc() = "Python bindings for the bl C++ library.";

	m.attr("major") = bl::major;
	m.attr("minor") = bl::minor;
	m.attr("patch") = bl::patch;

	m.attr("__version__")
		= std::format("{}.{}.{}", bl::major, bl::minor, bl::patch);

	pybind11::enum_<bl::block_name>(m, "block_name")
		.value("eErreur", bl::block_name::eErreur)
		.value("eAND_Gate", bl::block_name::eAND_Gate)
		.value("eNAND_Gate", bl::block_name::eNAND_Gate)
		.value("eNOR_Gate", bl::block_name::eNOR_Gate)
		.value("eNOT_Gate", bl::block_name::eNOT_Gate)
		.value("eOR_Gate", bl::block_name::eOR_Gate)
		.value("eSplitter", bl::block_name::eSplitter)
		.value("eXNOR_Gate", bl::block_name::eXNOR_Gate)
		.value("eXOR_Gate", bl::block_name::eXOR_Gate)
		.value("eCounter", bl::block_name::eCounter)
		.value("e8_Bit_Shifter_Counter",
			bl::block_name::e8_Bit_Shifter_Counter)
		.value("eNumber_Counter", bl::block_name::eNumber_Counter)
		.value("eColor_No_Light", bl::block_name::eColor_No_Light)
		.value("eGated_SR_Latch", bl::block_name::eGated_SR_Latch)
		.value("eFull_Adder", bl::block_name::eFull_Adder)
		.value("eSR_Latch", bl::block_name::eSR_Latch)
		.value("eToggle_Output", bl::block_name::eToggle_Output)
		.value("eDelay", bl::block_name::eDelay)
		.value("eTimer", bl::block_name::eTimer)
		.value("eRandomizer", bl::block_name::eRandomizer)
		.value("eWifi", bl::block_name::eWifi)
		.value("eButton", bl::block_name::eButton)
		.value("eSign", bl::block_name::eSign)
		.value("eLever", bl::block_name::eLever)
		.value("eToggle_Button", bl::block_name::eToggle_Button)
		.value("eInstant_Button", bl::block_name::eInstant_Button)
		.value("eHEX_Color_Display", bl::block_name::eHEX_Color_Display)
		.value("eHEX_Squared_Color_Display",
			bl::block_name::eHEX_Squared_Color_Display)
		.value("eHEX_LCD_Display", bl::block_name::eHEX_LCD_Display)
		.value("eHEX_Pixel_Color_Display",
			bl::block_name::eHEX_Pixel_Color_Display)
		.value("eBarrier", bl::block_name::eBarrier)
		.value("eRead_Output", bl::block_name::eRead_Output)
		.value("eColor_Neon_Light", bl::block_name::eColor_Neon_Light)
		.value("eColor_Light", bl::block_name::eColor_Light)
		.value("eRGB_Light", bl::block_name::eRGB_Light)
		.value("eBarrier_Block", bl::block_name::eBarrier_Block)
		.value("eInvisible_Block", bl::block_name::eInvisible_Block)
		.value("eTorchWATT_Down", bl::block_name::eTorchWATT_Down)
		.value("eSignWATT_Down", bl::block_name::eSignWATT_Down)
		.value("eSignWATT", bl::block_name::eSignWATT)
		.value("eTorchWATT", bl::block_name::eTorchWATT)
		.value("eDay_Controller", bl::block_name::eDay_Controller)
		.value(
			"e_Legacy_Kill_Module", bl::block_name::e_Legacy_Kill_Module
		)
		.value("eBlock", bl::block_name::eBlock)
		.value("eStair", bl::block_name::eStair)
		.value("eLadder", bl::block_name::eLadder)
		.value("eTorch", bl::block_name::eTorch)
		.value("eGreen_Screen", bl::block_name::eGreen_Screen)
		.value("eSlab", bl::block_name::eSlab)
		.value("eInner_Stair", bl::block_name::eInner_Stair)
		.value("eOuter_Stair", bl::block_name::eOuter_Stair)
		.value("eColor_Neon_Light_2",
			bl::block_name::eColor_Neon_Light_2)
		.value("eFull_Subtractor", bl::block_name::eFull_Subtractor)
		.value("ePlate", bl::block_name::ePlate)
		.value("ePiston", bl::block_name::ePiston)
		.value("e4_Bit_Register", bl::block_name::e4_Bit_Register)
		.value("eDip_Switches", bl::block_name::eDip_Switches)
		.value("e8x8_RGB2_Panel", bl::block_name::e8x8_RGB2_Panel)
		.value("eInterval_Calculator",
			bl::block_name::eInterval_Calculator)
		.value("e8_Bit_Splitter", bl::block_name::e8_Bit_Splitter)
		.value("eEEPROM", bl::block_name::eEEPROM)
		.value("eLED", bl::block_name::eLED)
		.value("e8_Bit_AND_Gate", bl::block_name::e8_Bit_AND_Gate)
		.value("e8_Bit_NOR_Gate", bl::block_name::e8_Bit_NOR_Gate)
		.value("e8_Bit_OR_Gate", bl::block_name::e8_Bit_OR_Gate)
		.value("e8_Bit_XOR_Gate", bl::block_name::e8_Bit_XOR_Gate)
		.value("e8_Bit_NAND_Gate", bl::block_name::e8_Bit_NAND_Gate)
		.value("e8_Bit_XNOR_Gate", bl::block_name::e8_Bit_XNOR_Gate)
		.value("eText_Button", bl::block_name::eText_Button)
		.value("eCommand_Block", bl::block_name::eCommand_Block)
		.value("e4_Bit_Shifter_Counter",
			bl::block_name::e4_Bit_Shifter_Counter)
		.value("eChair", bl::block_name::eChair)
		.value(
			"eHEX_Color_Display_2", bl::block_name::eHEX_Color_Display_2
		)
		.value("eText_Panel", bl::block_name::eText_Panel)
		.value("e2_Bit_Multiplier", bl::block_name::e2_Bit_Multiplier)
		.value("eDoor", bl::block_name::eDoor)
		.value("eElectric_Door", bl::block_name::eElectric_Door)
		.value("eSticky_Piston", bl::block_name::eSticky_Piston)
		.value("eTNT", bl::block_name::eTNT)
		.value("eEmpty_Block", bl::block_name::eEmpty_Block)
		.value("eRGB2_Light", bl::block_name::eRGB2_Light)
		.value("eCorner_Pane", bl::block_name::eCorner_Pane)
		.value("ePane", bl::block_name::ePane)
		.value("eRGB2_Light_Panel", bl::block_name::eRGB2_Light_Panel)
		.value("eBlock_Placer", bl::block_name::eBlock_Placer)
		.value("e8_Bit_Buffer", bl::block_name::e8_Bit_Buffer)
		.value("e4_Sides_Pole", bl::block_name::e4_Sides_Pole)
		.value("e5_Sides_Pole", bl::block_name::e5_Sides_Pole)
		.value("e6_Sides_Pole", bl::block_name::e6_Sides_Pole)
		.value("e4_LEDs", bl::block_name::e4_LEDs)
		.value("eTNT_Activator", bl::block_name::eTNT_Activator)
		.value("e4_Bit_Comparator", bl::block_name::e4_Bit_Comparator)
		.value("e8_Bit_Register", bl::block_name::e8_Bit_Register)
		.value("e16x16_RGB2_Panel", bl::block_name::e16x16_RGB2_Panel)
		.value(
			"e4_RGB_Lights_Panels", bl::block_name::e4_RGB_Lights_Panels
		)
		.value("eD_Flip_Flop", bl::block_name::eD_Flip_Flop)
		.value("eBeam_1x4", bl::block_name::eBeam_1x4)
		.value("eBeam_1x7", bl::block_name::eBeam_1x7)
		.value("e16_Bit_EEPROM", bl::block_name::e16_Bit_EEPROM)
		.value("eDouble_Dabble_Chip",
			bl::block_name::eDouble_Dabble_Chip)
		.value("eLaser", bl::block_name::eLaser)
		.value("eLaser_Detector", bl::block_name::eLaser_Detector)
		.value("eTransmitter", bl::block_name::eTransmitter)
		.value("eD_Latch", bl::block_name::eD_Latch)
		.value("eT_Flip_Flop", bl::block_name::eT_Flip_Flop)
		.value("e4_Sides_Pole_2", bl::block_name::e4_Sides_Pole_2)
		.value("eColor_Light_Panel", bl::block_name::eColor_Light_Panel)
		.value("eCorner_Pole", bl::block_name::eCorner_Pole)
		.value("ePole", bl::block_name::ePole)
		.value("eT_Pole", bl::block_name::eT_Pole)
		.value("e3_Sides_Pole", bl::block_name::e3_Sides_Pole)
		.value("eRGB_Light_Panel", bl::block_name::eRGB_Light_Panel)
		.value("eBuzzer", bl::block_name::eBuzzer)
		.value("eSpawn", bl::block_name::eSpawn)
		.value("eEMERGENCY", bl::block_name::eEMERGENCY)
		.value("eSpeaker", bl::block_name::eSpeaker)
		.value("eTeleport_Module_A", bl::block_name::eTeleport_Module_A)
		.value("eTeleport_Module_B", bl::block_name::eTeleport_Module_B)
		.value("ePressure_Plate", bl::block_name::ePressure_Plate)
		.value("eDont_Press_Button", bl::block_name::eDont_Press_Button)
		.value("ePlate_Button", bl::block_name::ePlate_Button)
		.value("eControllable_Color_Display",
			bl::block_name::eControllable_Color_Display)
		.value("eLoaded_Gate", bl::block_name::eLoaded_Gate)
		.value("eLight_Button", bl::block_name::eLight_Button)
		.value("eComplex_Counter", bl::block_name::eComplex_Counter)
		.value("eNUCLEAR_TNT", bl::block_name::eNUCLEAR_TNT)
		.value("ePhosphor_Light", bl::block_name::ePhosphor_Light)
		.value("eTrap_Door", bl::block_name::eTrap_Door)
		.value("eElectric_Trap_Door",
			bl::block_name::eElectric_Trap_Door)
		.value("eRGB_Neon_Light", bl::block_name::eRGB_Neon_Light)
		.value("eRGB2_Neon_Light", bl::block_name::eRGB2_Neon_Light)
		.value("eInverted_Double_Dabble_Chip",
			bl::block_name::eInverted_Double_Dabble_Chip)
		.value("eTriangular_Stair", bl::block_name::eTriangular_Stair)
		.value("e_unknown_133_", bl::block_name::e_unknown_133_)
		.value("eSticky_Block", bl::block_name::eSticky_Block)
		.value("e8_Bit_Multiplier", bl::block_name::e8_Bit_Multiplier)
		.value("e16_Bit_Multiplier", bl::block_name::e16_Bit_Multiplier)
		.value("e8_Bit_Divider", bl::block_name::e8_Bit_Divider)
		.value("e16_Bit_Divider", bl::block_name::e16_Bit_Divider)
		.value("eObsidian", bl::block_name::eObsidian)
		.value("eAir_Block", bl::block_name::eAir_Block)
		.value("e_Legacy_Player_Detector",
			bl::block_name::e_Legacy_Player_Detector)
		.value("eQuick_NOT", bl::block_name::eQuick_NOT)
		.value("eReinforced_Block", bl::block_name::eReinforced_Block)
		.value("eClay_Block", bl::block_name::eClay_Block)
		.value("eColor_Detector", bl::block_name::eColor_Detector)
		.value("e8_Bit_Adder", bl::block_name::e8_Bit_Adder)
		.value("e16_Bit_Adder", bl::block_name::e16_Bit_Adder)
		.value("eD_Flip", bl::block_name::eD_Flip)
		.value("eMini_HEX_Color_Display",
			bl::block_name::eMini_HEX_Color_Display)
		.value("eHTTP_Transmitter", bl::block_name::eHTTP_Transmitter)
		.value("e_unknown_151_", bl::block_name::e_unknown_151_)
		.value("e_unknown_152_", bl::block_name::e_unknown_152_)
		.value("e_unknown_153_", bl::block_name::e_unknown_153_)
		.value("eStair_Chair", bl::block_name::eStair_Chair)
		.value("eSolid_Chair", bl::block_name::eSolid_Chair)
		.value("eSlab_Chair", bl::block_name::eSlab_Chair)
		.value("eFirework_Module", bl::block_name::eFirework_Module)
		.value("e_Legacy_Keypad", bl::block_name::e_Legacy_Keypad)
		.value("eKeypad", bl::block_name::eKeypad)
		.value("e16_Bit_Shifter_Counter",
			bl::block_name::e16_Bit_Shifter_Counter)
		.value("eIllegal_Piston", bl::block_name::eIllegal_Piston)
		.value(
			"eIllegal_Sticky_Piston", bl::block_name::eIllegal_Sticky_Piston
		)
		.value("e_unknown_163_", bl::block_name::e_unknown_163_)
		.value("e1_Bit_1_16_Demux", bl::block_name::e1_Bit_1_16_Demux)
		.value("e1_Bit_1_8_Demux", bl::block_name::e1_Bit_1_8_Demux)
		.value("e4_Bit_4_1_Mux", bl::block_name::e4_Bit_4_1_Mux)
		.value("e8_Bit_2_1_Mux", bl::block_name::e8_Bit_2_1_Mux)
		.value("e8_Bit_8_1_Mux", bl::block_name::e8_Bit_8_1_Mux)
		.value("e4_Bit_16_1_Mux", bl::block_name::e4_Bit_16_1_Mux)
		.value("e4_Bit_Wifi", bl::block_name::e4_Bit_Wifi)
		.value("ePerfect_TNT", bl::block_name::ePerfect_TNT)
		.value("ePlayer_Detector", bl::block_name::ePlayer_Detector)
		.value("eKill_Module", bl::block_name::eKill_Module)
		.value("e_unknown_174_", bl::block_name::e_unknown_174_)
		.value("eSign_1x2", bl::block_name::eSign_1x2)
		.value("eSign_1x2WATT", bl::block_name::eSign_1x2WATT)
		.value("eSign_1x2WATT_Down", bl::block_name::eSign_1x2WATT_Down)
		.value("eCake", bl::block_name::eCake)
		.value("eComplex_Number_Counter",
			bl::block_name::eComplex_Number_Counter)
		.value("e_unknown_180_", bl::block_name::e_unknown_180_)
		.value("e8_Bit_Randomizer", bl::block_name::e8_Bit_Randomizer)
		.value("ePrecise_Randomizer",
			bl::block_name::ePrecise_Randomizer)
		.value("e_unknown_183_", bl::block_name::e_unknown_183_)
		.value("eSlab_Spawn", bl::block_name::eSlab_Spawn)
		.value("eCheckpoint", bl::block_name::eCheckpoint)
		.value("eSlab_Checkpoint", bl::block_name::eSlab_Checkpoint)
		.value("eSpotlight", bl::block_name::eSpotlight)
		.value("e_unknown_188_", bl::block_name::e_unknown_188_)
		.value("e_unknown_189_", bl::block_name::e_unknown_189_)
		.value("e_unknown_190_", bl::block_name::e_unknown_190_)
		.value("e_unknown_191_", bl::block_name::e_unknown_191_)
		.value("e_unknown_192_", bl::block_name::e_unknown_192_)
		.value(
			"eRGB2_Phosphor_Light", bl::block_name::eRGB2_Phosphor_Light
		)
		.value("e8_Bit_Shift_Register",
			bl::block_name::e8_Bit_Shift_Register);

	pybind11::enum_<bl::material>(m, "material")
		.value("eDefault", bl::material::eDefault)
		.value("eGlass", bl::material::eGlass)
		.value("eDiamond_Plate", bl::material::eDiamond_Plate)
		.value("eFabric", bl::material::eFabric)
		.value("eGrass", bl::material::eGrass)
		.value("eIce", bl::material::eIce)
		.value("eSand", bl::material::eSand)
		.value("eWood", bl::material::eWood)
		.value("eWooden_Planks", bl::material::eWooden_Planks)
		.value("eFoil", bl::material::eFoil)
		.value("eMetal", bl::material::eMetal)
		.value("eBrick", bl::material::eBrick)
		.value("eConcrete", bl::material::eConcrete)
		.value("eCobblestone", bl::material::eCobblestone)
		.value("eMarble", bl::material::eMarble)
		.value("eGranite", bl::material::eGranite)
		.value("eSlate", bl::material::eSlate)
		.value("eCorroded_Metal", bl::material::eCorroded_Metal)
		.value("eForce_Field", bl::material::eForce_Field)
		.value("eAerogel", bl::material::eAerogel);

	pybind11::enum_<bl::delay_interval>(m, "delay_interval")
		.value("e0_01s", bl::delay_interval::e0_01s)
		.value("e0_05s", bl::delay_interval::e0_05s)
		.value("e0_1s", bl::delay_interval::e0_1s)
		.value("e0_2s", bl::delay_interval::e0_2s)
		.value("e0_5s", bl::delay_interval::e0_5s)
		.value("e1s", bl::delay_interval::e1s)
		.value("e5s", bl::delay_interval::e5s);

	pybind11::enum_<bl::timer_interval>(m, "timer_interval")
		.value("e0_05s", bl::timer_interval::e0_05s)
		.value("e0_1s", bl::timer_interval::e0_1s)
		.value("e0_2s", bl::timer_interval::e0_2s)
		.value("e0_5s", bl::timer_interval::e0_5s)
		.value("e1s", bl::timer_interval::e1s)
		.value("e2s", bl::timer_interval::e2s)
		.value("e5s", bl::timer_interval::e5s)
		.value("e10s", bl::timer_interval::e10s)
		.value("e30s", bl::timer_interval::e30s)
		.value("e60s", bl::timer_interval::e60s)
		.value("e120s", bl::timer_interval::e120s)
		.value("e300s", bl::timer_interval::e300s);

	pybind11::enum_<bl::detection_shape>(m, "detection_shape")
		.value("eSphere", bl::detection_shape::eSphere)
		.value("eBox", bl::detection_shape::eBox)
		.value("eCylinder", bl::detection_shape::eCylinder)
		.value("eWedge", bl::detection_shape::eWedge)
		.value("ePyramid", bl::detection_shape::ePyramid);

	pybind11::class_<bl::block_name_traits>(m, "block_name_traits")
		.def(pybind11::init<bl::block_name>())
		.def(pybind11::init<bl::block_name const&>())
		.def_readonly("name", &bl::block_name_traits::name)
		.def_readonly("encoded", &bl::block_name_traits::encoded)
		.def_readonly("id", &bl::block_name_traits::id)
		.def_readonly("component", &bl::block_name_traits::component);

	pybind11::class_<bl::material_traits>(m, "material_traits")
		.def(pybind11::init<bl::material>())
		.def(pybind11::init<bl::material_traits const&>())
		.def_readonly("name", &bl::material_traits::name)
		.def_readonly("encoded", &bl::material_traits::encoded);

	pybind11::class_<bl::delay_interval_traits>(m, "delay_interval_traits")
		.def(pybind11::init<bl::delay_interval>())
		.def(pybind11::init<bl::delay_interval_traits const&>())
		.def_readonly("name", &bl::delay_interval_traits::name)
		.def_readonly("encoded", &bl::delay_interval_traits::encoded);

	pybind11::class_<bl::timer_interval_traits>(m, "timer_interval_traits")
		.def(pybind11::init<bl::timer_interval>())
		.def(pybind11::init<bl::timer_interval_traits const&>())
		.def_readonly("name", &bl::timer_interval_traits::name)
		.def_readonly("encoded", &bl::timer_interval_traits::encoded);

	pybind11::class_<bl::detection_shape_traits>(
		m, "detection_shape_traits"
	)
		.def(pybind11::init<bl::detection_shape>())
		.def(pybind11::init<bl::detection_shape_traits const&>())
		.def_readonly("name", &bl::detection_shape_traits::name)
		.def_readonly("encoded", &bl::detection_shape_traits::encoded);

	pybind11::class_<bl::vec3>(m, "vec3")
		.def_readwrite("x", &bl::vec3::x)
		.def_readwrite("y", &bl::vec3::y)
		.def_readwrite("z", &bl::vec3::z)
		.def_readwrite("r", &bl::vec3::r)
		.def_readwrite("g", &bl::vec3::g)
		.def_readwrite("b", &bl::vec3::b)
		.def(pybind11::init())
		.def(pybind11::init<bl::vec3 const&>())
		.def(pybind11::init<std::uint8_t, std::uint8_t, std::uint8_t>())
		.def(pybind11::init<std::uint8_t>())
		.def(pybind11::init<std::array<char, 4>>())
		.def(pybind11::self < pybind11::self)
		.def(pybind11::self <= pybind11::self)
		.def(pybind11::self > pybind11::self)
		.def(pybind11::self >= pybind11::self)
		.def("encode", &bl::vec3::encode);

	pybind11::class_<bl::rotation>(m, "rotation")
		.def_readwrite("x", &bl::rotation::x)
		.def_readwrite("y", &bl::rotation::y)
		.def_readwrite("z", &bl::rotation::z)
		.def(pybind11::init())
		.def(pybind11::init<bl::rotation const&>())
		.def(pybind11::init<
			std::uint_least8_t, std::uint_least8_t,
			std::uint_least8_t
		>())
		.def(pybind11::init<char>())
		.def(pybind11::self < pybind11::self)
		.def(pybind11::self <= pybind11::self)
		.def(pybind11::self > pybind11::self)
		.def(pybind11::self >= pybind11::self)
		.def("encode", &bl::rotation::encode);

	pybind11::class_<bl::delay_cfg>(m, "delay_cfg")
		.def_readwrite("interval", &bl::delay_cfg::interval)
		.def(pybind11::init())
		.def(pybind11::init<bl::delay_cfg const&>())
		.def(pybind11::init<std::string_view>())
		.def("to_value", &bl::delay_cfg::to_value);

	pybind11::class_<bl::timer_cfg>(m, "timer_cfg")
		.def_readwrite("interval", &bl::timer_cfg::interval)
		.def(pybind11::init())
		.def(pybind11::init<bl::timer_cfg const&>())
		.def(pybind11::init<std::string_view>())
		.def("to_value", &bl::timer_cfg::to_value);

	pybind11::class_<bl::text_cfg>(m, "text_cfg")
		.def_readwrite("text", &bl::text_cfg::text)
		.def(pybind11::init())
		.def(pybind11::init<bl::text_cfg const&>())
		.def(pybind11::init<std::string_view>())
		.def("to_value", &bl::text_cfg::to_value);

	pybind11::class_<bl::legacy_kill_module_cfg>(
		m, "legacy_kill_module_cfg"
	)
		.def_readwrite(
			"show_range", &bl::legacy_kill_module_cfg::show_range
		)
		.def_readwrite("damage", &bl::legacy_kill_module_cfg::damage)
		.def_readwrite("range", &bl::legacy_kill_module_cfg::range)
		.def(pybind11::init())
		.def(pybind11::init<bl::legacy_kill_module_cfg const&>())
		.def(pybind11::init<std::string_view>())
		.def("to_value", &bl::legacy_kill_module_cfg::to_value);

	pybind11::class_<bl::dip_switches_cfg>(m, "dip_switches_cfg")
		.def_readwrite("val", &bl::dip_switches_cfg::val)
		.def(pybind11::init())
		.def(pybind11::init<bl::dip_switches_cfg const&>())
		.def(pybind11::init<std::string_view>())
		.def("to_value", &bl::dip_switches_cfg::to_value);

	pybind11::class_<bl::eeprom_cfg>(m, "eeprom_cfg")
		.def_readwrite("mem", &bl::eeprom_cfg::mem)
		.def(pybind11::init())
		.def(pybind11::init<bl::eeprom_cfg const&>())
		.def(pybind11::init<std::string_view>())
		.def("to_value", &bl::eeprom_cfg::to_value);

	pybind11::class_<bl::block_placer_cfg>(m, "block_placer_cfg")
		.def_readwrite("name", &bl::block_placer_cfg::name)
		.def_readwrite("rot", &bl::block_placer_cfg::rot)
		.def(pybind11::init())
		.def(pybind11::init<bl::block_placer_cfg const&>())
		.def(pybind11::init<std::string_view>())
		.def("to_value", &bl::block_placer_cfg::to_value);

	pybind11::class_<bl::tnt_activator_cfg>(m, "tnt_activator_cfg")
		.def_readwrite("show_range", &bl::tnt_activator_cfg::show_range)
		.def_readwrite("range", &bl::tnt_activator_cfg::range)
		.def(pybind11::init())
		.def(pybind11::init<bl::tnt_activator_cfg const&>())
		.def(pybind11::init<std::string_view>())
		.def("to_value", &bl::tnt_activator_cfg::to_value);

	pybind11::class_<bl::eeprom16_cfg>(m, "eeprom16_cfg")
		.def_readwrite("mem", &bl::eeprom16_cfg::mem)
		.def(pybind11::init())
		.def(pybind11::init<bl::eeprom16_cfg const&>())
		.def(pybind11::init<std::string_view>())
		.def("to_value", &bl::eeprom16_cfg::to_value);

	pybind11::class_<bl::speaker_cfg>(m, "speaker_cfg")
		.def_readwrite("looped", &bl::speaker_cfg::looped)
		.def_readwrite("sound_id", &bl::speaker_cfg::sound_id)
		.def_readwrite("vol", &bl::speaker_cfg::vol)
		.def_readwrite("pitch", &bl::speaker_cfg::pitch)
		.def(pybind11::init())
		.def(pybind11::init<bl::speaker_cfg const&>())
		.def(pybind11::init<std::string_view>())
		.def("to_value", &bl::speaker_cfg::to_value);

	pybind11::class_<bl::teleport_module_cfg>(m, "teleport_module_cfg")
		.def_readwrite(
			"show_range", &bl::teleport_module_cfg::show_range
		)
		.def_readwrite("tp_offset", &bl::teleport_module_cfg::tp_offset)
		.def_readwrite("range", &bl::teleport_module_cfg::range)
		.def(pybind11::init())
		.def(pybind11::init<bl::teleport_module_cfg const&>())
		.def(pybind11::init<std::string_view>())
		.def("to_value", &bl::teleport_module_cfg::to_value);

	pybind11::class_<bl::legacy_player_detector_cfg>(
		m, "legacy_player_detector_cfg"
	)
		.def_readwrite(
			"show_range",
			&bl::legacy_player_detector_cfg::show_range
		)
		.def_readwrite(
			"activation_perm",
			&bl::legacy_player_detector_cfg::activation_perm
		)
		.def_readwrite("range", &bl::legacy_player_detector_cfg::range)
		.def(pybind11::init())
		.def(pybind11::init<bl::legacy_player_detector_cfg const&>())
		.def(pybind11::init<std::string_view>())
		.def("to_value", &bl::legacy_player_detector_cfg::to_value);

	pybind11::class_<bl::http_transmitter_cfg>(m, "http_transmitter_cfg")
		.def_readwrite(
			"get_requests", &bl::http_transmitter_cfg::get_requests
		)
		.def_readwrite(
			"get_interval", &bl::http_transmitter_cfg::get_interval
		)
		.def_readwrite("headers", &bl::http_transmitter_cfg::headers)
		.def_readwrite("url", &bl::http_transmitter_cfg::url)
		.def(pybind11::init())
		.def(pybind11::init<bl::http_transmitter_cfg const&>())
		.def(pybind11::init<std::string_view>())
		.def("to_value", &bl::http_transmitter_cfg::to_value);

	pybind11::class_<bl::legacy_keypad_cfg>(m, "legacy_keypad_cfg")
		.def_readwrite(
			"unlock_on_enter_key",
			&bl::legacy_keypad_cfg::unlock_on_enter_key
		)
		.def_readwrite(
			"unlocked_time", &bl::legacy_keypad_cfg::unlocked_time
		)
		.def_readwrite(
			"code_digits", &bl::legacy_keypad_cfg::code_digits
		)
		.def_readwrite(
			"show_key_press", &bl::legacy_keypad_cfg::show_key_press
		)
		.def_readwrite(
			"button_hold_time",
			&bl::legacy_keypad_cfg::button_hold_time
		)
		.def(pybind11::init())
		.def(pybind11::init<bl::legacy_keypad_cfg const&>())
		.def(pybind11::init<std::string_view>())
		.def("to_value", &bl::legacy_keypad_cfg::to_value);

	pybind11::class_<bl::precise_randomizer_cfg>(
		m, "precise_randomizer_cfg"
	)
		.def_readwrite(
			"right_percentage",
			&bl::precise_randomizer_cfg::right_percentage
		)
		.def(pybind11::init())
		.def(pybind11::init<bl::precise_randomizer_cfg const&>())
		.def(pybind11::init<std::string_view>())
		.def("to_value", &bl::precise_randomizer_cfg::to_value);

	pybind11::class_<bl::buzzer_cfg>(m, "buzzer_cfg")
		.def_readwrite("pitch", &bl::buzzer_cfg::pitch)
		.def(pybind11::init())
		.def(pybind11::init<bl::buzzer_cfg const&>())
		.def(pybind11::init<std::string_view>())
		.def("to_value", &bl::buzzer_cfg::to_value);

	pybind11::class_<bl::cake_cfg>(m, "cake_cfg")
		.def_readwrite("val", &bl::cake_cfg::val)
		.def(pybind11::init())
		.def(pybind11::init<bl::cake_cfg const&>())
		.def(pybind11::init<std::string_view>())
		.def("to_value", &bl::cake_cfg::to_value);

	pybind11::class_<bl::kill_module_cfg>(m, "kill_module_cfg")
		.def_readwrite(
			"show_detection_boundaries",
			&bl::kill_module_cfg::show_detection_boundaries
		)
		.def_readwrite(
			"kill_when_touched",
			&bl::kill_module_cfg::kill_when_touched
		)
		.def_readwrite("damage", &bl::kill_module_cfg::damage)
		.def_readwrite(
			"detection_size", &bl::kill_module_cfg::detection_size
		)
		.def_readwrite(
			"detect_shape", &bl::kill_module_cfg::detect_shape
		)
		.def_readwrite(
			"shape_orientation",
			&bl::kill_module_cfg::shape_orientation
		)
		.def_readwrite(
			"shape_offset", &bl::kill_module_cfg::shape_offset
		)
		.def(pybind11::init())
		.def(pybind11::init<bl::kill_module_cfg const&>())
		.def(pybind11::init<std::string_view>())
		.def("to_value", &bl::kill_module_cfg::to_value);

	pybind11::class_<bl::player_detector_cfg>(m, "player_detector_cfg")
		.def_readwrite(
			"show_detection_boundaries",
			&bl::player_detector_cfg::show_detection_boundaries
		)
		.def_readwrite(
			"activation_sel",
			&bl::player_detector_cfg::activation_sel
		)
		.def_readwrite(
			"detection_size",
			&bl::player_detector_cfg::detection_size
		)
		.def_readwrite(
			"detect_shape", &bl::player_detector_cfg::detect_shape
		)
		.def_readwrite(
			"shape_orientation",
			&bl::player_detector_cfg::shape_orientation
		)
		.def_readwrite(
			"shape_offset", &bl::player_detector_cfg::shape_offset
		)
		.def(pybind11::init())
		.def(pybind11::init<bl::player_detector_cfg const&>())
		.def(pybind11::init<std::string_view>())
		.def("to_value", &bl::player_detector_cfg::to_value);

	pybind11::class_<bl::keypad_cfg>(m, "keypad_cfg")
		.def_readwrite(
			"unlock_on_enter_key",
			&bl::keypad_cfg::unlock_on_enter_key
		)
		.def_readwrite("unlocked_time", &bl::keypad_cfg::unlocked_time)
		.def_readwrite("code_digits", &bl::keypad_cfg::code_digits)
		.def_readwrite(
			"show_key_press", &bl::keypad_cfg::show_key_press
		)
		.def_readwrite(
			"button_hold_time", &bl::keypad_cfg::button_hold_time
		)
		.def(pybind11::init())
		.def(pybind11::init<bl::keypad_cfg const&>())
		.def(pybind11::init<std::string_view>())
		.def("to_value", &bl::keypad_cfg::to_value);

	pybind11::class_<bl::block>(m, "block")
		.def_readwrite("value", &bl::block::value)
		.def_readwrite("name", &bl::block::name)
		.def_readwrite("mat", &bl::block::mat)
		.def_readwrite("pos", &bl::block::pos)
		.def_readwrite("color", &bl::block::color)
		.def_readwrite("rot", &bl::block::rot)
		.def_readwrite("activated", &bl::block::activated)
		.def(pybind11::init())
		.def(pybind11::init<bl::block const&>())
		.def(pybind11::init<
			     std::string const&, bl::block_name, bl::material,
			     bl::vec3, bl::vec3, bl::rotation, bool
		     >(),
			"value"_a = "", "name"_a = bl::block_name(),
			"mat"_a = bl::material::eDefault, "pos"_a = bl::vec3(),
			"color"_a = bl::vec3(255), "rot"_a = bl::rotation(),
			"activated"_a = false);

	pybind11::class_<bl::unique_id>(m, "unique_id")
		.def(pybind11::init())
		.def(pybind11::init<bl::unique_id const&>())
		.def_static("create", &bl::unique_id::create)
		.def(pybind11::self < pybind11::self)
		.def(pybind11::self <= pybind11::self)
		.def(pybind11::self > pybind11::self)
		.def(pybind11::self >= pybind11::self);

	pybind11::class_<bl::block_wire>(m, "block_wire")
		.def_readwrite("from_blk", &bl::block_wire::from_blk)
		.def_readwrite("to_blk", &bl::block_wire::to_blk)
		.def_readwrite("from_con", &bl::block_wire::from_con)
		.def_readwrite("to_con", &bl::block_wire::to_con)
		.def(pybind11::init())
		.def(pybind11::init<bl::block_wire const&>())
		.def(pybind11::init<bl::unique_id, bl::unique_id, char, char>(),
			"from_blk"_a = bl::unique_id(),
			"to_blk"_a = bl::unique_id(), "from_con"_a = 0,
			"to_con"_a = 0);

	pybind11::class_<bl::emplacement>(m, "emplacement")
		.def_readwrite("blks", &bl::emplacement::blks)
		.def_readwrite("wires", &bl::emplacement::wires)
		.def(pybind11::init())
		.def(pybind11::init<bl::emplacement const&>())
		.def(pybind11::init<std::string_view>())
		.def("place",
			pybind11::overload_cast<bl::block const&>(&bl::
					emplacement::place))
		.def("connect",
			pybind11::overload_cast<bl::block_wire const&>(&bl::
					emplacement::connect))
		.def("remove", &bl::emplacement::remove)
		.def("disconnect", &bl::emplacement::disconnect)
		.def("clear", &bl::emplacement::clear)
		.def("save", &bl::emplacement::save);

	m.def("decode_block_name", &bl::decode_block_name);
	m.def("block_name_from_block_id", &bl::block_name_from_block_id);
	m.def("decode_material", &bl::decode_material);
	m.def("decode_delay_interval", &bl::decode_delay_interval);
	m.def("decode_timer_interval", &bl::decode_timer_interval);
	m.def("decode_detection_shape", &bl::decode_detection_shape);
	m.def("encode_world_id", &bl::encode_world_id);
	m.def("decode_world_id", &bl::decode_world_id);
	m.def("encode_units", &bl::encode_units);
	m.def("decode_units", &bl::decode_units);
	m.def("encode62", &bl::encode62);
	m.def("encode_bl64", &bl::encode_bl64);
	m.def("encode_bl71", &bl::encode_bl71);
	m.def("encode_bl75", &bl::encode_bl75);
	m.def("encode_bl82", &bl::encode_bl82);
	m.def("decode62", &bl::decode62);
	m.def("decode_bl64", &bl::decode_bl64);
	m.def("decode_bl71", &bl::decode_bl71);
	m.def("decode_bl75", &bl::decode_bl75);
	m.def("decode_bl82", &bl::decode_bl82);

	auto cake{m.def_submodule("cake")};
	cake.attr("e0") = bl::cake::e0;
	cake.attr("e1") = bl::cake::e1;
	cake.attr("e2") = bl::cake::e2;
	cake.attr("e3") = bl::cake::e3;
	cake.attr("e4") = bl::cake::e4;
	cake.attr("e5") = bl::cake::e5;
	cake.attr("e6") = bl::cake::e6;
	cake.attr("e7") = bl::cake::e7;

	auto con{m.def_submodule("con")};

	auto eAND_Gate{con.def_submodule("eAND_Gate")};
	eAND_Gate.attr("a") = bl::con::eAND_Gate::a;
	eAND_Gate.attr("b") = bl::con::eAND_Gate::b;
	eAND_Gate.attr("q") = bl::con::eAND_Gate::q;

	auto eNAND_Gate{con.def_submodule("eNAND_Gate")};
	eNAND_Gate.attr("a") = bl::con::eNAND_Gate::a;
	eNAND_Gate.attr("b") = bl::con::eNAND_Gate::b;
	eNAND_Gate.attr("q") = bl::con::eNAND_Gate::q;

	auto eNOR_Gate{con.def_submodule("eNOR_Gate")};
	eNOR_Gate.attr("a") = bl::con::eNOR_Gate::a;
	eNOR_Gate.attr("b") = bl::con::eNOR_Gate::b;
	eNOR_Gate.attr("q") = bl::con::eNOR_Gate::q;

	auto eNOT_Gate{con.def_submodule("eNOT_Gate")};
	eNOT_Gate.attr("a") = bl::con::eNOT_Gate::a;
	eNOT_Gate.attr("q") = bl::con::eNOT_Gate::q;

	auto eOR_Gate{con.def_submodule("eOR_Gate")};
	eOR_Gate.attr("a") = bl::con::eOR_Gate::a;
	eOR_Gate.attr("b") = bl::con::eOR_Gate::b;
	eOR_Gate.attr("q") = bl::con::eOR_Gate::q;

	auto eSplitter{con.def_submodule("eSplitter")};
	eSplitter.attr("a") = bl::con::eSplitter::a;
	eSplitter.attr("q") = bl::con::eSplitter::q;
	eSplitter.attr("r") = bl::con::eSplitter::r;

	auto eXNOR_Gate{con.def_submodule("eXNOR_Gate")};
	eXNOR_Gate.attr("a") = bl::con::eXNOR_Gate::a;
	eXNOR_Gate.attr("b") = bl::con::eXNOR_Gate::b;
	eXNOR_Gate.attr("q") = bl::con::eXNOR_Gate::q;

	auto eXOR_Gate{con.def_submodule("eXOR_Gate")};
	eXOR_Gate.attr("a") = bl::con::eXOR_Gate::a;
	eXOR_Gate.attr("b") = bl::con::eXOR_Gate::b;
	eXOR_Gate.attr("q") = bl::con::eXOR_Gate::q;

	auto eCounter{con.def_submodule("eCounter")};
	eCounter.attr("inc_out") = bl::con::eCounter::inc_out;
	eCounter.attr("dec_out") = bl::con::eCounter::dec_out;
	eCounter.attr("inc_in") = bl::con::eCounter::inc_in;
	eCounter.attr("dec_in") = bl::con::eCounter::dec_in;
	eCounter.attr("q0") = bl::con::eCounter::q0;
	eCounter.attr("q1") = bl::con::eCounter::q1;
	eCounter.attr("q2") = bl::con::eCounter::q2;
	eCounter.attr("q3") = bl::con::eCounter::q3;
	eCounter.attr("reset") = bl::con::eCounter::reset;

	auto e8_Bit_Shifter_Counter{
		con.def_submodule("e8_Bit_Shifter_Counter")
	};
	e8_Bit_Shifter_Counter.attr("left")
		= bl::con::e8_Bit_Shifter_Counter::left;
	e8_Bit_Shifter_Counter.attr("reset")
		= bl::con::e8_Bit_Shifter_Counter::reset;
	e8_Bit_Shifter_Counter.attr("output")
		= bl::con::e8_Bit_Shifter_Counter::output;
	e8_Bit_Shifter_Counter.attr("right")
		= bl::con::e8_Bit_Shifter_Counter::right;
	e8_Bit_Shifter_Counter.attr("q7") = bl::con::e8_Bit_Shifter_Counter::q7;
	e8_Bit_Shifter_Counter.attr("q6") = bl::con::e8_Bit_Shifter_Counter::q6;
	e8_Bit_Shifter_Counter.attr("q5") = bl::con::e8_Bit_Shifter_Counter::q5;
	e8_Bit_Shifter_Counter.attr("q4") = bl::con::e8_Bit_Shifter_Counter::q4;
	e8_Bit_Shifter_Counter.attr("q3") = bl::con::e8_Bit_Shifter_Counter::q3;
	e8_Bit_Shifter_Counter.attr("q2") = bl::con::e8_Bit_Shifter_Counter::q2;
	e8_Bit_Shifter_Counter.attr("q1") = bl::con::e8_Bit_Shifter_Counter::q1;
	e8_Bit_Shifter_Counter.attr("q0") = bl::con::e8_Bit_Shifter_Counter::q0;
}
