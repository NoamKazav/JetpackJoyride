#include "GameState.h"
#include "Menus/Menu.h" 
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Utils/GameConstants.h"

class InstructionsState : public GameState {
public:
    InstructionsState();

    void enter(Controller& controller) override;
    std::unique_ptr<GameState> handleInput(const sf::Event& event) override;
    std::unique_ptr<GameState> update(float, Controller& controller) override;
    void render(sf::RenderWindow& window) override;
    bool isFinished() const override { return false; }

    Controller* getController() { return m_controller; }
    size_t getCurrentSlideIndex() const { return m_currentSlideIndex; }
    void setCurrentSlideIndex(size_t index) { m_currentSlideIndex = index; }
    size_t getSlideCount() const { return m_slideNames.size(); }
    void loadSlide(); 
    void updateSlideAndButtons();
private:

    const std::vector<std::string>& m_slideNames = GameConstants::HELP_SLIDES;
    size_t m_currentSlideIndex = 0;

    sf::Sprite m_slideSprite;
    Menu m_menu;
    Controller* m_controller = nullptr;
    static bool m_registerit;
};
