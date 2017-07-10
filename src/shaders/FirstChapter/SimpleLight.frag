#version 330 core
struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform float time;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;

vec3 interpolate(vec3 a, vec3 b, float c){
    //c = abs(normalize(c));
    float d = 1. - c;
    return normalize(a * c + b * d);
}

vec3 interpolate3(vec3 a, vec3 b, vec3 c, float d){
    if(d > 0.5){
        return interpolate(c, b, (d - 0.5) * 2.);
    }
    else{
        return interpolate(b, a, d * 2.);
    }
}

float triangleFunc(float x){
    if(sin(x) < 0.)
        return 1. - abs(x - floor(x));
    return abs(x - floor(x));
}

void main()
{
    // ambient
    vec3 ambient = material.ambient * lightColor;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (diff * material.diffuse) * lightColor;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec * lightColor;  

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}