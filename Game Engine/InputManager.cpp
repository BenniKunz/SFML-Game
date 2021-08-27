#include "InputManager.h"

namespace Engine
{
    bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window, bool previous, bool current)
    {
        
        if (previous && !current)
        {
            sf::IntRect rect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

            if (rect.contains(sf::Mouse::getPosition(window)))
            {
                return true;
            }

        }
        return false;
    }

    bool InputManager::IsSpriteHovered(sf::Sprite object, sf::RenderWindow& window)
    {
        sf::IntRect rect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

        if (rect.contains(sf::Mouse::getPosition(window)))
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


