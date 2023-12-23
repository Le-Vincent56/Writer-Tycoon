#include "../stdafx.h"
#include "TileMap.h"

// Private Functions
void TileMap::clear()
{
	for (size_t x = 0; x < this->maxSize.x; ++x)
	{
		for (size_t y = 0; y < this->maxSize.y; ++y)
		{
			for (size_t z = 0; z < this->layers; ++z)
			{
				delete this->map[x][y][z];
				this->map[x][y][z] = nullptr;
			}

			this->map[x][y].clear();
		}

		this->map[x].clear();
	}

	this->map.clear();
}

// Constructor/Destructor
TileMap::TileMap(float gridSize, unsigned int width, unsigned int height, std::string textureFilePath)
{
	// Set variables
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned int>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 2;
	this->textureFilePath = textureFilePath;

	// Resize the x vector and fill it with objects
	this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());
	for (size_t x = 0; x < this->maxSize.x; ++x)
	{
		for (size_t y = 0; y < this->maxSize.y; ++y)
		{
			// Resize the y vectors and fill them with objects
			this->map[x].resize(this->maxSize.y, std::vector<Tile*>());
			
			for (size_t z = 0; z < this->layers; ++z)
			{
				// Resize the z vectors and fill them with nullptr
				this->map[x][y].resize(this->layers, nullptr);
			}
		}
	}

	// Check if the texture sheet loading was successful
	if (!this->tileSheet.loadFromFile(this->textureFilePath))
	{
		throw("ERROR::TILEMAP::FAILED_TO_LOAD_TILESHEET::FILENAME:" + textureFilePath + "\n");
	}
}

TileMap::~TileMap()
{
	// Clear the tile map
	this->clear();
}

// Accessors
const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

// Functions
void TileMap::saveToFile(const std::string fileName)
{
	// Format:
	// -- Basics
	// Size x y
	// Gridsize
	// Layers
	// Texture File
	// -- All tiles
	// GridPos x y, Texture rect x y,, collision, type

	// Attempt to open the file
	std::ofstream outFile;
	outFile.open(fileName);

	// CHeck if the opening is successful
	if (outFile.is_open())
	{
		outFile << this->maxSize.x << " " << this->maxSize.y << "\n"
			<< this->gridSizeU << "\n"
			<< this->layers << "\n"
			<< this->textureFilePath << "\n";

		for (size_t x = 0; x < this->maxSize.x; ++x)
		{
			for (size_t y = 0; y < this->maxSize.y; ++y)
			{
				for (size_t z = 0; z < this->layers; ++z)
				{
					// Check if nullptr
					if (this->map[x][y][z] != nullptr)
					{
						outFile << x << " " << y << " " << z 
							<< " " << this->map[x][y][z]->toString() << " ";
					}
				}
			}
		}
	}
	else
	{
		throw("ERROR::TILEMAP::COULD_NOT_SAVE_TO_FILE::FILENAME:" + fileName + "\n");
	}

	// Close the file
	outFile.close();
}

void TileMap::loadFromFile(const std::string fileName)
{
	// Format:
	// -- Basics
	// Size x y
	// Gridsize
	// Layers
	// Texture File
	// -- All tiles
	// GridPos x y layer, Texture rect x y, collision, type

	// Attempt to open the file
	std::ifstream inFile;
	inFile.open(fileName);

	// CHeck if the opening is successful
	if (inFile.is_open())
	{
		// General
		sf::Vector2u size;
		unsigned int gridSize = 0;
		unsigned int layers = 0;
		std::string textureFile;

		// Tile
		unsigned int x = 0;
		unsigned int y = 0;
		unsigned int z = 0;
		unsigned int textureRectX = 0;
		unsigned int textureRectY = 0;
		bool collision = false;
		short int type = 0;

		// Add in variables
		inFile >> size.x >> size.y >> gridSize >> layers >> textureFile;

		// Set variables
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeU = gridSize;
		this->maxSize.x = size.x;
		this->maxSize.y = size.y;
		this->layers = layers;
		this->textureFilePath = textureFile;

		// Clear the tile map
		this->clear();

		// Resize the x vector and fill it with objects
		this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());
		for (size_t x = 0; x < this->maxSize.x; ++x)
		{
			for (size_t y = 0; y < this->maxSize.y; ++y)
			{
				// Resize the y vectors and fill them with objects
				this->map[x].resize(this->maxSize.y, std::vector<Tile*>());

				for (size_t z = 0; z < this->layers; ++z)
				{
					// Resize the z vectors and fill them with nullptr
					this->map[x][y].resize(this->layers, nullptr);
				}
			}
		}

		// Check if the texture sheet loading was successful
		if (!this->tileSheet.loadFromFile(this->textureFilePath))
		{
			throw("ERROR::TILEMAP::FAILED_TO_LOAD_TILESHEET::FILENAME:" + textureFilePath + "\n");
		}

		// Load all tiles
		while (inFile >> x >> y >> z >> textureRectX >> textureRectY >> collision >> type)
		{
			// Add the new tile
			this->map[x][y][z] = new Tile(
				x, y, this->gridSizeF, this->tileSheet, 
				sf::IntRect(textureRectX, textureRectY, this->gridSizeU, this->gridSizeU),
				collision, type
			);
		}
	}
	else
	{
		throw("ERROR::TILEMAP::COULD_NOT_LOAD_TO_FILE::FILENAME:" + fileName + "\n");
	}

	// Close the file
	inFile.close();
}

void TileMap::addTile(const sf::IntRect& textureRect, const unsigned int x, const unsigned int y,
	const unsigned int z)
{
	// Check if the given coordinates are within the grid bounds
	if (x < this->maxSize.x && x >= 0 
		&& y < maxSize.y && y >= 0
		&& z < this->layers && z >= 0)
	{
		// Check if the tile can be added into the space
		if (this->map[x][y][z] == nullptr)
		{
			this->map[x][y][z] = new Tile(x, y, 
				this->gridSizeF, this->tileSheet, textureRect);
		}
	}
}

void TileMap::removeTile(const unsigned int x, const unsigned int y, const unsigned int z)
{
	if (x < this->maxSize.x && x >= 0
		&& y < maxSize.y && y >= 0
		&& z < this->layers && z >= 0)
	{
		// Check if the tile can be added into the space
		if (this->map[x][y][z] != nullptr)
		{
			delete this->map[x][y][z];
			this->map[x][y][z] = nullptr;
		}
	}
}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto &x : this->map)
	{
		for (auto &y : x)
		{
			for (auto* z : y)
			{
				// Check if z is a nullptr
				if(z != nullptr)
					z->render(target);
			}
		}
	}
}
