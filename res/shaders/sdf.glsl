#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 worldPos;

void main()
{
  worldPos = vec3(model * vec4(aPos, 1.0));
  gl_Position = projection * view * vec4(worldPos, 1.0);
}

#shader fragment
#version 330 core
in vec3 worldPos;
out vec4 FragColor;

uniform vec3 cameraPos;
uniform vec3 sphereCenter;
uniform float sphereRadius;
uniform mat4 view;
uniform mat4 projection;

float sdSphere(vec3 p, vec3 center, float radius)
{
    return length(p - center) - radius;
}

vec3 calcNormal(vec3 p)
{
    const float eps = 0.001;
    vec2 h = vec2(eps, 0.0);
    return normalize(vec3(
        sdSphere(p + h.xyy, sphereCenter, sphereRadius) - sdSphere(p - h.xyy, sphereCenter, sphereRadius),
        sdSphere(p + h.yxy, sphereCenter, sphereRadius) - sdSphere(p - h.yxy, sphereCenter, sphereRadius),
        sdSphere(p + h.yyx, sphereCenter, sphereRadius) - sdSphere(p - h.yyx, sphereCenter, sphereRadius)
    ));
}

void main()
{
    vec3 rayDir = normalize(worldPos - cameraPos);
    vec3 rayOrigin = cameraPos;
    
    float t = 0.1;
    bool hit = false;
    vec3 hitPos;
    
    for (int i = 0; i < 128; i++)
    {
        vec3 p = rayOrigin + rayDir * t;
        float d = sdSphere(p, sphereCenter, sphereRadius);
        
        if (d < 0.001)
        {
            hit = true;
            hitPos = p;
            break;
        }
        
        if (t > 20.0)
            break;
            
        t += d;
    }
    
    if (!hit)
        discard;
    
    // Calculate lighting
    vec3 normal = calcNormal(hitPos);
    vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));
    
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 color = vec3(0.2, 0.6, 0.8) * (0.3 + 0.7 * diff);
    
    FragColor = vec4(color, 1.0);
    
    // Write depth
    vec4 clipSpacePos = projection * view * vec4(hitPos, 1.0);
    float ndcDepth = clipSpacePos.z / clipSpacePos.w;
    gl_FragDepth = (ndcDepth + 1.0) * 0.5;
}
