# TWILIGHT-1 K4 MOTION Design

## Purpose
Add perceived movement to a static FM patch: vibrato and tremolo
depth, without changing the patch's timbre identity.

MOTION must not simply raise every modulation parameter: on the FM-1,
a depth parameter does nothing unless its sensitivity is non-zero.

## Macro range
0-100. MOTION 0 must leave the patch byte-identical.

## Verified parameters used

| Offset | Parameter | Range |
|---|---|---|
| 139 | LFO pitch mod depth (PMD) | 0-99 |
| 140 | LFO amp mod depth (AMD) | 0-99 |
| 143 | Pitch mod sensitivity (PMS) | 0-7 |
| op*21 + 14 | Operator amp mod sensitivity | 0-3 |
| op*21 + 16 | Operator output level | 0-99 |

Not used in v1: 137 (LFO rate), 138 (LFO delay), 141 (sync),
142 (waveform). Those change the character of the movement, not the
amount, and are a separate design decision.

## Transformation


### Why max() instead of assignment
MOTION adds movement to movement. A patch that already has vibrato
must not lose it when MOTION is low. MOTION therefore never reduces
139 or 140 — it only raises them toward the target.

### Why the sensitivities are raised
- PMD (139) is multiplied by PMS (143). At PMS 0 the vibrato is
  silent, so MOTION would appear broken. Setting PMS to 3 gives a
  usable vibrato when the patch had none.
- AMD (140) is applied per operator, gated by that operator's amp
  mod sensitivity (op*21+14). At 0 the operator does not tremolo.
  Only operators with a non-zero output level are enabled, so
  silent operators stay silent.

## Expected values

| motion | 139 written | 140 written |
|---|---|---|
| 0 | unchanged (copy) | unchanged (copy) |
| 25 | 15 | 10 |
| 50 | 30 | 20 |
| 100 | 60 | 40 |

Readings are taken from a patch with 139 = 0, 140 = 0.

## Known limitation
Patch values are latched at note-on (`dx7note_init` in
`web/synth/dx7synth.c`). A MOTION change is heard on the next note,
not on a note already sounding. This applies to every TWILIGHT-1
macro, not only MOTION.

## Test requirements
- MOTION 0 leaves the patch byte-identical.
- Source patch is never modified.
- 25 / 50 / 100 produce the values in the table above.
- Existing PMD / AMD above the target are preserved, not lowered.
- PMS 0 becomes 3; an existing PMS of 5 stays 5.
- An operator with level 0 keeps amp mod sensitivity 0.
- An operator with a non-zero level and sensitivity 0 becomes 1.
- Bytes outside 139, 140, 143 and op*21+14 are unchanged.
- MOTION above 100 is rejected by the Engine Core.

## Implementation status
Not implemented. Design only.
