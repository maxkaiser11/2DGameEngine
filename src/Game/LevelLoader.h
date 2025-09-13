//
// Created by User on 13/09/2025.
//

#ifndef INC_2DGAMEENGINE_LEVELLOADER_H
#define INC_2DGAMEENGINE_LEVELLOADER_H
#include "ECS/ECS.h"
#include <memory>
#include <SDL.h>

#include "AssetStore/AssetStore.h"


class LevelLoader
{
public:
    LevelLoader();
    ~LevelLoader();

    void LoadLevel(const std::unique_ptr<Registry>& registry, const std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer, int level);
};


#endif //INC_2DGAMEENGINE_LEVELLOADER_H