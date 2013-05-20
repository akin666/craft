{
    "shader": [
        {
            "type": "vertex",
            "name": "simple_vs",
            "level": 0,
            "data": [
                "#version 400 // GL 4.0",
                "precision mediump float;",
                "layout(location=0) in vec4 vertex;",
                "uniform mat4 projectionMatrix;",
                "uniform mat4 modelMatrix;",
                "uniform mat4 viewMatrix;",
                "void main(void)",
                "{",
                "   gl_Position = projectionMatrix * viewMatrix * modelMatrix * vertex;",
                "}"
            ],
            "uniform": {
                "projectionMatrix": "mat4",
                "modelMatrix": "mat4",
                "viewMatrix": "mat4"
            },
            "attribute": {
                "vertex": "vec4"
            }
        },
        {
            "type": "fragment",
            "name": "simple_fs",
            "level": 0,
            "data": [
                "#version 400 // GL 4.0",
                "precision mediump float;",
                "out vec4 out_Color;",
                "void main(void)",
                "{",
                "   out_Color = vec4( 1.0 , 0.5 , 0.25 , 1.0 );",
                "}"
            ]
        }
    ],
    "program": [
        {
            "name": "simple",
            "component": [
                "simple_vs",
                "simple_fs"
            ]
        }
    ]
}