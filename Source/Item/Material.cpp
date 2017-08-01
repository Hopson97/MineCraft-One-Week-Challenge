#include "Material.h"

const Material Material::NOTHING        (ID::Nothing, 0,  false, "None" );
const Material Material::GRASS_BLOCK    (ID::Grass, 99, true, "Grass Block");
const Material Material::DIRT_BLOCK     (ID::Dirt, 99, true, "Dirt Block");
const Material Material::STONE_BLOCK    (ID::Stone, 99, true, "Stone Block");
const Material Material::OAK_BARK_BLOCK (ID::OakBark, 99, true, "Oak Bark Block");
const Material Material::OAK_LEAF_BLOCK (ID::OakLeaf, 99, true, "Oak Leaf Block");
const Material Material::SAND_BLOCK     (ID::Sand, 99, true, "Sand Block");

Material::Material(Material::ID id, int maxStack, bool isBlock, std::string&& name)
:   id              (id)
,   maxStackSize    (maxStack)
,   isBlock         (isBlock)
,   name            (std::move(name))
{

}

BlockId Material::toBlockID() const
{
    switch (id)
    {
        case Nothing:
            return BlockId::Air;

        case Grass:
            return BlockId::Grass;

        case Dirt:
            return BlockId::Dirt;

        case Stone:
            return BlockId::Stone;

        case OakBark:
            return BlockId::OakBark;

        case OakLeaf:
            return BlockId::OakLeaf;

        case Sand:
            return BlockId::Sand;

        default:
            return BlockId::NUM_TYPES;
    }
}

const Material& Material::toMaterial(BlockId id)
{
    switch (id)
    {
        case BlockId::NUM_TYPES:
        case BlockId::Air:
            return NOTHING;

        case BlockId::Grass:
            return GRASS_BLOCK;

        case BlockId::Dirt:
            return DIRT_BLOCK;

        case BlockId::Stone:
            return STONE_BLOCK;

        case BlockId::OakBark:
            return OAK_BARK_BLOCK;

        case BlockId::OakLeaf:
            return OAK_LEAF_BLOCK;

        case BlockId::Sand:
            return SAND_BLOCK;
    }
}


