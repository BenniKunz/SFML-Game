#include "InputManager.h"

namespace Engine
{
    bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window, bool previous, bool current)
    {
        
        if (previous && !current)
        {
            sf::IntRect rect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

            if (rect.contains(worldPos.x,worldPos.y))
            {
                return true;
            }

        }
        return false;
    }

    bool InputManager::IsSpriteHovered(sf::Sprite object, sf::RenderWindow& window)
    {
        sf::IntRect rect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

        if (rect.contains(worldPos.x, worldPos.y))
        {
            return true;
        }

        return false;
    }

    sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window)
    {
        return sf::Mouse::getPosition(window);
    }
}


