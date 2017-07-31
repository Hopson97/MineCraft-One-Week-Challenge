#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include <string>
#include "../World/Block/BlockId.h"

#include "../Util/NonCopyable.h"

struct Material : public NonCopyable
{
    enum ID
    {
        Nothing,
        Grass,
        Dirt,
        Stone,
        OakBark,
        OakLeaf
    };

    const static Material   NOTHING,
                            GRASS_BLOCK,
                            DIRT_BLOCK,
                            STONE_BLOCK,
                            OAK_BARK_BLOCK,
                            OAK_LEAF_BLOCK;

    Material(Material::ID id, int maxStack, bool isBlock, std::string&& name);

    BlockId toBlockID() const;

    const Material::ID  id;
    const int           maxStackSize;
    const bool          isBlock;
    const std::string   name;
};

namespace std
{
    template<>
    struct hash<Material::ID>
    {
        size_t operator()(const Material::ID& id) const
        {
            std::hash<Material::ID> hasher;

            return hasher(id);
        }
    };
}


#endif // MATERIAL_H_INCLUDED
