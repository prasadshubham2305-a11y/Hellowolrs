# TWILIGHT-1 K2 EDGE Design

## Purpose
Increase tonal brightness, sharper harmonics and
perceived bite in FM patches.

EDGE must not simply increase overall volume.

## Macro Range
0-100

- EDGE 0: Neutral
- EDGE 25: Subtle tonal emphasis
- EDGE 50: Moderate brightness and bite
- EDGE 75: Stronger metallic edge
- EDGE 100: Maximum bounded transformation

These are design targets, not implemented behaviour.

## Safety Principles
1. Original patch remains unchanged.
2. Transform a separate patch copy.
3. Respect native parameter limits.
4. Never use unverified patch offsets.
5. Never transform an already transformed patch.
6. Do not modify unrelated patch data.
7. EDGE 0 must leave the patch unchanged.

## Candidate Parameters
Require verification before implementation:

- Operator output levels
- Frequency ratios
- Feedback
- Operator modulation relationships
- Envelope characteristics

## Implementation Status
Not implemented.

EDGE currently has an isolation test.

## Future Test Requirements
- EDGE 0 leaves patch unchanged.
- Source patch remains unchanged.
- Output values remain bounded.
- Unrelated bytes remain unchanged.
- Only approved parameters are modified.
- Invalid input is handled safely.
- GitHub Actions tests pass.
