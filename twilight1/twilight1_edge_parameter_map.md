# TWILIGHT-1 EDGE Parameter Map

## Patch format
Expanded FM-1 patch: 156 bytes.

## Verified parameter offsets

### Operator output levels
Six native DX7 operator output levels:

- OP1: offset 121
- OP2: offset 100
- OP3: offset 79
- OP4: offset 58
- OP5: offset 37
- OP6: offset 16

Verified native range: 0-99.

These offsets are verified from the existing TWILIGHT-1
BODY prototype and its tests.

## EDGE candidates

### Operator output level
Verified offsets, but output level alone is not a
brightness parameter.

Not approved as the EDGE transformation target.

### Operator frequency
Not yet mapped in the expanded 156-byte format.

### Feedback
Not yet mapped in the expanded 156-byte format.

### Algorithm
Not yet mapped in the expanded 156-byte format.

### Envelope parameters
Not yet mapped for EDGE.

## Implementation status
EDGE transformation is not implemented.

EDGE isolation test remains active.

## Safety
- Original patch is read-only.
- Output patch is separate.
- No unverified offsets may be written.
- EDGE 0 must remain neutral.
- Every modified parameter must be range-bounded.
- Unrelated bytes must remain unchanged.
