#include "ItemStack.h"

#include <algorithm>

ItemStack::ItemStack(const Material& material, int amount)
:   m_pMaterial     (&material)
,   m_numInStack    (amount)
{ }

void ItemStack::add(int amount)
{
    m_numInStack += amount;
    m_numInStack = std::min(m_numInStack, m_pMaterial->maxStackSize);
}

void ItemStack::remove()
{
    m_numInStack--;
}

int ItemStack::getNumInStack() const
{
    return m_numInStack;
}

const Material& ItemStack::getMaterial() const
{
    return *m_pMaterial;
}
