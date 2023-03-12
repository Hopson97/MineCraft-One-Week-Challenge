#include "BlockType.h"

/// @brief Reads block data from an existing file.
/// @param fileName 
BlockType::BlockType(const std::string &fileName)
    : m_data(fileName)
{
}

const BlockData &BlockType::getData() const
{
    return m_data;
}
