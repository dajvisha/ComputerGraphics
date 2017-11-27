// Diego Adolfo José Villa - A00815260
// Computer Graphics
// POV - Sierpinski Pyramid
// Based on the tutorial: Quick and Dirty: Rendering Sierpinski's Pyramid by Mike Kost

// ————————————————————————————
// Camera setup
// ————————————————————————————
global_settings {
    max_trace_level 10
    adc_bailout 1/255
}

camera { 
	location < 6, 5, -5.00>
	look_at  < 2, 4, 2>
	angle  75
}

// ————————————————————————————
// Environment setup
// ————————————————————————————
plane {
    <0,1, 0> 0
    pigment {
    	image_map {
    		png "sand.png"
    		map_type 0
    	}
    	scale .9
    	rotate y*75
    }
}

sky_sphere {
   pigment { color rgb <2.5, 2, 30>   }
}

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
            finish { ambient 0.1}
        }
    }

    plane {
        <0, -1, 0> 0
        translate <5, 5, 5>
        texture {
            pigment { Cloud }
            finish { ambient  0.1 }
        }
    }

    plane {
        <0, -1, 0> 0
        translate <0, 0, 0>
        texture {
            pigment { Cloud }
            finish { ambient 0.1 }
        }
    }

    plane {
        <1, -1, 0> 0
        translate <0, 0, 0>
        texture {
            pigment { Cloud }
            finish { ambient 0.1 }
        }
    }
    translate <0, 1000, 0>
}

// ————————————————————————————
// Pyramid
// ————————————————————————————	
#macro sierpinski(s, base_center, recursion_depth)
    #if (recursion_depth > 0)
        union {        
            sierpinski(s / 2, base_center + s/2*y,      recursion_depth - 1)
            sierpinski(s / 2, base_center - s/2*(x+z),  recursion_depth - 1)
            sierpinski(s / 2, base_center - s/2*(x-z),  recursion_depth - 1)
            sierpinski(s / 2, base_center - s/2*(-x+z), recursion_depth - 1)
            sierpinski(s / 2, base_center - s/2*(-x-z), recursion_depth - 1)
        }
    #else
        difference{
            box { <1,1,1>, <-1,0,-1> }
            plane{ x-y,  -sqrt(2)/2}
            plane{ -x-y, -sqrt(2)/2}
            plane{ z-y,  -sqrt(2)/2}
            plane{ -z-y, -sqrt(2)/2}
            scale s*1.0
            translate base_center
            pigment { rgb <0.2, 0, 0> }
		finish {
			diffuse 2
            	reflection 0.20
      	}
        }     
    #end
#end

// Call the recursive function
sierpinski(2,2,4)
