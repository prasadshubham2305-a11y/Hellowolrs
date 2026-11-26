# TWILIGHT-1 Verified Patch Map

## Patch format
FM-1 expanded FM patch: 156 bytes.

Every offset in this file is verified against the SDK source
(`web/synth/dx7note.c`, `web/synth/dx7lfo.c`, `web/synth/dx7synth.c`,
`web/synth/dx7pitchenv.c`). Offsets not listed here are unverified and
must not be written.

Ranges are the published DX7 voice ranges. The SDK does not clamp these
values, so TWILIGHT-1 must.

## Operator block (6 operators, 21 bytes each)

Operator `op` starts at `op * 21`:

| Offset | Parameter | Range | Verified by |
|---|---|---|---|
| +0..+3 | EG rates R1-R4 | 0-99 | `dx7env_set(..., parm, ...)` |
| +4..+7 | EG levels L1-L4 | 0-99 | `dx7env_set(..., parm + 4, ...)` |
| +8 | Key breakpoint | 0-99 | `scale_lvl(..., parm[8], ...)` |
| +9 | Left depth | 0-99 | `scale_lvl(...)` |
| +10 | Right depth | 0-99 | `scale_lvl(...)` |
| +11 | Left curve | 0-3 | `scale_lvl(...)` |
| +12 | Right curve | 0-3 | `scale_lvl(...)` |
| +13 | Rate scaling | 0-7 | `scalerate(midinote, parm[13])` |
| +14 | Amp mod sensitivity | 0-3 | `parm[14] & 3` |
| +15 | Key velocity sensitivity | 0-7 | `sacle_vel(velocity, parm[15])` |
| +16 | Operator output level | 0-99 | `dx7_outlvl(parm[16])` |
| +17 | Osc mode (0 ratio, 1 fixed) | 0-1 | `osc_freq(..., parm[17], ...)` |
| +18 | Frequency coarse | 0-31 | `osc_freq(...)` |
| +19 | Frequency fine | 0-99 | `osc_freq(...)` |
| +20 | Detune | 0-14 | `osc_freq(...)` |

Operator output level absolute offsets: 16, 37, 58, 79, 100, 121.

## Global block

| Offset | Parameter | Range | Verified by |
|---|---|---|---|
| 126-129 | Pitch EG rates | 0-99 | `dx7pitchenv_set(..., patch + 126, ...)` |
| 130-133 | Pitch EG levels | 0-99 | `dx7pitchenv_set(..., patch + 130, ...)` |
| 134 | Algorithm | 0-31 | `this->algorithm = patch[134]` |
| 135 | Feedback | 0-7 | `patch[135] ? 8 - patch[135] : 16` |
| 136 | Osc key sync | 0-1 | `if (patch[136]) dx7note_oscsync(...)` |
| 137 | LFO rate | 0-99 | `dx7lfo_reset(..., patch + 137, ...)` |
| 138 | LFO delay | 0-99 | `dx7lfo_reset(...)` |
| 139 | LFO pitch mod depth (PMD) | 0-99 | `patch[139] * 165 >> 6` |
| 140 | LFO amp mod depth (AMD) | 0-99 | `patch[140] * 165 >> 6` |
| 141 | LFO sync | 0-1 | `params[4] != 0` |
| 142 | LFO waveform | 0-5 | `params[5]` |
| 143 | Pitch mod sensitivity | 0-7 | `pitchmodsenstab[patch[143] & 7]` |
| 144 | Transpose | 0-48, centred on 24 | `midi + patch[144] - 24` |

**Transpose warning:** the stored value is biased. 24 means no transpose.
Writing raw semitones here detunes the patch by -24 semitones.

## What this means for MOTION

MOTION must not simply raise 139 or 140:

- PMD (139) does nothing while pitch mod sensitivity (143) is 0.
- AMD (140) does nothing on an operator whose amp mod sensitivity
  (`op * 21 + 14`) is 0.
- LFO delay (138) suppresses the LFO at note start if it is high.
- LFO rate (137) sets the speed of the movement.

A MOTION design must decide and document:

1. Which of 137/138/139/140/143 it may write.
2. What it does when the relevant sensitivity is already 0.
3. That it never writes outside the ranges above.

## EDGE

EDGE modifies feedback (135), capped at 7. The macro design is in
`twilight1_edge_design.md`.

## Safety rules

- Original patch is read-only; transformations write a separate buffer.
- Every written value stays inside the verified range.
- Unrelated bytes must remain unchanged.
- A macro at 0 must leave the patch unchanged.
- No offset may be used before it is listed in this file.
