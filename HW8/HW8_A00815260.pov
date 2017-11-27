// Diego Adolfo José Villa - A00815260
// Computer Graphics
// POV - Trees with Arbaro
// Based on the tutorial: Quick And Dirty: Creating A Tree with Arbaro by Mike Kost

#include "black_tupelo.inc"
background {rgb <0.95,0.95,0.9>}
light_source { <5000,5000,-3000>, rgb 1.2 }
light_source { <-5000,2000,3000>, rgb 0.5 shadowless }

// ————————————————————————————
// Camera setup
// ————————————————————————————
camera { 
	location <0, 2, -50>
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

// ————————————————————————————
// Trees setup
// ————————————————————————————	         

union { 
	object { black_tupelo_13_stems pigment {color rgb <144/255, 104/255, 78/255>} }
      object { black_tupelo_13_leaves
      	texture { pigment {
      		gradient x
                	color_map {
                		[(1-cos(radians( 30)))/2 color rgb <0.7, 0.2, 0.2> ]
                		[(1-cos(radians(120)))/2 color rgb <0.8, 0.3, 0>]
                		[(1-cos(radians(120)))/2 color rgb <0.8, 0.7, 0.1>]}
                	scale 1.5
                	translate -1
                } 
                finish { ambient 0.15 diffuse 0.8 }}}
         rotate 90*y 
         translate <5,-.2,-5>
}

union { 
	object { black_tupelo_13_stems pigment {color rgb <144/255, 104/255, 78/255>} }
      object { black_tupelo_13_leaves
      	texture { pigment {
      		gradient x
                	color_map {
                		[(1-cos(radians( 30)))/2 color rgb <0.6, 0.6, 0> ]
                		[(1-cos(radians(120)))/2 color rgb <0.6, 0.7, 0.3>]
                		[(1-cos(radians(120)))/2 color rgb <0.6, 0.3, 0.3>]}
                	scale 1.5
                	translate -1
                } 
                finish { ambient 0.15 diffuse 0.8 }}}
         rotate 120*y 
         translate <-9,-.2,-8>
}

                
object { black_tupelo_13_stems
	rotate 45*y
	translate <18,-.2,-20>
	pigment {color rgb <144/255, 104/255, 78/255>}
      scale 1
 }
 
 object { black_tupelo_13_stems
 	rotate 45*y
 	translate <22,-.2,-4>
 	pigment {color rgb <144/255, 104/255, 78/255>}
 	scale 1          
 }

object { black_tupelo_13_stems
	rotate 45*y
	translate <21,-.2,-3.5>
	pigment {color rgb <144/255, 104/255, 78/255>}
	scale 1
}

















