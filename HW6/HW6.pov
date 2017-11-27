// Diego Adolfo José Villa - A00815260
// Computer Graphics
// POV - Good Enough Clouds
// Based on the tutorial: Quick and dirty Good Enough Clouds by Mike Kost

global_settings {
    max_trace_level 10
    adc_bailout 1/255
}

camera {
    angle 65
    location <0,2,4.5>
    look_at <.5,2,-0.75>
}

sky_sphere {
   pigment { color rgb <2.5, 2, 30>   }
}

light_source { <800,1500,0> color rgb 0.45 }

#declare Cloud = pigment {
    wrinkles
    turbulence <0.55, 0.55, 0.55>
    octaves    7
    omega      0.75
    lambda     3
    color_map {
        [0.45 color rgbt <1.00,1.00,1.00, 1.00>]
        [0.55 color rgbt <0.75,0.75,0.75,0.50>]
    }
    scale <1200,1000,1000>
}

union {
    plane {
        <0, -1, 0> 0
        texture {
            pigment { Cloud }
            finish { ambient 0.2 }
        }
    }

    plane {
        <0, -1, 0> 0
        translate <5, 5, 5>
        texture {
            pigment { Cloud }
            finish { ambient  0.3 }
        }
    }

    plane {
        <0, -1, 0> 0
        translate <0, 0, 0>
        texture {
            pigment { Cloud }
            finish { ambient 0.8 }
        }
    }

    plane {
        <1, -1, 0> 0
        translate <0, 0, 0>
        texture {
            pigment { Cloud }
            finish { ambient 0.4 }
        }
    }
    translate <0, 1000, 0>
}

plane {
    <0,1, 0> 0
    texture {
        checker
        texture {
            pigment { color rgb <1.44, 0.19, 2.00> }
        }
        texture {
            pigment { color rgb <0.74, 0.74, 0.99> }
        }
    }
}

sphere {
    <0, 0, 0>, 1
    texture {
        pigment { rgb <0.658824, 0.658824, 0.658824> }
        finish {
            diffuse 0.2
            ambient 0.0
            reflection 0.65
        }
    }
    scale 1
    translate <0, 0.5, 0>
}