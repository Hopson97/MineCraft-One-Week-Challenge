#ifndef ITEMSTACK_H_INCLUDED
#define ITEMSTACK_H_INCLUDED

#include "Material.h"

class ItemStack
{
    public:
        ItemStack(const Material& material, int amount);

        void add(int amount);
        void remove();

        int getNumInStack() const;

        const Material& getMaterial() const;

    private:
        const Material* m_pMaterial;
        int             m_numInStack;

};

#endif // ITEMSTACK_H_INCLUDED
