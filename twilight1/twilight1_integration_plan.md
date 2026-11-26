# TWILIGHT-1 Firmware Integration Plan

## Status
TWILIGHT-1 is a host-tested patch transformation layer. It is NOT part of
the FM-1 firmware today. Nothing here is implemented.

## Where the patch lives
In `web/engine/sound.c`, which is compiled into the firmware app:

- `sources[track].patch` is the live 156-byte FM patch for a track.
- `engine_note()` (around line 399) is the single funnel for DX7 note
  starts and stops. It calls
  `synth_dx7_midi_tuned(fm, sources[track].patch, ...)`.

Line numbers drift. Search for `engine_note` instead of trusting them.

## Why note-on only
`dx7note_init()` reads the patch only when a note starts. Transforming
on note-off or on controller traffic cannot be heard and only costs time
in the audio path.

## The change (not applied)
Inside `engine_note()`, transform a copy for note-ons only:

```c
    if (groove_source_type(track) == GROOVE_DX7) {
        uint8_t m[3] = {(uint8_t)(velocity ? 0x90 : 0x80),
                        (uint8_t)note, (uint8_t)velocity};
        if (sources[track].fm) {
            if (velocity) {
                uint8_t patch[156];
                if (twilight1_engine_apply(sources[track].patch, patch,
                                           &macros[track]) == 0)
                    (void)synth_dx7_midi_tuned(sources[track].fm, patch,
                                               m, 3, cents);
            } else {
                (void)synth_dx7_midi_tuned(sources[track].fm,
                                           sources[track].patch, m, 3, cents);
            }
        }
    }
