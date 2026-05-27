# Docs

Note: As I said in the README file, all of this was reverse-engineered by one
guy in his basement.

## Savestring format

The savestring format consists of encoded blocks, separated by semicolons. An
encoded block consists of the encoded name, encoded position, encoded rotation,
encoded color, and encoded material.

```text
encoded-name encoded-position [encoded-rotation [encoded-color] [encoded-material]]
```

(Square brackets mean that something is optional in the format.)

This forms the basic encoding format for blocks. There is more stuff that can
be included in blocks, but we'll get to that later.

By the way, I call these separator semicolons "block terminators" and you can
see this term being used in the source code.

### Encoded names

Encoded names are literally the encoded version of a block name. You can find a
big list of all the encoded names in the `block_type_db.txt` file. Here's a
sample line from the file:

```text
X(Block, "Block", "G", 43, F)
```

`"Block"` is the full name of the block, and `G` is the encoded name. `43` is
the block ID, which is a numerical representation of block types.

Unfortunately, one character isn't enough to encode all blocks so Tomtom
extended the encoded name format with the special characters `#` and `%`. When
the savestring decoder finds one of these characters, it treats the following
character as being part of the encoded name.

### Encoded positions, colors, and rotations

The trouble is that I kind of forgot/don't fully understand how the encoding
format for these things work so yeah, just go to `bl.cpp` and look at the code
for encoding and decoding `bl::vec3` and `bl::rotation`. The code works, okay,
and that's what matters.

### Encoded materials

Encoded materials are really simple. They're just characters with a 1:1
correspondence to decoded materials. Go have a look in `material_db.txt` to see
what I mean.

### Values

Well that's the basics, but there's more. Notably, we need to understand how
values are encoded. Values, are, well, values for blocks. They contain encoded
info for things like configurations of blocks or cake slice combinations or
buzzer pitches or dip switch values, etc. For things like levers and toggle
buttons, values are not used and instead a more boolean mechanism is used:
activated(-ness). We'll get to that later. For now though, we're interested in
values.

Values extend upon the basic encoding format I showed you earlier and begin with
a `/` (slash):

```text
basic-encoding ["/" value]
```

(Text contained in double quotes represent literal text.)

`=`s (equal signs) and `^` (carets) have to be "escaped" using `/`, so to speak,
in the value if the block is not a component. Components, by the way, are blocks
that have at least one connector on them, meaning that they can be wired. By
"escape", I mean that a `/` has to appear before any `=` or `^` that might
appear in the value. Note that `>` characters are not escaped. `/`s themselves
aren't escaped either.

### World IDs and activated-ness

All component blocks have something called a world ID that is unique to that
particular block. It is used for identifying/referencing blocks in wire
connections.

World IDs are encoded using a positional number system. It is not base-10
though. It is base-71. The bl library provides the `bl::encode_bl71()` and
`bl::decode_bl71()` for encoding and decoding these base-71 digits.

The character set for these base-71 digits is called "BL71" which stands for
"Build Logic (character set) 71", for lack of a better name. Note that the name
"BL71" is not official; I coined it myself.

World IDs come after `value` (or `basic-encoding` if `value` is not present) and
begin with the `=` character, like so:

```text
1$BwfA=1
```

The `=1` part is the world ID.

But now let's get to activated-ness. As I mentioned earlier, some blocks like
levers and toggle buttons do not use values to represent their on/off state.
Instead they use activated-ness, which is a boolean mechanism designed
specifically for this purpose. How is it encoded? Well, to signal that a block
is activated, the `=` (equal sign) that starts a world ID is replaced with a `>`
(right angle bracket). `>` behaves the same as `=` except it indicates the block
is activated.

### Wires

Time for the fun part. Wires.

A block can have incoming wires (that is, wires that start at some other block
and go to this block). The first incoming wire starts with a `^` (caret) and
then consists of a destination connector, destination world ID, source
connector, and source world ID in the following format:

```text
dst-con dst-world-id "_" src-con src-world-id
```

This wire data comes after `value` or `basic-encoding` like world IDs. Wire data
and world IDs cannot both be specified, but this is fine, because wire data is a
superset of world IDs. This is because "incoming wires" *means* that its
destination is the current block, meaning that the "destination world ID" I told
you about in the first incoming wire is just the world ID of the current block,
making it equivalent to the world ID you'd find after `=`.

Each of the rest of the incoming wires are in this format:

```text
"." dst-con src-world-id src-con
```

However there is a special case for when the source world ID is equal to the
destination world ID. In this "to-self" case, the first incoming wire is encoded
like this:

```text
dst-con dst-world-id "-" src-con
```

And for the rest of the incoming wires:

```text
"*" dst-con src-con
```

## Value format

You thought it was over? Not yet, buddy. Values are their own little world too.

TODO: explain value format
