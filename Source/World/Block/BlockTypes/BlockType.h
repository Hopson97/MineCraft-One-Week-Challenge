#ifndef BLOCKTYPE_H_INCLUDED
#define BLOCKTYPE_H_INCLUDED

#include "../BlockData.h"

class BlockType : public NonCopyable {
  public:
    BlockType(const std::string &fileName);
    virtual ~BlockType() = default;

    const BlockData &getData() const;

  private:
    BlockData m_data;
};

class DefaultBlock : public BlockType {
  public:
    DefaultBlock(const std::string &fileName)
        : BlockType(fileName)
    {
    }
};

#endif // BLOCKTYPE_H_INCLUDED
