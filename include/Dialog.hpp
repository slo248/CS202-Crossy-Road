#include "Component.hpp"

namespace GUI {

class Dialog : public Component {
   public:
    typedef std::shared_ptr<Dialog> Ptr;

    Dialog(
        const sf::Font& font, const std::string& message,
        const sf::Vector2f& positionMessage
    );
    virtual bool isSelectable() const override { return false; }

    virtual void handleEvent(const sf::Event& event) override {}

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states);

   private:
    sf::RectangleShape backgroundBox;
    sf::Text messageText;
};

}  // namespace GUI
