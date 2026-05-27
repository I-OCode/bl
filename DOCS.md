# Docs

Note: As I said in the README file, all of this was reverse-engineered by one
guy in his basement.

## Savestring format

The savestring format consists of encoded blocks, separated by semicolons. An
encoded block consists of the encoded name, encoded position, encoded rotation,
encoded color, and encoded material.

```text
<encoded name><encoded position>[encoded rotation [encoded color] [encoded material]]
```

(Angle brackets mean that something is required to be present in the format,
whereas square brackets mean it's optional.)

This forms the basic encoding format for blocks. There is more stuff that can
be included in blocks, but we'll get to that later.

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

TODO: more writing...
