# Changelog

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
