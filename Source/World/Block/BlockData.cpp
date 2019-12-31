#include "BlockData.h"

#include <fstream>

BlockData::BlockData(const std::string &fileName)
{
    std::ifstream inFile("Res/Blocks/" + fileName + ".block");

    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open block file: " + fileName +
                                 "!");
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (line == "TexTop") {
            int x, y;
            inFile >> x >> y;
            m_data.texTopCoord = {x, y};
        }
        else if (line == "TexSide") {
            int x, y;
            inFile >> x >> y;
            m_data.texSideCoord = {x, y};
        }
        else if (line == "TexBottom") {
            int x, y;
            inFile >> x >> y;
            m_data.texBottomCoord = {x, y};
        }
        else if (line == "TexAll") {
            int x, y;
            inFile >> x >> y;
            m_data.texTopCoord = {x, y};
            m_data.texSideCoord = {x, y};
            m_data.texBottomCoord = {x, y};
        }
        else if (line == "Id") {
            int id;
            inFile >> id;
            m_data.id = static_cast<BlockId>(id);
        }
        else if (line == "Opaque") {
            inFile >> m_data.isOpaque;
        }
        else if (line == "Collidable") {
            inFile >> m_data.isCollidable;
        }
        else if (line == "MeshType") {
            int id;
            inFile >> id;
            m_data.meshType = static_cast<BlockMeshType>(id);
        }
        else if (line == "ShaderType") {
            int id;
            inFile >> id;
            m_data.shaderType = static_cast<BlockShaderType>(id);
        }
    }
}

const BlockDataHolder &BlockData::getBlockData() const
{
    return m_data;
}
