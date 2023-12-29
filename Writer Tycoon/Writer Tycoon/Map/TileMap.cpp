#include "../stdafx.h"
#include "TileMap.h"

// Private Functions
void TileMap::clear()
{
	for (int x = 0; x < this->maxSizeGrid.x; ++x)
	{
		for (int y = 0; y < this->maxSizeGrid.y; ++y)
		{
			for (int z = 0; z < this->layers; ++z)
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
TileMap::TileMap(float gridSize, int width, int height, std::string textureFilePath)
{
	// Set variables
	this->gridSizeF = gridSize;
	this->gridSizeI = static_cast<unsigned int>(this->gridSizeF);
	this->maxSizeGrid.x = width;
	this->maxSizeGrid.y = height;
	this->maxSizeWorld.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorld.y = static_cast<float>(height) * gridSize;
	this->layers = 2;
	this->textureFilePath = textureFilePath;
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	// Create collision box
	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineThickness(1.0f);
	this->collisionBox.setOutlineColor(sf::Color::Red);

	// Resize the x vector and fill it with objects
	this->map.resize(this->maxSizeGrid.x, std::vector<std::vector<Tile*>>());
	for (size_t x = 0; x < this->maxSizeGrid.x; ++x)
	{
		for (size_t y = 0; y < this->maxSizeGrid.y; ++y)
		{
			// Resize the y vectors and fill them with objects
			this->map[x].resize(this->maxSizeGrid.y, std::vector<Tile*>());
			
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
		std::cout << this->textureFilePath << "\n";
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
		outFile << this->maxSizeGrid.x << " " << this->maxSizeGrid.y << "\n"
			<< this->gridSizeI << "\n"
			<< this->layers << "\n"
			<< this->textureFilePath << "\n";

		for (size_t x = 0; x < this->maxSizeGrid.x; ++x)
		{
			for (size_t y = 0; y < this->maxSizeGrid.y; ++y)
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
		int gridSize = 0;
		int layers = 0;
		std::string textureFile;

		// Tile
		int x = 0;
		int y = 0;
		int z = 0;
		int textureRectX = 0;
		int textureRectY = 0;
		bool collision = false;
		short int type = 0;

		// Add in variables
		inFile >> size.x >> size.y >> gridSize >> layers >> textureFile;

		// Set variables
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeI = gridSize;
		this->maxSizeGrid.x = size.x;
		this->maxSizeGrid.y = size.y;
		this->layers = layers;
		this->textureFilePath = textureFile;

		// Clear the tile map
		this->clear();

		// Resize the x vector and fill it with objects
		this->map.resize(this->maxSizeGrid.x, std::vector<std::vector<Tile*>>());
		for (size_t x = 0; x < this->maxSizeGrid.x; ++x)
		{
			for (size_t y = 0; y < this->maxSizeGrid.y; ++y)
			{
				// Resize the y vectors and fill them with objects
				this->map[x].resize(this->maxSizeGrid.y, std::vector<Tile*>());

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
				sf::IntRect(textureRectX, textureRectY, this->gridSizeI, this->gridSizeI),
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

void TileMap::addTile(const sf::IntRect& textureRect, const int x, const int y,
	const int z, const bool& collision, const short int& type)
{
	// Check if the given coordinates are within the grid bounds
	if (x < this->maxSizeGrid.x && x >= 0
		&& y < maxSizeGrid.y && y >= 0
		&& z < this->layers && z >= 0)
	{
		// Check if the tile can be added into the space
		if (this->map[x][y][z] == nullptr)
		{
			this->map[x][y][z] = new Tile(x, y, 
				this->gridSizeF, this->tileSheet, textureRect,
				collision, type);
		}
	}
}

void TileMap::removeTile(const int x, const int y, const int z)
{
	if (x < this->maxSizeGrid.x && x >= 0
		&& y < maxSizeGrid.y && y >= 0
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

void TileMap::cullTiles(Entity* entity)
{
	// Set the FromX position and keep within bounds
	this->fromX = entity->getGridPosition(this->gridSizeI).x - 1;
	if (this->fromX < 0)
	{
		this->fromX = 0;
	}
	else if (this->fromX > this->maxSizeGrid.x)
	{
		this->fromX = this->maxSizeGrid.x;
	}

	// Set the ToX position and keep within bounds
	this->toX = entity->getGridPosition(this->gridSizeI).x + 3;
	if (this->toX < 0)
	{
		this->toX = 0;
	}
	else if (this->toX > this->maxSizeGrid.x)
	{
		this->toX = this->maxSizeGrid.x;
	}

	// Set the FromY position and keep within bounds
	this->fromY = entity->getGridPosition(this->gridSizeI).y - 1;
	if (this->fromY < 0)
	{
		this->fromY = 0;
	}
	else if (this->fromY > this->maxSizeGrid.y)
	{
		this->fromY = this->maxSizeGrid.y;
	}

	// Set the ToY position and keep within bounds
	this->toY = entity->getGridPosition(this->gridSizeI).y + 3;
	if (this->toY < 0)
	{
		this->toY = 0;
	}
	else if (this->toY > this->maxSizeGrid.y)
	{
		this->toY = this->maxSizeGrid.y;
	}
}

void TileMap::updateCollision(const float& dt, Entity* entity)
{
	this->layer = 0;

	// Keep entities within the world bounds
	if (entity->getPosition().x < 0.0f)
	{
		// Set the position of the entity
		entity->setPosition(0.0f, entity->getPosition().y);

		// Stop the entity's x-velocity
		entity->setVelocity(0.0f, entity->getVelocity().y);
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width  > this->maxSizeWorld.x)
	{
		// Set the position of the entity
		entity->setPosition(
			this->maxSizeWorld.x - entity->getGlobalBounds().width,
			entity->getPosition().y
		);

		// Stop the entity's x-velocity
		entity->setVelocity(0.0f, entity->getVelocity().y);
	}

	if (entity->getPosition().y < 0.0f)
	{
		// Set the position of the entity
		entity->setPosition(entity->getPosition().x, 0.0f);

		// Stop the entity's y-velocity
		entity->setVelocity(entity->getVelocity().x, 0.0f);
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorld.y)
	{
		// Set the position of the entity
		entity->setPosition(
			entity->getPosition().x, 
			this->maxSizeWorld.y - entity->getGlobalBounds().height
		);

		// Stop the entity's y-velocity
		entity->setVelocity(entity->getVelocity().x, 0.0f);
	}

	// Cull tiles
	this->cullTiles(entity);

	// Loop through the culled tiles
	for (int x = this->fromX; x < this->toX; ++x)
	{
		for (int y = this->fromY; y < this->toY; ++y)
		{
			// Get bounds
			sf::FloatRect playerBounds = entity->getGlobalBounds();
			sf::FloatRect wallBounds = this->map[x][y][this->layer]->getGlobalBounds();
			sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

			// Check if the tile exists
			if (this->map[x][y][this->layer] != nullptr)
			{
				// Check if the tile intersects the entity
				if (this->map[x][y][this->layer]->getCollision()
					&& this->map[x][y][this->layer]->intersects(nextPositionBounds))
				{
					sf::FloatRect collisionBox = RectUtils::getIntersect(playerBounds, wallBounds);

					// If the width is less than or equal to the height, then the character is colliding through the side
					if (collisionBox.width <= collisionBox.height)
					{
						// Check if the difference between the colliding boxes is greater than 0,
						// that means the collider is to the right of the player - so move left
						if (wallBounds.left - playerBounds.left > 0)
						{
							entity->setVelocity(0.0f, entity->getVelocity().y);
							entity->setPosition(playerBounds.left - collisionBox.width, playerBounds.top);
						}
						// Otherwise, the player is to the left of the collider, so move right
						else if (wallBounds.left - playerBounds.left < 0)
						{
							entity->setVelocity(0.0f, entity->getVelocity().y);
							entity->setPosition(playerBounds.left + collisionBox.width, playerBounds.top);
						}
					}
					// If the height is less than the width, then the character is colliding through the top
					else if (collisionBox.height < collisionBox.width)
					{
						// Check if the difference between the colliding boxes is less than 0,
						// that means the collider is above the player - so move down
						if (wallBounds.top - playerBounds.top < 0)
						{
							entity->setVelocity(entity->getVelocity().x, 0.0f);
							entity->setPosition(playerBounds.left, playerBounds.top + collisionBox.height);
						}
						// Otherwise, the player is above the collider, so move up
						else if (wallBounds.top - playerBounds.top > 0)
						{
							entity->setVelocity(entity->getVelocity().x, 0.0f);
							entity->setPosition(playerBounds.left, playerBounds.top - collisionBox.height);
						}
					}
				}
			}
		}
	}
}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target, Entity* entity)
{
	// Check if an entity is given
	if (entity != nullptr)
	{
		// Draw the tiles around the entity that are not culled
		this->layer = 0;

		// Cull tiles
		this->cullTiles(entity);

		// Loop through the culled tiles
		for (int x = this->fromX; x < this->toX; ++x)
		{
			for (int y = this->fromY; y < this->toY; ++y)
			{
				// Check if the tile exists
				if (this->map[x][y][this->layer] != nullptr)
				{
					this->map[x][y][this->layer]->render(target);
					if (this->map[x][y][this->layer]->getCollision())
					{
						this->collisionBox.setPosition(this->map[x][y][this->layer]->getPosition());
						target.draw(this->collisionBox);
					}
				}
			}
		}
	}
	else
	{
		for (auto& x : this->map)
		{
			for (auto& y : x)
			{
				for (auto* z : y)
				{
					// Check if z is a nullptr
					if (z != nullptr)
					{
						// Render the tile
						z->render(target);

						// Render collisions
						if (z->getCollision())
						{
							this->collisionBox.setPosition(z->getPosition());
							target.draw(this->collisionBox);
						}
					}
				}
			}
		}
	}
}
