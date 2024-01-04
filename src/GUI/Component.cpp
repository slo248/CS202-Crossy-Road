#include "Component.hpp"

using namespace GUI;

Component::Component()
    : mIsSelected(false), mIsActive(true), mIsSelectable(true) {}

Component::~Component() {}

bool Component::isSelected() const { return mIsSelected; }

void Component::select() { mIsSelected = true; }

void Component::deselect() { mIsSelected = false; }

bool Component::isActive() const { return mIsActive; }
