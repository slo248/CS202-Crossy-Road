#include "Component.hpp"

using namespace GUI;

Component::Component()
    : mIsSelected(false), mIsActive(true), mIsSelectable(true) {}

void Component::select() { mIsSelected = true; }
void Component::deselect() { mIsSelected = false; }
bool Component::isSelected() const { return mIsSelected; }
bool Component::isActive() const { return mIsActive; }
void Component::isSelectable(bool isSelectable) {
    mIsSelectable = isSelectable;
}
void Component::activate() { mIsActive = true; }
void Component::deactivate() { mIsActive = false; }
