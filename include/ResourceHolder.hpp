#ifndef RESOURCE_HOLDER_HPP
#define RESOURCE_HOLDER_HPP

#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

template <typename Resource, typename Identifier>
class ResourceHolder {
   public:
    void loadTextureFromFile();
    void loadFontFromFile();
    void loadSoundBufferFromFile();
    void load(Identifier id, const std::string& filename);

    template <typename Parameter>
    void load(
        Identifier id, const std::string& filename, const Parameter& secondParam
    );

    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;

   private:
    void insertResource(Identifier id, std::unique_ptr<Resource> resource);

   private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "ResourceHolder.inl"
#include "ResourceLoad.inl"
#endif  // RESOURCE_HOLDER_HPP
