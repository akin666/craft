{
    "shader": [
        {
            "type": "vertex",
            "name": "texture_vs",
            "level": 0,
            "data": [
                "#version 400 // GL 4.0",
                "precision mediump float;",
                "layout(location=0) in vec4 vertex;",
                "layout(location=1) in vec2 textureCoordinate;",
                "uniform mat4 projectionMatrix;",
                "uniform mat4 modelMatrix;",
                "uniform mat4 viewMatrix;",
                "out vec2 textureCoordinateInterpolation;",
                "void main(void)",
                "{",
                "   gl_Position = projectionMatrix * viewMatrix * modelMatrix * vertex;",
                "   textureCoordinateInterpolation = textureCoordinate;",
                "}"
            ],
            "out": {
                "textureCoordinateInterpolation": "vec2"
            },
            "uniform": {
                "projectionMatrix": "mat4",
                "modelMatrix": "mat4",
                "viewMatrix": "mat4"
            },
            "attribute": {
                "vertex": "vec4",
                "textureCoordinate": "vec2"
            }
        },
        {
            "type": "fragment",
            "name": "texture_fs",
            "level": 0,
            "comment":"for some reason, texturecoordinateinterpolation requires highp, othewise shader will error C7011: implicit cast from vec4 to f16vec4r",
            "data": [
                "#version 400 // GL 4.0",
                "precision highp float;",
                "uniform sampler2D texture;",
                "in vec2 textureCoordinateInterpolation;",
                "out vec4 out_Color;",
                "void main(void)",
                "{",
                "   //out_Color = texture2D( texture , textureCoordinateInterpolation );",
                "   out_Color = vec4( textureCoordinateInterpolation , 0.25 , 1.0 );",
                "}"
            ],
            "in": {
                "textureCoordinateInterpolation": "vec2"
            },
            "out": {
                "out_Color": "vec4"
            },
            "uniform": {
                "texture": "sampler2D"
            }
        }
    ],
    "program": [
        {
            "name": "texture",
            "component": [
                "texture_vs",
                "texture_fs"
            ]
        }
    ]
}