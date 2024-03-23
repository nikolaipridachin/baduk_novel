uniform sampler2D main_texture;
uniform sampler2D mask_texture;
uniform float cutoff;
uniform float cutoff_range;

void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(main_texture, gl_TexCoord[0].xy);
    float d = texture2D(mask_texture, gl_TexCoord[0].xy).r;
	// pixel[3] = 0.8f;

    float r = cutoff * (1 + cutoff_range * 2) - cutoff_range;
    pixel[3] = (d - r) * (1 / (cutoff_range));

    // multiply it by the color
    gl_FragColor = gl_Color * pixel;
}