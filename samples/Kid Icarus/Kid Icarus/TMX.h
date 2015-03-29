#pragma once

#include "../externals/pugixml-1.5/src/pugixml.hpp"

#include <string>
#include <vector>

class TMX
{
public:
	class Map
	{
	public:
		class Tileset
		{
		public:
			int firstGID;
			std::string name;
			
			int tileWidth;
			int tileHeight;
			
			std::string imageFilename;
		};
		
		class Layer
		{
		public:
			std::string name;
			
			int width;
			int height;
			
			std::vector<int> tiles;
		};
		
		enum orientation_t {
			ORTHOGONAL
		};
		
		enum renderOrder_t {
			LEFT_DOWN
		};
		
		int width;
		int height;
		
		int tileWidth;
		int tileHeight;
		
		orientation_t orientation;
		renderOrder_t renderOrder;
		
		Tileset tileset;
		Layer layer;
	};
	
	bool Load(const std::string &filename);
	
	Map map;
};
