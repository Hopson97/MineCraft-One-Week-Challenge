#include "BlockData.h"

#include <fstream>

BlockData::BlockData(const std::string &fileName)
{
    std::ifstream inFile("Res/Blocks/" + fileName + ".block");

    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open block file: " + fileName +
                                 "!");
    }

    /* BlockData parses through text strings and applies valid attributes.

    Textures are applied first, then Block IDs, opacity data, collision data,
    mesh data, and shader data.

    Essentially, blocks being constructed by the renderer depend on this
    file data being correctly imported and read by the program.*/

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
