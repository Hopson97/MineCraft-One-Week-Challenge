#include "BlockDB.h"

BlockDB::BlockDB()
:   textureAtlas    ("DefaultPack")
{
    // Air
    Block block_air = {false, false, false, 0, 0, static_cast<BlockMeshType>(0), static_cast<BlockShaderType>(0), "Air", {0, 0}, {0, 0}, {0, 0}};
    blocks.push_back(block_air);
    id_block_rel.emplace(block_air.id, 0);
    name_block_rel.emplace(block_air.name, 0);

    // Water
    Block block_water = {false, false, false, 1, 0, static_cast<BlockMeshType>(0), static_cast<BlockShaderType>(1), "Water", {8, 0}, {8, 0}, {8, 0}};
    blocks.push_back(block_water);
    id_block_rel.emplace(block_water.id, 1);
    name_block_rel.emplace(block_water.name, 1);

    // Nothing
    Block block_nothing = {false, false, false, 2, 0, static_cast<BlockMeshType>(0), static_cast<BlockShaderType>(0), "Nothing", {0, 0}, {0, 0}, {0, 0}};
    blocks.push_back(block_nothing);
    id_block_rel.emplace(block_nothing.id, 2);
    name_block_rel.emplace(block_nothing.name, 2);

    Load("./Res/Blocks/BlockDB.csv");
}

void BlockDB::Load(std::string filename) {
	CsvLoader::LoadFromFile(filename, 14, [&](std::vector<std::string> values) {
		unsigned meshtype = 0, shadertype = 0, texture1 = 0, texture2 = 0;
		Block block;

		// ID
		block.id = std::stoul(values[0]);

		// Name
		block.name = values[1];

		// Description
		// block.description = values[2];

		// If it is a block
		block.isBlock = std::stoul(values[2]);

		// Opaqueness
		block.isOpaque = std::stoul(values[3]);

		// Collidable
		block.isCollidable = std::stoul(values[4]);

		// Stacksize
		block.maxStackSize = std::stoul(values[5]);

		// Top Texture
		texture1 = std::stoul(values[6]);
		texture2 = std::stoul(values[7]);
		block.texTopCoord = {texture1, texture2};

		// Side Texture
		texture1 = std::stoul(values[8]);
		texture2 = std::stoul(values[9]);
		block.texSideCoord = {texture1, texture2};

		// Bottom Texture
		texture1 = std::stoul(values[10]);
		texture2 = std::stoul(values[11]);
		block.texBottomCoord = {texture1, texture2};

		// Mesh
		meshtype = std::stoul(values[12]);
		block.meshType = static_cast<BlockMeshType>(meshtype);

		// Shader
		shadertype = std::stoul(values[13]);
		block.shaderType = static_cast<BlockShaderType>(shadertype);

		blocks.push_back(block);
		unsigned new_pos = blocks.size() - 1;
		id_block_rel.emplace(block.id, new_pos);
		name_block_rel.emplace(block.name, new_pos);
	});
}

Block& BlockDB::operator[](std::string name) {

    Block& res = blocks[name_block_rel[name]];

	return res;
}

Block& BlockDB::operator[](unsigned id) {
	return blocks[id_block_rel.at(id)];
}

BlockDB & BlockDB::get() {
	static BlockDB db;
	return db;
}
