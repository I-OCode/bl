#pragma once

#include <cstdint>
#include <map>
#include <span>
#include <string>

/// @brief
///   The main namespace for the bl library. For a thorough explanation of how
///   Build Logic's savestring format works, see the `DOCS.md` file.
namespace bl {
	// See https://semver.org/

	inline constexpr unsigned major{0};
	inline constexpr unsigned minor{6};
	inline constexpr unsigned patch{0};

	/// @brief
	///   Namespace dedicated to connectors, for convenience. This way you
	///   can type `bl::con::eAND_Gate::A` instead of `'1'`.
	namespace con {};

	/// @brief Types of blocks.
	enum class block_type {
		// Fun fact about why these enum names begin with `e`:
		//
		// Things like "_Legacy Keypad" can't just have the enum name
		// `_Legacy_Keypad` because any identifier beginning with an
		// underscore followed by an uppercase letter is ill-formed
		// according to the C++ standard. So I had to put *some* letter
		// before the underscore. And that letter was `e`. Just like the
		// Vulkan-Hpp enum naming style.

		eErreur,		      ///< Erreur
		eAND_Gate,		      ///< AND Gate
		eNAND_Gate,		      ///< NAND Gate
		eNOR_Gate,		      ///< NOR Gate
		eNOT_Gate,		      ///< NOT Gate
		eOR_Gate,		      ///< OR Gate
		eSplitter,		      ///< Splitter
		eXNOR_Gate,		      ///< XNOR Gate
		eXOR_Gate,		      ///< XOR Gate
		eCounter,		      ///< Counter
		e8_Bit_Shifter_Counter,	      ///< 8 Bit Shifter Counter
		eNumber_Counter,	      ///< Number Counter
		eColor_No_Light,	      ///< Color No Light
		eGated_SR_Latch,	      ///< Gated SR Latch
		eFull_Adder,		      ///< Full Adder
		eSR_Latch,		      ///< SR Latch
		eToggle_Output,		      ///< Toggle Output
		eDelay,			      ///< Delay
		eTimer,			      ///< Timer
		eRandomizer,		      ///< Randomizer
		eWifi,			      ///< Wifi
		eButton,		      ///< Button
		eSign,			      ///< Sign
		eLever,			      ///< Lever
		eToggle_Button,		      ///< Toggle Button
		eInstant_Button,	      ///< Instant Button
		eHEX_Color_Display,	      ///< HEX Color Display
		eHEX_Squared_Color_Display,   ///< HEX Squared Color Display
		eHEX_LCD_Display,	      ///< HEX LCD Display
		eHEX_Pixel_Color_Display,     ///< HEX Pixel Color Display
		eBarrier,		      ///< Barrier
		eRead_Output,		      ///< Read Output
		eColor_Neon_Light,	      ///< Color Neon Light
		eColor_Light,		      ///< Color Light
		eRGB_Light,		      ///< RGB Light
		eBarrier_Block,		      ///< Barrier Block
		eInvisible_Block,	      ///< Invisible Block
		eTorchWATT_Down,	      ///< TorchWATT_Down
		eSignWATT_Down,		      ///< SignWATT_Down
		eSignWATT,		      ///< SignWATT
		eTorchWATT,		      ///< TorchWATT
		eDay_Controller,	      ///< Day Controller
		e_Legacy_Kill_Module,	      ///< _Legacy Kill Module
		eBlock,			      ///< Block
		eStair,			      ///< Stair
		eLadder,		      ///< Ladder
		eTorch,			      ///< Torch
		eGreen_Screen,		      ///< Green Screen
		eSlab,			      ///< Slab
		eInner_Stair,		      ///< Inner Stair
		eOuter_Stair,		      ///< Outer Stair
		eColor_Neon_Light_2,	      ///< Color Neon Light 2
		eFull_Subtractor,	      ///< Full Subtractor
		ePlate,			      ///< Plate
		ePiston,		      ///< Piston
		e4_Bit_Register,	      ///< 4 Bit Register
		eDip_Switches,		      ///< Dip Switches
		e8x8_RGB2_Panel,	      ///< 8x8 RGB2 Panel
		eInterval_Calculator,	      ///< Interval Calculator
		e8_Bit_Splitter,	      ///< 8 Bit Splitter
		eEEPROM,		      ///< EEPROM
		eLED,			      ///< LED
		e8_Bit_AND_Gate,	      ///< 8 Bit AND Gate
		e8_Bit_NOR_Gate,	      ///< 8 Bit NOR Gate
		e8_Bit_OR_Gate,		      ///< 8 Bit OR Gate
		e8_Bit_XOR_Gate,	      ///< 8 Bit XOR Gate
		e8_Bit_NAND_Gate,	      ///< 8 Bit NAND Gate
		e8_Bit_XNOR_Gate,	      ///< 8 Bit XNOR Gate
		eText_Button,		      ///< Text Button
		eCommand_Block,		      ///< Command Block
		e4_Bit_Shifter_Counter,	      ///< 4 Bit Shifter Counter
		eChair,			      ///< Chair
		eHEX_Color_Display_2,	      ///< HEX Color Display 2
		eText_Panel,		      ///< Text Panel
		e2_Bit_Multiplier,	      ///< 2 Bit Multiplier
		eDoor,			      ///< Door
		eElectric_Door,		      ///< Electric Door
		eSticky_Piston,		      ///< Sticky Piston
		eTNT,			      ///< TNT
		eEmpty_Block,		      ///< Empty Block
		eRGB2_Light,		      ///< RGB2 Light
		eCorner_Pane,		      ///< Corner Pane
		ePane,			      ///< Pane
		eRGB2_Light_Panel,	      ///< RGB2 Light Panel
		eBlock_Placer,		      ///< Block Placer
		e8_Bit_Buffer,		      ///< 8 Bit Buffer
		e4_Sides_Pole,		      ///< 4 Sides Pole
		e5_Sides_Pole,		      ///< 5 Sides Pole
		e6_Sides_Pole,		      ///< 6 Sides Pole
		e4_LEDs,		      ///< 4 LEDs
		eTNT_Activator,		      ///< TNT Activator
		e4_Bit_Comparator,	      ///< 4 Bit Comparator
		e8_Bit_Register,	      ///< 8 Bit Register
		e16x16_RGB2_Panel,	      ///< 16x16 RGB2 Panel
		e4_RGB_Lights_Panels,	      ///< 4 RGB Lights Panels
		eD_Flip_Flop,		      ///< D Flip Flop
		eBeam_1x4,		      ///< Beam 1x4
		eBeam_1x7,		      ///< Beam 1x7
		e16_Bit_EEPROM,		      ///< 16 Bit EEPROM
		eDouble_Dabble_Chip,	      ///< Double Dabble Chip
		eLaser,			      ///< Laser
		eLaser_Detector,	      ///< Laser Detector
		eTransmitter,		      ///< Transmitter
		eD_Latch,		      ///< D Latch
		eT_Flip_Flop,		      ///< T Flip Flop
		e4_Sides_Pole_2,	      ///< 4 Sides Pole 2
		eColor_Light_Panel,	      ///< Color Light Panel
		eCorner_Pole,		      ///< Corner Pole
		ePole,			      ///< Pole
		eT_Pole,		      ///< T Pole
		e3_Sides_Pole,		      ///< 3 Sides Pole
		eRGB_Light_Panel,	      ///< RGB Light Panel
		eBuzzer,		      ///< Buzzer
		eSpawn,			      ///< Spawn
		eEMERGENCY,		      ///< EMERGENCY
		eSpeaker,		      ///< Speaker
		eTeleport_Module_A,	      ///< Teleport Module A
		eTeleport_Module_B,	      ///< Teleport Module B
		ePressure_Plate,	      ///< Pressure Plate
		eDont_Press_Button,	      ///< Don't Press Button
		ePlate_Button,		      ///< Plate Button
		eControllable_Color_Display,  ///< Controllable Color Display
		eLoaded_Gate,		      ///< Loaded Gate
		eLight_Button,		      ///< Light Button
		eComplex_Counter,	      ///< Complex Counter
		eNUCLEAR_TNT,		      ///< NUCLEAR TNT
		ePhosphor_Light,	      ///< Phosphor Light
		eTrap_Door,		      ///< Trap Door
		eElectric_Trap_Door,	      ///< Electric Trap Door
		eRGB_Neon_Light,	      ///< RGB Neon Light
		eRGB2_Neon_Light,	      ///< RGB2 Neon Light
		eInverted_Double_Dabble_Chip, ///< Inverted Double Dabble Chip
		eTriangular_Stair,	      ///< Triangular Stair
		e_unknown_133_,
		eSticky_Block,		  ///< Sticky Block
		e8_Bit_Multiplier,	  ///< 8 Bit Multiplier
		e16_Bit_Multiplier,	  ///< 16 Bit Multiplier
		e8_Bit_Divider,		  ///< 8 Bit Divider
		e16_Bit_Divider,	  ///< 16 Bit Divider
		eObsidian,		  ///< Obsidian
		eAir_Block,		  ///< Air Block
		e_Legacy_Player_Detector, ///< _Legacy Player Detector
		eQuick_NOT,		  ///< Quick NOT
		eReinforced_Block,	  ///< Reinforced Block
		eClay_Block,		  ///< Clay Block
		eColor_Detector,	  ///< Color Detector
		e8_Bit_Adder,		  ///< 8 Bit Adder
		e16_Bit_Adder,		  ///< 16 Bit Adder
		eD_Flip,		  ///< D Flip
		eMini_HEX_Color_Display,  ///< Mini HEX Color Display
		eHTTP_Transmitter,	  ///< HTTP Transmitter
		e_unknown_151_,
		e_unknown_152_,
		e_unknown_153_,
		eStair_Chair,		 ///< Stair Chair
		eSolid_Chair,		 ///< Solid Chair
		eSlab_Chair,		 ///< Slab Chair
		eFirework_Module,	 ///< Firework Module
		e_Legacy_Keypad,	 ///< _Legacy Keypad
		eKeypad,		 ///< Keypad
		e16_Bit_Shifter_Counter, ///< 16 Bit Shifter Counter
		eIllegal_Piston,	 ///< Illegal Piston
		eIllegal_Sticky_Piston,	 ///< Illegal Sticky Piston
		e_unknown_163_,
		e1_Bit_1_16_Demux, ///< 1 Bit 1:16 Demux
		e1_Bit_1_8_Demux,  ///< 1 Bit 1:8 Demux
		e4_Bit_4_1_Mux,	   ///< 4 Bit 4:1 Mux
		e8_Bit_2_1_Mux,	   ///< 8 Bit 2:1 Mux
		e8_Bit_8_1_Mux,	   ///< 8 Bit 8:1 Mux
		e4_Bit_16_1_Mux,   ///< 4 Bit 16:1 Mux
		e4_Bit_Wifi,	   ///< 4 Bit Wifi
		ePerfect_TNT,	   ///< Perfect TNT
		ePlayer_Detector,  ///< Player Detector
		eKill_Module,	   ///< Kill Module
		e_unknown_174_,
		eSign_1x2,		 ///< Sign 1x2
		eSign_1x2WATT,		 ///< Sign 1x2WATT
		eSign_1x2WATT_Down,	 ///< Sign 1x2WATT_Down
		eCake,			 ///< Cake
		eComplex_Number_Counter, ///< Complex Number Counter
		e_unknown_180_,
		e8_Bit_Randomizer,   ///< 8 Bit Randomizer
		ePrecise_Randomizer, ///< Precise Randomizer
		e_unknown_183_,
		eSlab_Spawn,	  ///< Slab Spawn
		eCheckpoint,	  ///< Checkpoint
		eSlab_Checkpoint, ///< Slab Checkpoint
		eSpotlight,	  ///< Spotlight
		e_unknown_188_,
		e_unknown_189_,
		e_unknown_190_,
		e_unknown_191_,
		e_unknown_192_,
		eRGB2_Phosphor_Light, ///< RGB2 Phosphor Light
		e8_Bit_Shift_Register ///< 8 Bit Shift Register
	};

	/// @brief Block materials.
	/// @note
	///   `eCobblestone` and `eAerogel` aren't listed in the game's material
	///   selector, so I had to improvise the names myself. A material named
	///   "Cobblestone" does exist in the world baseplate material selector
	///   though, so I guess the improvisation worked out for that at least.
	enum class material {
		eDefault,	 ///< Default
		eGlass,		 ///< Glass
		eDiamond_Plate,	 ///< Diamond Plate
		eFabric,	 ///< Fabric
		eGrass,		 ///< Grass
		eIce,		 ///< Ice
		eSand,		 ///< Sand
		eWood,		 ///< Wood
		eWooden_Planks,	 ///< Wooden Planks
		eFoil,		 ///< Foil
		eMetal,		 ///< Metal
		eBrick,		 ///< Brick
		eConcrete,	 ///< Concrete
		eCobblestone,	 ///< Cobblestone
		eMarble,	 ///< Marble
		eGranite,	 ///< Granite
		eSlate,		 ///< Slate
		eCorroded_Metal, ///< Corroded Metal
		eForce_Field,	 ///< Force Field
		eAerogel	 ///< Aerogel
	};

	/// @brief Configurations of the `Delay` block.
	enum class delay_interval {
		e0_01s, ///< 0.01s
		e0_05s, ///< 0.05s
		e0_1s,	///< 0.1s
		e0_2s,	///< 0.2s
		e0_5s,	///< 0.5s
		e1s,	///< 1s
		e5s	///< 5s
	};

	/// @brief Configurations of the `Timer` block.
	enum class timer_interval {
		e0_05s, ///< 0.05s
		e0_1s,	///< 0.1s
		e0_2s,	///< 0.2s
		e0_5s,	///< 0.5s
		e1s,	///< 1s
		e2s,	///< 2s
		e5s,	///< 5s
		e10s,	///< 10s
		e30s,	///< 30s
		e60s,	///< 60s
		e120s,	///< 120s
		e300s	///< 300s
	};

	/// @brief Detection shape for `Kill Module`s and `Player Detector`s.
	enum class detection_shape {
		eSphere,   ///< Sphere
		eBox,	   ///< Box
		eCylinder, ///< Cylinder
		eWedge,	   ///< Wedge
		ePyramid   ///< Pyramid
	};

	/// @brief
	///   Some constant properties and info that is associated with
	///   every block type. You can query these traits for a particular
	///   block type using `get_block_traits()`.
	class block_type_traits {
	public:
		std::string_view name{};    ///< The full in-game name of the
					    ///< block.
		std::string_view encoded{}; ///< The encoded version of the
					    ///< block.
		std::size_t id{};	    ///< Block ID.
		bool component{}; ///< `true` if the block is a component,
				  ///< `false` otherwise.
	};

	/// @brief
	///   Some constant properties and info that is associated with
	///   every material. You can query these traits for a particular
	///   material using `get_material_traits()`.
	class material_traits {
	public:
		std::string_view name{}; ///< The name of the material.
		char encoded{};		 ///< The encoded version of the
					 ///< material.
	};

	/// @brief
	///   Some constant properties and info that is associated with
	///   every delay interval. You can query these traits for a particular
	///   delay interval using `get_delay_interval_traits()`.
	class delay_interval_traits {
	public:
		std::string_view name{};
		char encoded{};
	};

	/// @brief
	///   Some constant properties and info that is associated with
	///   every timer interval. You can query these traits for a particular
	///   timer interval using `get_timer_interval_traits()`.
	class timer_interval_traits {
	public:
		std::string_view name{};
		char encoded{};
	};

	/// @brief
	///   Some constant properties and info that is associated with
	///   every detection shape. You can query these traits for a particular
	///   detection shape using `get_detection_shape_traits()`.
	class detection_shape_traits {
	public:
		std::string_view name{};
		std::size_t encoded{};
	};

	/// @brief
	///   Represents a 3D position in the Build Logic world or a R8G8B8
	///   color. The Build Logic world is 256x256x256, by the way.
	class vec3 {
	public:
		union {
			std::uint8_t x{}; ///< X-axis.
			std::uint8_t r;	  ///< Red.
		};

		union {
			std::uint8_t y{}; ///< Y-axis.
			std::uint8_t g;	  ///< Green.
		};

		union {
			std::uint8_t z{}; ///< Z-axis.
			std::uint8_t b;	  ///< Blue.
		};

		vec3() noexcept = default;

		/// @brief Constructor.
		/// @param[in] a First component.
		/// @param[in] b Second component.
		/// @param[in] c Third component.
		vec3(std::uint8_t a, std::uint8_t b, std::uint8_t c) noexcept:
			x{a}, y{b}, z{c} {}

		/// @brief
		///   Shorthand constructor for filling the entire vector to a
		///   single value.
		/// @param[in] v The value.
		vec3(std::uint8_t v) noexcept: vec3(v, v, v) {}

		/// @brief
		///   Constructor to create the vector from an encoded
		///   position/color.
		/// @param[in] v The encoded value.
		vec3(std::span<char const, 4> v);

		bool operator==(vec3 const& v) const noexcept {
			return this->x == v.x
				&& this->y == v.y
				&& this->z == v.z;
		}

		auto operator<=>(vec3 const& v) const noexcept {
			return std::tie(this->x, this->y, this->z)
				<=> std::tie(v.x, v.y, v.z);
		}

		std::array<char, 4> encode() const;
	};

	/// @brief The rotation of a block, measured in right angles.
	class rotation {
	public:
		std::uint_least8_t x{}; ///< X-axis. Each unit is worth 90
					///< degrees.
		std::uint_least8_t y{}; ///< Y-axis. Each unit is worth 90
					///< degrees.
		std::uint_least8_t z{}; ///< Z-axis. Each unit is worth 90
					///< degrees.

		rotation() noexcept = default;

		/// @brief Constructor.
		/// @param[in] a First component.
		/// @param[in] b Second component.
		/// @param[in] c Third component.
		rotation(
			std::uint_least8_t a, std::uint_least8_t b,
			std::uint_least8_t c
		) noexcept: x{a}, y{b}, z{c} {}

		/// @brief Construct the rotation from an encoded rotation.
		/// @param[in] v The encoded value to decode.
		rotation(char v);

		auto operator<=>(rotation const&) const noexcept = default;

		char encode() const;
	};

	/// @brief Configuration for `Delay`s.
	class delay_cfg {
	public:
		delay_interval interval{delay_interval::e0_1s}; ///< Interval.

		delay_cfg() noexcept = default;

		/// @brief Construct from a value.
		/// @param[in] v A value.
		delay_cfg(std::string_view v);

		/// @brief Convert the configuration to a value.
		/// @returns The stringified configuration.
		std::string to_value() const;
	};

	/// @brief Configuration for `Timer`s.
	class timer_cfg {
	public:
		timer_interval interval{timer_interval::e1s}; ///< Interval.

		timer_cfg() noexcept = default;

		/// @brief Construct from a value.
		/// @param[in] v A value.
		timer_cfg(std::string_view v);

		/// @brief Convert the configuration to a value.
		/// @returns The stringified configuration.
		std::string to_value() const;
	};

	/// @brief Configuration for `Sign`s, `SignWATT_Down`s,
	///        `SignWATT`s, and `Text Button`s.
	class text_cfg {
	public:
		std::string text{}; ///< Text.

		text_cfg() = default;

		/// @brief Convert the configuration to a value.
		/// @returns The stringified configuration.
		std::string to_value() const;
	};

	/// @brief Configuration for `_Legacy Kill Module`s.
	class legacy_kill_module_cfg {
	public:
		bool show_range{};   ///< Show Range
		double damage{25};   ///< Damages
		double range{13.33}; ///< Range

		legacy_kill_module_cfg() noexcept = default;

		/// @brief Construct from a value.
		/// @param[in] v A value.
		legacy_kill_module_cfg(std::string_view v);

		/// @brief Convert the configuration to a value.
		/// @returns The stringified configuration.
		std::string to_value() const;
	};

	/// @brief Configuration for `Dip Switches`.
	class dip_switches_cfg {
	public:
		std::uint_least8_t val{0};

		dip_switches_cfg() noexcept = default;

		/// @brief Construct from a value.
		/// @param[in] v A value.
		dip_switches_cfg(std::string_view v);

		/// @brief Convert the configuration to a value.
		/// @returns The stringified configuration.
		std::string to_value() const;
	};

	/// @brief Configuration for `EEPROM`s.
	class eeprom_cfg {
	public:
		std::map<std::uint8_t, std::uint8_t> mem{};

		eeprom_cfg() = default;

		/// @brief Construct from a value.
		/// @param[in] v A value.
		eeprom_cfg(std::string_view v);

		/// @brief Convert the configuration to a value.
		/// @returns The stringified configuration.
		std::string to_value() const;
	};

	/// @brief Configuration for `Block Placer`s.
	class block_placer_cfg {
	public:
		block_type type{block_type::eBlock}; ///< Block type.
		rotation rot{};			     ///< Rotation.

		block_placer_cfg() noexcept = default;

		/// @brief Construct from a value.
		/// @param[in] v A value.
		block_placer_cfg(std::string_view v);

		/// @brief Convert the configuration to a value.
		/// @returns The stringified configuration.
		std::string to_value() const;
	};

	/// @brief Configuration for `TNT Activator`s.
	class tnt_activator_cfg {
	public:
		bool show_range{};  ///< Show Range
		double range{3.33}; ///< Range

		tnt_activator_cfg() noexcept = default;

		/// @brief Construct from a value.
		/// @param[in] v A value.
		tnt_activator_cfg(std::string_view v);

		/// @brief Convert the configuration to a value.
		/// @returns The stringified configuration.
		std::string to_value() const;
	};

	/// @brief Configuration for `16 Bit EEPROM`s.
	class eeprom16_cfg {
	public:
		std::map<std::uint16_t, std::uint16_t> mem{};

		eeprom16_cfg() = default;

		/// @brief Construct from a value.
		/// @param[in] v A value.
		eeprom16_cfg(std::string_view v);

		/// @brief Convert the configuration to a value.
		/// @returns The stringified configuration.
		std::string to_value() const;
	};

	/// @brief Configuration for `Speaker`s.
	class speaker_cfg {
	public:
		bool looped{true};			 ///< Looped
		std::uint_least64_t sound_id{542343755}; ///< Sound Id
		double vol{0.5};			 ///< Volume
		double pitch{1.0};			 ///< Pitch

		speaker_cfg() noexcept = default;

		/// @brief Construct from a value.
		/// @param[in] v A value.
		speaker_cfg(std::string_view v);

		/// @brief Convert the configuration to a value.
		/// @returns The stringified configuration.
		std::string to_value() const;
	};

	/// @brief Configuration for `Teleport Module A`s and
	///        `Teleport Module B`s.
	class teleport_module_cfg {
	public:
		bool show_range{false};		   ///< Show Range
		std::array<double, 3> tp_offset{}; ///< TP Offset
		double range{13.33};		   ///< Range

		teleport_module_cfg() noexcept = default;

		/// @brief Construct from a value.
		/// @param[in] v A value.
		teleport_module_cfg(std::string_view v);

		/// @brief Convert the configuration to a value.
		/// @returns The stringified configuration.
		std::string to_value() const;
	};

	/// @brief Configuration for `_Legacy Player Detector`s.
	class legacy_player_detector_cfg {
	public:
		bool show_range{};		///< Show Range
		std::size_t activation_perm{2}; ///< Activation Permission
		double range{13.33};		///< Range

		legacy_player_detector_cfg() noexcept = default;

		/// @brief Construct from a value.
		/// @param[in] v A value.
		legacy_player_detector_cfg(std::string_view v);

		/// @brief Convert the configuration to a value.
		/// @returns The stringified configuration.
		std::string to_value() const;
	};

	/// @brief Configuration for `HTTP Transmitter`s.
	class http_transmitter_cfg {
	public:
		bool get_requests{};	  ///< GET Requests
		double get_interval{0.1}; ///< GET Interval
		std::string headers{};	  ///< Headers
		std::string url{};	  ///< Url

		http_transmitter_cfg() = default;

		/// @brief Construct from a value.
		/// @param[in] v A value.
		http_transmitter_cfg(std::string_view v);

		/// @brief Convert the configuration to a value.
		/// @returns The stringified configuration.
		std::string to_value() const;
	};

	/// @brief Configuration for `_Legacy Keypad`s.
	class legacy_keypad_cfg {
	public:
		bool unlock_on_enter_key{}; ///< Unlock on Enter Key
		double unlocked_time{2};    ///< Unlocked Time (seconds, 0 =
					    ///< infinite)
		std::string code_digits{"1234"}; ///< Code Digits
		bool show_key_press{true};	 ///< Show Key Press
		double button_hold_time{0.05};	 ///< Button Hold time

		legacy_keypad_cfg() = default;

		/// @brief Construct from a value.
		/// @param[in] v A value.
		legacy_keypad_cfg(std::string_view v);

		/// @brief Convert the configuration to a value.
		/// @returns The stringified configuration.
		std::string to_value() const;
	};

	/// @brief Configuration for `Precise Randomizer`s.
	class precise_randomizer_cfg {
	public:
		double right_percentage{50.0}; ///< Right Percentage

		precise_randomizer_cfg() noexcept = default;

		/// @brief Construct from a value.
		/// @param[in] v A value.
		precise_randomizer_cfg(std::string_view v);

		/// @brief Convert the configuration to a value.
		/// @returns The stringified configuration.
		std::string to_value() const;
	};

	class buzzer_cfg {
	public:
		std::uint8_t pitch{6};

		buzzer_cfg() noexcept = default;

		/// @brief Construct from a value.
		/// @param[in] v A value.
		buzzer_cfg(std::string_view v);

		/// @brief Convert the configuration to a value.
		/// @returns The stringified configuration.
		std::string to_value() const;
	};

	/// @brief Configuration for `Cake`s.
	class cake_cfg {
	public:
		std::uint8_t val{0xFF};

		cake_cfg() noexcept = default;

		/// @brief Construct from a value.
		/// @param[in] v A value.
		cake_cfg(std::string_view v);

		/// @brief Convert the configuration to a value.
		/// @returns The stringified configuration.
		std::string to_value() const;
	};

	/// @brief Configuration for `Kill Module`s.
	/// @warning
	///   I don't know how kill modules and player detectors encode decimal
	///   values in `Detection Size`, `Shape Orientation`, etc. If a kill
	///   module or player detector with decimal coordinate values like that
	///   is loaded, everything will explode (maybe). Negative numbers are
	///   OK though.
	class kill_module_cfg {
	public:
		bool show_detection_boundaries{}; ///< Show Detection Boundaries
		bool kill_when_touched{};	  ///< Kill When Touched
		double damage{25.0};		  ///< Damages
		std::array<double, 3> detection_size{
			15.0, 15.0, 15.0
		}; ///< Detection Size in Blocks
		detection_shape detect_shape{
			detection_shape::eSphere
		}; ///< Detection Shape
		std::array<double, 3> shape_orientation{}; ///< Shape
							   ///< Orientation
							   ///< (degrees)
		std::array<double, 3> shape_offset{}; ///< Shape Offset in
						      ///< Blocks

		kill_module_cfg() = default;

		/// @brief Construct from a value.
		/// @param[in] v A value.
		kill_module_cfg(std::string_view v);

		/// @brief Convert the configuration to a value.
		/// @returns The stringified configuration.
		std::string to_value() const;
	};

	/// @brief Configuration for `Player Detector`s.
	/// @warning
	///   I don't know how kill modules and player detectors encode decimal
	///   values in `Detection Size`, `Shape Orientation`, etc. If a kill
	///   module or player detector with decimal coordinate values like that
	///   is loaded, everything will explode (maybe). Negative numbers are
	///   OK though.
	class player_detector_cfg {
	public:
		bool show_detection_boundaries{}; ///< Show Detection Boundaries
		std::string activation_sel{"@perm>=2"}; ///< Activation Selector
		std::array<double, 3> detection_size{
			15.0, 15.0, 15.0
		}; ///< Detection Size in Blocks
		detection_shape detect_shape{
			detection_shape::eSphere
		}; ///< Detection Shape
		std::array<double, 3> shape_orientation{}; ///< Shape
							   ///< Orientation
							   ///< (degrees)
		std::array<double, 3> shape_offset{}; ///< Shape Offset in
						      ///< Blocks

		player_detector_cfg() = default;

		/// @brief Construct from a value.
		/// @param[in] v A value.
		player_detector_cfg(std::string_view v);

		/// @brief Convert the configuration to a value.
		/// @returns The stringified configuration.
		std::string to_value() const;
	};

	/// @brief Configuration for `Keypad`s.
	class keypad_cfg {
	public:
		bool unlock_on_enter_key{true}; ///< Unlock on Enter Key
		double unlocked_time{2.0};	///< Unlocked Time (seconds, 0 =
						///< infinite)
		std::string code_digits{"1234"}; ///< Code Digits
		bool show_key_press{true};	 ///< Show Key Press
		double button_hold_time{0.05};	 ///< Button Hold time

		keypad_cfg() = default;

		/// @brief Construct from a value.
		/// @param[in] v A value.
		keypad_cfg(std::string_view v);

		/// @brief Convert the configuration to a value.
		/// @returns The stringified configuration.
		std::string to_value() const;
	};

	/// @brief Represents the saved state of a block.
	class block {
	public:
		std::string value{};		  ///< Value.
		block_type type{};		  ///< Type.
		material mat{material::eDefault}; ///< Material.
		vec3 pos{};			  ///< Position.
		vec3 color{255};		  ///< Color.
		rotation rot{};			  ///< Rotation.
		bool activated{};		  ///< Activated-ness.
	};

	/// @brief
	///   Class that stores an "ID" that is unique for every object of this
	///   class created with `bl::unique_id::create()`.
	class unique_id {
	private:
		// `_a` is the least significant and `_d` is the most
		// significant. There's probably no need to use a 256-bit
		// integer like this, but might as well really really make sure
		// it won't overflow.

		// The default `operator<=>` treats the first member as the most
		// significant so we put `_d` first.

		std::uint_least64_t _d{};
		std::uint_least64_t _c{};
		std::uint_least64_t _b{};
		std::uint_least64_t _a{};

	public:
		static unique_id create();
		auto operator<=>(unique_id const&) const noexcept = default;
	};

	/// @brief Wires.
	class block_wire {
	public:
		unique_id from_blk{}; ///< The source block of the wire.
		unique_id to_blk{};   ///< The destination block of the wire.
		char from_con{};      ///< The source connector of the wire.
		char to_con{};	      ///< The destination block of the wire.
	};

	/// @brief
	///   Emplacements. This represents the saved state of an entire Build
	///   Logic world.
	class emplacement {
	public:
		std::map<unique_id, block> blks{};	 ///< Blocks.
		std::map<unique_id, block_wire> wires{}; ///< Wires.

		emplacement() = default;

		/// @brief Constructor.
		/// @param[in] src
		///   An encoded emplacement (savestring) to load from.
		emplacement(std::string_view src);

		/// @brief Create a new block.
		/// @param[in] blk The block.
		/// @returns The ID of the newly-created block.
		unique_id place(block const& blk);
		unique_id place(block&& blk);

		/// @brief Connect two blocks with a wire.
		/// @param[in] wire The wire.
		/// @returns The ID of the newly-created wire.
		unique_id connect(block_wire const& wire);
		unique_id connect(block_wire&& wire);

		/// @brief Remove a block.
		/// @param[in] blk The block `unique_id` to remove.
		/// @returns
		///   The number of blocks with the unique ID `blk` removed.
		std::size_t remove(unique_id const& blk) noexcept;

		/// @brief Remove a wire.
		/// @param[in] wire The wire `unique_id` to remove.
		/// @returns
		///   The number of wires with the unique ID `wire` removed.
		std::size_t disconnect(unique_id const& wire) noexcept;

		/// @brief Remove all blocks and wires.
		void clear() noexcept;

		std::string save() const;
	};

	/// @brief Get a `block_type_traits` object of a particular block type.
	/// @param[in] type A block type.
	/// @returns The aforementioned traits.
	/// @note
	///   For `bl::block_type::eErreur`, a block ID of `0` is returned in
	///   the traits. Technically the block ID is `Error` but I'd say `0`
	///   makes more sense, and I did not want to make all block IDs strings
	///   to make `Error` work.
	block_type_traits get_block_type_traits(block_type type);

	/// @brief Get a `material_traits` object of a particular material.
	/// @param[in] mat A material.
	/// @returns The aforementioned traits.
	material_traits get_material_traits(material mat);

	/// @brief
	///   Get a `delay_interval_traits` object of a particular delay
	///   interval.
	/// @param[in] interval A delay interval.
	/// @returns The aforementioned traits.
	delay_interval_traits
	get_delay_interval_traits(delay_interval interval);

	/// @brief
	///   Get a `timer_interval_traits` object of a particular timer
	///   interval.
	/// @param[in] interval A timer interval.
	/// @returns The aforementioned traits.
	timer_interval_traits
	get_timer_interval_traits(timer_interval interval);

	/// @brief
	///   Get a `detection_shape_traits` object of a particular detection
	///   shape.
	/// @param[in] shape A detection shape.
	/// @returns The aforementioned traits.
	detection_shape_traits
	get_detection_shape_traits(detection_shape shape);

	/// @brief Create a block type from an encoded name.
	/// @param[in] v An encoded name.
	/// @returns A block type.
	block_type block_type_from_encoded_name(std::string_view v);

	/// @brief Create a block type from a block ID.
	/// @param[in] v A block ID.
	/// @returns A block type.
	block_type block_type_from_block_id(std::size_t v);

	/// @brief Create a material from an encoded material.
	/// @param[in] v An encoded material.
	/// @returns A material.
	material decode_material(char v);

	/// @brief Create a delay interval from an encoded delay interval.
	/// @param[in] v An encoded delay interval.
	/// @returns A delay interval.
	delay_interval decode_delay_interval(char v);

	/// @brief Create a timer interval from an encoded timer interval.
	/// @param[in] v An encoded timer interval.
	/// @returns A timer interval.
	timer_interval decode_timer_interval(char v);

	/// @brief Create a detection shape from an encoded detection shape.
	/// @param[in] v An encoded detection shape.
	/// @returns A detection shape.
	detection_shape decode_detection_shape(std::size_t v);

	/// @brief Encode a world ID.
	/// @param[in] v An unsigned integer.
	/// @returns A string.
	std::string encode_world_id(std::size_t v);

	/// @brief Decode a world ID.
	/// @param[in] v A string.
	/// @returns An unsigned integer.
	std::size_t decode_world_id(std::string_view v);

	/// @brief Encode units.
	/// @param[in] v An unsigned integer.
	/// @returns A string.
	std::string encode_units(std::size_t v);

	/// @brief Decode units.
	/// @param[in] v A string.
	/// @returns An unsigned integer.
	std::size_t decode_units(std::string_view v);

	/// @brief
	///   Encode according to [0-9a-zA-Z]. This character set is not used
	///   directly by the game, but it's a common subset found in other
	//    character sets.
	/// @param[in] v An unsigned integer.
	/// @returns A character.
	char encode62(std::uint8_t v);

	/// @brief Encode according to the BL64 character set.
	/// @param[in] v An unsigned integer.
	/// @returns A character.
	char encode_bl64(std::uint8_t v);

	/// @brief Encode according to the BL71 character set.
	/// @param[in] v An unsigned integer.
	/// @returns A character.
	char encode_bl71(std::uint8_t v);

	/// @brief Encode according to the BL75 character set.
	/// @param[in] v An unsigned integer.
	/// @returns A character.
	char encode_bl75(std::uint8_t v);

	/// @brief Encode according to the BL82 character set.
	/// @param[in] v An unsigned integer.
	/// @returns A character.
	char encode_bl82(std::uint8_t v);

	/// @brief Opposite of `bl::encode62()`.
	/// @param[in] v A character.
	/// @returns An unsigned integer.
	std::uint8_t decode62(char v);

	/// @brief Opposite of `bl::encode_bl64()`.
	/// @param[in] v A character.
	/// @returns An unsigned integer.
	std::uint8_t decode_bl64(char v);

	/// @brief Opposite of `bl::encode_bl71()`.
	/// @param[in] v A character.
	/// @returns An unsigned integer.
	std::uint8_t decode_bl71(char v);

	/// @brief Opposite of `bl::encode_bl75()`.
	/// @param[in] v A character.
	/// @returns An unsigned integer.
	std::uint8_t decode_bl75(char v);

	/// @brief Opposite of `bl::encode_bl82()`.
	/// @param[in] v A character.
	/// @returns An unsigned integer.
	std::uint8_t decode_bl82(char v);
}

/// @brief
///   Namespace dedicated to cake slices, for convenience. Bitwise OR these
///   slices together to make combinations of slices.
/// @note
///   The slices are numbered in clockwise order when viewing the cake along the
///   positive Z axis. Therefore, if you have a cake and look at it along +Z,
///   then `e2` should come after `e1` that should come after `e0` in clockwise
///   order. `e0` is in the top-right quadrant of the cake, just to the right of
///   the vertical centerline of the cake.
namespace bl::cake {
	inline constexpr std::uint8_t e6{1 << 0};
	inline constexpr std::uint8_t e3{1 << 1};
	inline constexpr std::uint8_t e4{1 << 2};
	inline constexpr std::uint8_t e1{1 << 3};
	inline constexpr std::uint8_t e2{1 << 4};
	inline constexpr std::uint8_t e0{1 << 5};
	inline constexpr std::uint8_t e7{1 << 6};
	inline constexpr std::uint8_t e5{1 << 7};
};

/// @brief AND Gate
namespace bl::con::eAND_Gate {
	inline constexpr char a{'1'}; ///< First input.
	inline constexpr char b{'2'}; ///< Second input.
	inline constexpr char q{'3'}; ///< Output.
};

/// @brief NAND Gate
namespace bl::con::eNAND_Gate {
	inline constexpr char a{'1'}; ///< First input.
	inline constexpr char b{'2'}; ///< Second input.
	inline constexpr char q{'3'}; ///< Output.
};

/// @brief NOR Gate
namespace bl::con::eNOR_Gate {
	inline constexpr char a{'1'}; ///< First input.
	inline constexpr char b{'2'}; ///< Second input.
	inline constexpr char q{'3'}; ///< Output.
};

/// @brief NOT Gate
namespace bl::con::eNOT_Gate {
	inline constexpr char a{'1'}; ///< Input.
	inline constexpr char q{'2'}; ///< Output.
};

/// @brief OR Gate
namespace bl::con::eOR_Gate {
	inline constexpr char a{'1'}; ///< First input.
	inline constexpr char b{'2'}; ///< Second input.
	inline constexpr char q{'3'}; ///< Output.
};

/// @brief Splitter
namespace bl::con::eSplitter {
	inline constexpr char a{'1'}; ///< Input.
	inline constexpr char q{'2'}; ///< First output.
	inline constexpr char r{'3'}; ///< Second output.
};

/// @brief XNOR Gate
namespace bl::con::eXNOR_Gate {
	inline constexpr char a{'1'}; ///< First input.
	inline constexpr char b{'2'}; ///< Second input.
	inline constexpr char q{'3'}; ///< Output.
};

/// @brief XOR Gate
namespace bl::con::eXOR_Gate {
	inline constexpr char a{'1'}; ///< First input.
	inline constexpr char b{'2'}; ///< Second input.
	inline constexpr char q{'3'}; ///< Output.
};

/// @brief Counter
namespace bl::con::eCounter {
	inline constexpr char inc_out{'1'}; ///< Carry-out/overflow output.
	inline constexpr char dec_out{'2'}; ///< Underflow output.
	inline constexpr char inc_in{'3'};  ///< Increment input.
	inline constexpr char dec_in{'4'};  ///< Decrement input.
	inline constexpr char q0{'5'};	    ///< Output[0].
	inline constexpr char q1{'6'};	    ///< Output[1].
	inline constexpr char q2{'7'};	    ///< Output[2].
	inline constexpr char q3{'8'};	    ///< Output[3].
	inline constexpr char reset{'9'};   ///< Reset input.
};

/// @brief 8 Bit Shifter Counter
namespace bl::con::e8_Bit_Shifter_Counter {
	inline constexpr char left{'1'};   ///< Increment/shift left input.
	inline constexpr char reset{'2'};  ///< Reset input.
	inline constexpr char output{'3'}; ///< Input for whether to output.
	inline constexpr char right{'4'};  ///< Decrement/shift right input.
	inline constexpr char q7{'5'};	   ///< Output[7].
	inline constexpr char q6{'6'};	   ///< Output[6].
	inline constexpr char q5{'7'};	   ///< Output[5].
	inline constexpr char q4{'8'};	   ///< Output[4].
	inline constexpr char q3{'9'};	   ///< Output[3].
	inline constexpr char q2{'a'};	   ///< Output[2].
	inline constexpr char q1{'b'};	   ///< Output[1].
	inline constexpr char q0{'c'};	   ///< Output[0].
};
