#version 130

/*
Here you can enable/disable the effects of this shader.
Put "//" in front of the "#define" of the effect you want to disable.
*/

//#define DEBUG_RENDER
#define SHADOWS
#define REFLECTIONS
//#define BLOOM
#define MONOCHROMATIC_RENDER
//#define QUANTIZE_RENDER
#define CUSTOM_TONEMAP

/*
Here you can set the parameters of each effect of this shader.
Change the values at the end of the lines starting with "#define" to do so.
*/

#ifdef DEBUG_RENDER
#define DEBUG_COLOR vec3(1.0)
#endif
#ifdef SHADOWS
#define SHADOWS_DARKNESS 3.0
#endif
#ifdef REFLECTIONS
#define REFLECTIONS_SMOOTHING 2
#define REFLECTIONS_STRENGTH 0.6
#endif
#ifdef BLOOM
#define BLOOM_OFFSET 0.1
#define BLOOM_RADIUS 2
#define BLOOM_STRENGTH 0.2
#endif
#ifdef QUANTIZE_RENDER
#define QUANTIZE_RATIO 1
#endif
#ifdef CUSTOM_TONEMAP
#define TONEMAP_CONTRAST 3.0
#define TONEMAP_BRIGHTNESS 0.3
#define TONEMAP_SATURATION 0.5
#endif

/* -------------------------------------------------------------------------- */

uniform mat4 worldMatrix;
uniform mat4 invertedWorldMatrix;
uniform mat4 worldViewProjectionMatrix;
uniform vec3 lightPos;
uniform vec4 lightColor;
uniform vec2 screenDimensions;
uniform sampler2D colorSampler;
uniform sampler2D depthSampler;

varying vec2 texCoord;
varying vec3 normalMap;

/* -------------------------------------------------------------------------- */

float mean(in vec2 vector)
{
    return (vector.s + vector.t) / 2.;
}

float mean(in vec3 vector)
{
    return (vector.x + vector.y + vector.z) / 3.;
}

float mean(in vec4 vector)
{
    return (vector.r + vector.g + vector.b + vector.a) / 4.;
}

/* -------------------------------------------------------------------------- */

#ifdef SHADOWS
void apply_basicShadows(inout vec3 colorMap, in float lightStrength)
{
    colorMap = mix(colorMap / SHADOWS_DARKNESS, colorMap, lightStrength);
}
#endif

#ifdef REFLECTIONS
void apply_basicReflections(inout vec3 colorMap, in vec2 fragCoord, in float lightStrength)
{
    colorMap = mix(colorMap, lightColor.rgb, pow(lightStrength * fragCoord.y, REFLECTIONS_SMOOTHING) * REFLECTIONS_STRENGTH);
}
#endif

#ifdef BLOOM
void apply_bloomFilter(inout vec3 colorMap)
{
    float bloomStrength = 0.;

    for (int y = -BLOOM_RADIUS; y < BLOOM_RADIUS; y++)
        for (int x = -BLOOM_RADIUS; x < BLOOM_RADIUS; x++)
            if (mean(texture2D(colorSampler, texCoord + vec2(x, y)).rgb) > BLOOM_OFFSET)
                bloomStrength += 1.;
    bloomStrength /= pow(2 * BLOOM_RADIUS + 1, 2);
    colorMap = mix(colorMap, lightColor.rgb, bloomStrength * BLOOM_STRENGTH);
}
#endif

#ifdef MONOCHROMATIC_RENDER
void apply_monochromaticRender(inout vec3 colorMap)
{
    colorMap = vec3(mean(colorMap));
}
#endif

#ifdef QUANTIZE_RENDER
void apply_quantizeRender(inout vec3 colorMap)
{
    colorMap.r = round(colorMap.r * QUANTIZE_RATIO) / QUANTIZE_RATIO;
    colorMap.g = round(colorMap.g * QUANTIZE_RATIO) / QUANTIZE_RATIO;
    colorMap.b = round(colorMap.b * QUANTIZE_RATIO) / QUANTIZE_RATIO;
}
#endif

#ifdef CUSTOM_TONEMAP
void apply_customTonemap(inout vec3 colorMap)
{
    vec3 contrastedColor = mix(colorMap / TONEMAP_CONTRAST, colorMap * TONEMAP_CONTRAST, colorMap);
    vec3 saturatedColor = vec3(
        pow(2.0 * colorMap.r, TONEMAP_SATURATION) / 2.0,
        pow(2.0 * colorMap.g, TONEMAP_SATURATION) / 2.0,
        pow(2.0 * colorMap.b, TONEMAP_SATURATION) / 2.0
    );

    colorMap = mix(contrastedColor, saturatedColor, 0.5) * TONEMAP_BRIGHTNESS;
}
#endif

/* -------------------------------------------------------------------------- */

void main()
{
#ifndef DEBUG_RENDER
    vec4 colorMap = texture2D(colorSampler, texCoord);
    colorMap.rgb = mix(colorMap.rgb, lightColor.rgb, lightColor.a);
#else
    vec4 colorMap = vec4(DEBUG_COLOR, 1.);
#endif
    vec2 fragCoord = gl_FragCoord.st / screenDimensions;
    float lightStrength = dot(normalize(lightPos), normalMap);

#ifdef SHADOWS
    apply_basicShadows(colorMap.rgb, lightStrength);
#endif
#ifdef REFLECTIONS
    apply_basicReflections(colorMap.rgb, fragCoord, lightStrength);
#endif
#ifdef BLOOM
    apply_bloomFilter(colorMap.rgb);
#endif
#ifdef MONOCHROMATIC_RENDER
    apply_monochromaticRender(colorMap.rgb);
#endif
#ifdef QUANTIZE_RENDER
    apply_quantizeRender(colorMap.rgb);
#endif
#ifdef CUSTOM_TONEMAP
    apply_customTonemap(colorMap.rgb);
#endif
    gl_FragColor = colorMap;
}