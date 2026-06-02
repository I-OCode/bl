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

There are some blocks that are not listed in the build tool but can be placed
using other methods, like `Erreur` and the block names beginning with `_Legacy`.
However there are some unlisted blocks that can't be placed at all. These are
restricted blocks.

In the past you could see every block, restricted or not, in the block search
menu if you left the search box empty. Now that's not possible but the block
limiter search menu shows (some) restricted blocks, so I'm also aware of these
unlisted blocks:

- Loki Spawner
- Junction Block
- Physics Block
- Connector Block
- Block Painter
- Shared EEPROM
- Checkered Block

There're probably more though. Also, I don't know what the encoded names of
these restricted blocks are, because well, you can't place them.

Restricted blocks have the name `e_unknown_XXX_` in `bl::block_type`, where
`XXX` is their block ID. The reason why I didn't use names like `eLoki_Spawner`
or `eJunction_Block` is that I have no idea which restricted block corresponds
to which block ID. Technically the enumerator values don't strictly have to
correspond to block IDs, but I wanted to be consistent.

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
"BL71" is not official; I coined it myself. You'll see this BL*xx* pattern being
used in the rest of the docs and in the source code.

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

Each block has its own unique way of encoding their values, but there are a few
common patterns.

Notably for blocks that have configurations, like your kill modules or player
detectors or speakers, the value consists of any number of *fields* (unofficial
term). Each field has the following format:

```text
len-min-one contents
```

`len-min-one` is a number encoded in the *BL82* character set (again, unofficial
term). It represents the length of `contents` minus 1. Therefore, an encoded
`len-min-one` of `0` signals that `contents` is 1 character long.

For the case where `contents` has zero length, a `` ` `` is used in place of
`len-min-one`.

Here's a funny quirk: in the BL82 character set, the exclaimation mark appears
*twice*. That's right. Both 62 and 78 are encoded to `!`. But which number is
picked when decoding a `!`? The answer is 78. This means that if you have a 63
character long string, Build Logic will treat it as a 79 character long string
therefore causing the game to read data further than the string and into the
rest of the value. The game does not read further than the end of the value
though, so no game-breaking exploits unfortunately.

Another quirk: in block configurations that have a field in which you can type
arbitrary text like HTTP transmitters, you can type `/=` or `/^` and the game
will treat each of them as being 2 characters long. But when the game loads the
block, it will remove the `/`s in the `/=`s and `/^`s because it thinks that
it's a value escape. Therefore you have a buggy configuration where the field
length is longer than the actual field content. Just like the previous quirk I
mentioned, this causes the game to read data further than the field and into the
rest of the value. But again, unfortunately, the game does not go further than
the end of the value.

Anyways, it's over. Right? No. There's still a special case where `len-min-one`
is too big to fit in the BL82 character set. What to do then? Well, this
alternative format is used for fields:

```text
"|" len "~" contents
```

Where `len` represents the length of `contents`. `len` is encoded in the same
format as world IDs. I personally call the `len` part surrounded by `|` and `~`
the *extended field length*.

TODO: explain other value encoding formats
