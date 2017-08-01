#include "BlockType.h"

BlockType::BlockType(const std::string& fileName)
:   m_data  (fileName)
{

}

const BlockData& BlockType::getData() const noexcept
{
    return m_data;
}
