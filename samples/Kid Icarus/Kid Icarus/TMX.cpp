#include "TMX.h"

using namespace std;

bool TMX::Load(const std::string &filename)
{
	pugi::xml_document doc;
	doc.load_file(filename.c_str());
	
	auto mapNode = doc.child("map");
	
	map.width      = mapNode.attribute("width").as_int();
	map.height     = mapNode.attribute("height").as_int();
	map.tileWidth  = mapNode.attribute("tilewidth").as_int();
	map.tileHeight = mapNode.attribute("tileheight").as_int();
	
	string orientation = mapNode.attribute("orientation").as_string();
	if (orientation == "orthogonal") map.orientation = Map::orientation_t::ORTHOGONAL;
	
	string renderOrder = mapNode.attribute("renderorder").as_string();
	if (renderOrder == "left-down") map.renderOrder = Map::renderOrder_t::LEFT_DOWN;
	
	auto tilesetNode = mapNode.child("tileset");
	map.tileset.firstGID   = tilesetNode.attribute("firstgid").as_int();
	map.tileset.name       = tilesetNode.attribute("name").as_string();
	map.tileset.tileWidth  = tilesetNode.attribute("tilewidth").as_int();
	map.tileset.tileHeight = tilesetNode.attribute("tileheight").as_int();
	
	auto imageNode = tilesetNode.child("image");
	map.tileset.imageFilename = imageNode.attribute("source").as_string();
	
	auto layerNode = mapNode.child("layer");
	map.layer.name   = layerNode.attribute("name").as_string();
	map.layer.width  = layerNode.attribute("width").as_int();
	map.layer.height = layerNode.attribute("height").as_int();
	
	auto layerData = layerNode.child("data");
	auto tileNode = layerData.child("tile");
	
	map.layer.tiles.reserve(map.layer.width * map.layer.height);
	
	while (tileNode) {
		map.layer.tiles.push_back(tileNode.attribute("gid").as_int());
		tileNode = tileNode.next_sibling("tile");
	}
	
	return true;
}

