#version 330

in vec2 fragTexCoord; // Texture coordinates passed from vertex shader
in vec3 fragNormal;   // Normal passed from vertex shader
in vec3 fragPosition; // Fragment position in world space

out vec4 finalColor; // Output color of the fragment

uniform sampler2D texture0; // Texture sampler
uniform vec4 colDiffuse; // Diffuse color
uniform vec3 lightPosition; // Light position in world space
uniform vec4 lightColor; // Light color

void main()
{
    // Normalize the normal vector
    vec3 norm = normalize(fragNormal);
    
    // Calculate light direction
    vec3 lightDir = normalize(lightPosition - fragPosition);
    
    // Calculate the diffuse component
    float diff = max(dot(norm, lightDir), 0.0);
    
    // Sample the texture
    vec4 texColor = texture(texture0, fragTexCoord);
    
    // Calculate the final color
    vec4 finalTexColor = texColor * colDiffuse;
    finalColor = finalTexColor * diff * lightColor;

    // Ensure the output color is between 0 and 1
    finalColor.a = texColor.a; // Use the texture's alpha for transparency
}
