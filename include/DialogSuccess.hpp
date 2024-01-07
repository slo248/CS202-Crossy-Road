#ifndef DIALOG_SUCCESS_HPP
#define DIALOG_SUCCESS_HPP

#include "Dialog.hpp"
#include "Button.hpp"

class DialogSuccess : public Dialog {
    public:
    DialogSuccess(const sf::Texture& texture, State::Context& context);

    private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void handleEvent(const sf::Event& event);

    private:
    Button::Ptr mButtonOK;
};

#endif
