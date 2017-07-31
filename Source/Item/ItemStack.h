#ifndef ITEMSTACK_H_INCLUDED
#define ITEMSTACK_H_INCLUDED

#include "Material.h"

class ItemStack
{
    public:
        ItemStack(Material material, int amount);

        void add(int amount);
        void remove();

    private:
        Material m_material;
        int      numInStack;

};

#endif // ITEMSTACK_H_INCLUDED
