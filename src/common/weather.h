//
// Created by František Gič on 11/12/2019.
//


#ifndef DYNABLASTER3D_WEATHER_H
#define DYNABLASTER3D_WEATHER_H

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

#include <bin/ppgso/lib/ppgso.h>
#include "../objects/object.h"

using namespace std;
using namespace ppgso;

class Scene;

class Weather {

private:
    bool raining = false;
    Scene *scene;
    
    class RainParticle final : public Object {
        
        static unique_ptr<Mesh> mesh;
        static unique_ptr<Shader> shader;
        static unique_ptr<Texture> texture;
    private:
        Weather *parent;
        vec3 speed = {0, -3.0f, 0};
    
    public:
        RainParticle (vec3 position, Weather *parent);
        
        bool update (Scene &scene, float dt) override;
        
        void render (Scene &scene) override;
        
    };

public:
    float wind = 0.0f;
    
    explicit Weather (Scene *scene);
    
    void update ();
    
    void toggleRain ();
};


#endif //DYNABLASTER3D_WEATHER_H
