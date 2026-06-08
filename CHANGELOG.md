# Changelog

## 0.7.1

Fixed `bl::emplacement::save()` not saving wires correctly. This bug was
probably in every version of bl until this.

## 0.7.0

- Added `operator==()` to all classes that didn't have it already.
- Added `std::hash` specializations for `bl::vec3`, `bl::rotation`, and
  `bl::unique_id`.
- Switched `bl::eeprom_cfg`, `bl::eeprom16_cfg`, and `bl::emplacement` to use
  `std::unordered_map`s instead of `std::map`s.

## 0.6.1

- Removed the `bl::emplacement::connect(bl::block_wire&&)` overload.
- Made the `place()`, `connect()`, `remove()`, `disconnect()`, and `clear()`
  methods of `bl::emplacement` inline.

This was a patch version bump because the changes were backward-compatible and
no new functionality was added.

## 0.6.0

- Tweaked the `detection_size` default member initializer of
  `bl::kill_module_cfg` and `bl::player_detector_cfg` to be
  `{15.0, 15.0, 15.0}`.
- Tweaked the `mat` and `color` default member initializers of `bl::block` to be
  `bl::material::eDefault` and `bl::vec3(255)` respectively.
- Tweaked `DOCS.md`.

## 0.5.0

- Removed `bl::encode_bl72()`, `bl::decode_bl72()`, `bl::encode_field_len()`,
  and `bl::decode_field_len()`.
- Fixed extended value field lengths. Previously I thought there was a `#` in
  the charset used for extended value field lengths but no such `#` is actually
  used in the game.
- More work done on `DOCS.md`.

## 0.4.0

- Changed `bl::con::eAND_Gate`'s members to lowercase.
- Added the connectors of 9 more blocks to `bl::con`.
- More work on the docs.

## 0.3.0

- Made the code in `cfg.cpp` a little less crap.
- Added constructor to `bl::rotation`.
- Got a start on the `DOCS.md` file.

## 0.2.1

fix

Okay but seriously, there was a bug in the savestring decoder where the `;`
block terminator was put in the `blk` stream which is wrong. Versions <=0.2.0
were affected with the bug.

## 0.2.0

- Added the `8 Bit Shift Register` block to `bl::block_type`.
- Added the changelog that you are reading right now.

## 0.1.0

Initial commit.
