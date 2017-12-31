#ifndef BLOCKDB_H
#define BLOCKDB_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>

#include "Block.h"
#include "../../Util/Singleton.h"
#include "../../Util/CsvLoader.h"
#include "../../Texture/TextureAtlas.h"

// Handles all block types
class BlockDB : public Singleton {
public:

	static BlockDB& get();
	void Load(std::string filename);

	TextureAtlas textureAtlas;

	Block& operator[](std::string name);
	Block& operator[](unsigned id);

private:

    BlockDB();

	// dynamic storage for moddability
	std::vector<Block> blocks;
	// hashmap for faster named access
	std::unordered_map<std::string, unsigned> name_block_rel;
	// hashmap for faster id access
	std::unordered_map<unsigned, unsigned> id_block_rel;

};
#endif // !BLOCKDB_H
