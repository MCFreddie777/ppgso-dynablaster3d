if (game > 0) {
    game = 0;
    auto hra = std::make_unique<Game>();
hra->parent = this;
hra->scale *= 1.5f;
scene.objects.push_back(move(hra));
}

//druhy objekt
modelMatrix = parent->modelMatrix;




void Object::child1(float age) {
    position = {cos(age *2) * 4.8f, 0, sin(age*2) * 4.8f};
    modelMatrix =  modelMatrix *translate(glm::mat4(1.0f), position)
* glm::orientate4(rotation)
* glm::scale(glm::mat4(1.0f), scale);
}


#version 330

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

// A texture is expected as program attribute
uniform sampler2D Texture;

// Direction of light
uniform vec3 LightDirection;

//uniform float ambientStr = 0.5f;

// (optional) Transparency
uniform float Transparency;

// (optional) Texture offset
uniform vec2 TextureOffset;

uniform vec3 DifMaterial;

uniform vec3 viewPos;
uniform vec3 FragPos;
uniform vec3 lightPos;

// The vertex shader will feed this input
in vec2 texCoord;

// Wordspace normal passed from vertex shader
in vec4 normal;

// The final color
out vec4 FragmentColor;

void main() {
    // Compute diffuse lighting
    //  float diffuse = max(dot(normal, vec4(normalize(LightDirection), 1.0f)), 0.0f);

    // Lookup the color in Texture on coordinates given by texCoord
    // NOTE: Texture coordinate is inverted vertically for compatibility with OBJ
    //  FragmentColor = texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset) * diffuse;
    //  FragmentColor.a = Transparency;

    float ambientStr = 0.25f;
    vec3 amb = ambientStr * DifMaterial;
    vec4 ambient = vec4(amb, 1.0);
    //--------
    float diff = max(dot(normal, vec4(normalize(LightDirection), 1.0f)), 0.0);
    vec4 diffuse = vec4(diff * DifMaterial, 1.0);
    //--------
    vec4 norm = normalize(normal);
    vec4 lightDir = vec4(normalize(lightPos - FragPos), 1.0);
    float specularStrength = 0.5;

    vec4 viewDir = vec4(normalize(viewPos - FragPos), 1.0);
    vec4 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec4 specular = vec4(specularStrength * spec * vec3(1, 1, 1), 1.0);
    //--------
    FragmentColor = texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset) * (ambient + diffuse + specular);
    FragmentColor.a = Transparency;
}






------------------------------------------------------------------------------------------------
locA = position;
locB = position;
locC = position;
locB.y += kfHore;
locC.y -= kfDole;


end += dt;

if (end < time1) {
    part = end / time1;
    keyFrame(locA, locB, {-ppgso::PI / 4, 0, 0}, {0, 0, 0}, part);




glm::mat4 Object::keyFramePart(glm::vec3 locA, glm::vec3 rot) {
return glm::translate(glm::mat4(1.0f), locA)
* glm::orientate4(rot);
}

void Object::keyFrame(glm::vec3 locA, glm::vec3 locB, glm::vec3 rotA, glm::vec3 rotB, float part) {
position =(1 - part) * locA + part * locB;
modelMatrix = (1 - part) * keyFramePart(locA, rotA)
+ part * keyFramePart(locB, rotB);
}