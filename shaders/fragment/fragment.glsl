#version 330 core
    out vec4 FragColor;
    in vec3 ourColor;
    in vec2 TexCoord;

    uniform sampler2D texture1;
    uniform sampler2D texture2;
    uniform sampler2D texture3;
    uniform int currentTexture;

    void main()
    {
        if (currentTexture == 1)
            FragColor = (texture(texture3, TexCoord));

        else
            FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5f);
    }
