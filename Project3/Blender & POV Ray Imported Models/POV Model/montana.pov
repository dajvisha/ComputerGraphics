// Diego Adolfo José Villa - A00815260
// Computer Graphics
// POV - Trees with Arbaro
// Based on the tutorial: Quick And Dirty: Creating A Tree with Arbaro by Mike Kost

#include "object.inc"
background {rgb <0.95,0.95,0.9>}
light_source { <5000,5000,-3000>, rgb 1.2 }
light_source { <-5000,2000,3000>, rgb 0.5 shadowless }

// ————————————————————————————
// Camera setup
// ————————————————————————————

/*camera { 
	location <0, 2, -50>
	look_at  < 5, 20, 2>
	angle  60
}*/

/*camera { 
	location <0, 10, -50>
	look_at  < 5, 20, 2>
	angle  60
}*/

/*camera { 
	location <0, 15, -50>
	look_at  < 5, 20, 2>
	angle  60
}*/

camera { 
	location <0, 20, -50>
	look_at  < 5, 20, 2>
	angle  60
}


// ————————————————————————————
// Environmet setup
// ————————————————————————————
#declare Cloud = pigment {
    wrinkles
    turbulence <0.20, 0.02, 0.35>
    octaves    5
    omega      0.85
    lambda     4
    color_map {
        [0.35 color rgb <1,1,1, 1>]
        [0.55 color rgb <0.5,0.7,1.00, 1.00>]
    }
    scale <1200,1000,1000>
}

union {
    plane {
        <0, -1, 0> 0
        texture {
            pigment { Cloud }
        }
    }    
    translate <0, 1000, 0>
}

plane {
    <0,1, 0> 0
    pigment {
    	color rgb <0.6, 0.6, 0.3>
    }
}

union
{
    object { 
    	Mountain
        translate <0, 0, 0>
        rotate <-90, 0, 0>
         rotate <0, -90, 0>
        translate <-10, -17, 0>
        texture { pigment {
          		gradient y
                    	color_map {
                    		[(1-cos(radians( 30)))/2 color rgb <0.6, 0.6, 0> ]
                    	}
                    	scale 5
                    	translate -1
                    }
                    }
    }
}
