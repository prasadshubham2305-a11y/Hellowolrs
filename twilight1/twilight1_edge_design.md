# TWILIGHT-1 K2 EDGE Design

## Purpose
K2 EDGE is intended to increase tonal brightness, sharper
harmonics and perceived bite in FM patches.

EDGE must not simply increase overall volume.

## Macro Range
0-100

- EDGE 0: Neutral. No patch modification.
- EDGE 25: Subtle tonal emphasis.
- EDGE 50: Moderate brightness and bite.
- EDGE 75: Stronger metallic edge.
- EDGE 100: Maximum bounded transformation.

These are design targets, not implemented behaviour.

## Safety Principles

1. Original patch must remain unchanged.
2. Transformation operates on a separate patch copy.
3. Parameter values must remain within native limits.
4. No unverified patch offsets.
5. No repeated transformation of an already transformed patch.
6. EDGE must not modify unrelated patch data.
7. EDGE 0 must return an unchanged patch.

## Candidate Parameters

Parameters requiring verification before implementation:

- Operator output levels
- Frequency ratios and oscillator relationships
- Feedback
- Operator modulation relationships
- Relevant envelope characteristics

No parameter is approved for modification until its
native location, range and behaviour are verified.

## Implementation Status

Not implemented.

EDGE currently has an isolation test ensuring that
changing the EDGE macro does not modify the patch.

## Future Test Requirements

- EDGE 0 leaves patch unchanged.
- Source patch remains unchanged.
- Output values remain bounded.
- Unrelated patch bytes remain unchanged.
- EDGE changes only approved parameters.
- Invalid input is handled safely.
- Tests run through GitHub Actions.
