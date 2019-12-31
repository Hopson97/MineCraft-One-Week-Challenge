#ifndef CHUNKSHADER_H_INCLUDED
#define CHUNKSHADER_H_INCLUDED

#include "BasicShader.h"

class ChunkShader : public BasicShader {
  public:
    ChunkShader();

  private:
    void getUniforms() override;
};

#endif // CHUNKSHADER_H_INCLUDED
