#include "Animation.h"


namespace Engine
{
   

    Animation::Animation(std::string textureName, int rowCount, int columnCount, GameData& data, sf::Vector2f position)
        :_textureName{ textureName }, _rowCount{ rowCount }, _columnCount{ columnCount }, _data{ data }, _position{ position }, _frameSpeed{ 0.1f }
    {
        this->_texture.setTexture(this->_data.assets.GetTexture(_textureName));
        this->_texture.setPosition(_position.x, _position.y);
        
    }

    int Animation::GetFrameHeight()
    {
        return this->_texture.getGlobalBounds().height / this->_rowCount;

    }

    int Animation::GetFrameWidth()
    {

        return this->_texture.getGlobalBounds().width / this->_columnCount;
    }

    float Animation::GetFrameSpeed()
    {
        return this->_frameSpeed;
    }

    int Animation::GetCurrentColumn()
    {
        return this->_currentColumn;
    }

    int Animation::GetCurrentRow()
    {
        return this->_currentRow;
    }

    void Animation::CurrentColumnPlusOne()
    {
        this->_currentColumn++;
    }

    void Animation::SetCurrentColumnToZero()
    {
        this->_currentColumn = 0;
    }

    void Animation::CurrentRowPlusOne()
    {
        this->_currentRow++;
    }

    void Animation::SetCurrentRowToZero()
    {
        this->_currentRow = 0;
    }

    int Animation::GetColumnCount()
    {
        return this->_columnCount;
    }

    int Animation::GetRowCount()
    {
        return this->_rowCount;
    }
}

