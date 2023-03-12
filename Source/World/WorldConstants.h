#ifndef WORLDCONSTANTS_H_INCLUDED
#define WORLDCONSTANTS_H_INCLUDED

// Defines the most basic rules for chunk generation in any given world.

constexpr int CHUNK_SIZE = 16, CHUNK_AREA = CHUNK_SIZE * CHUNK_SIZE,
              CHUNK_VOLUME = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE,

              WATER_LEVEL = 64;

#endif // WORLDCONSTANTS_H_INCLUDED
