// Diego Adolfo José Villa - A00815260
// Computer Graphics
// POV - Chess Set
// Based on the tutorial: Building a CSG Chess Set by Mike Kost
// Some things were developed thanks to following material:
//	POV-Ray Raytracer by Friedrich A. Lohmüller - Link: http://www.f-lohmueller.de/pov_tut/pov__eng.htm

global_settings {
    max_trace_level 10
    adc_bailout 1/255
}

camera { 
	location < 0.00, 5, -4.00>
	look_at  < 2.75, -0.25,  2.00>
	right x*image_width/image_height
	angle  60
}

// ————————————————————————————
// Background
plane {
    <0,1, 0> 0
    texture { pigment { color rgb <0.7, 0.9, 1> } }
}
// ————————————————————————————

// ————————————————————————————
// Tablero
#declare Tablero = union {
	box {<-1.01,0.00,-1.01>,<1.01,0.049,1.01>
		texture { pigment { color rgb<0.75,0.5,0.30> }}} 
	box {<-1.00,0.00,-1.00>,<1.00,0.050,1.00>
		texture {
			pigment { 
				checker
				color rgb<1,1,1>
				color rgb<0.7,0.4,0.1>
			} 
				scale 0.25
		}
		} 
} 
// ————————————————————————————

// ————————————————————————————
// Peon
#declare basePeon = difference {
    box { 0.3, -0.5 }
    torus { 0.8, 0.73}
    translate <0, 1, 0>
}

#declare PeonCafe = merge {
	object { basePeon }
	sphere { 0, 0.13 translate <0, 1.42, 0> }
	pigment { rgb <0.7, 0.4, 0> }
	finish {
		diffuse 2
            ambient .6
            reflection 0.5
      }
}

#declare PeonBlanco = merge {
	object { basePeon }
	sphere { 0, 0.13 translate <0, 1.42, 0> }
	pigment { rgb <1, 1, 1> }
	finish {
		diffuse 2
            ambient .6
            reflection 0.5
      }
}
// ————————————————————————————

// ————————————————————————————
// Castillo
#declare baseCastillo = difference {
    box { 0.4, -0.5 }
    torus { 0.8,0.7 }
    translate <0, 0.5, 0>
}

#declare CastilloCafe = difference {
    object {
        baseCastillo
        scale <1.1, 1.2, 1.1>
    }
    cylinder { 0.95*y, 1.1*y, 0.17 }
    #local i = 0;
    #while (i < 4)
        box {
            <-0.04, 1.0, -1>, <0.04, 1.1, 1>
            rotate 45*y*i
        }
        #local i = i + 1;
    #end
    pigment { rgb <0.7, 0.4, 0> }
    finish {
    	diffuse 2
    	ambient .6
    	reflection 0.5
    }
}

#declare CastilloBlanco = difference {
    object {
        baseCastillo
        scale <1.1, 1.2, 1.1>
    }
    cylinder { 0.95*y, 1.1*y, 0.17 }
    #local i = 0;
    #while (i < 4)
        box {
            <-0.04, 1.0, -1>, <0.04, 1.1, 1>
            rotate 45*y*i
        }
        #local i = i + 1;
    #end
    pigment { rgb <1, 1, 1> }
    finish {
    	diffuse 2
    	ambient .6
    	reflection 0.5
    }
}
// ————————————————————————————

// ————————————————————————————
// Alfil
#declare baseAlfil = difference {
    box { 0.4, -0.5 }
    torus { 0.8,0.7 }
    translate <0, 0.5, 0>
}

#declare AlfilCafe = merge {
    object {
        baseAlfil
        scale <1.05, 1.3, 1.05>
    }
    difference {
        sphere {
            0, 0.17
            scale <1, 1.5, 1>
            translate <0, 1.3, 0>
        }
        box {
            <-1, -0.15, -0.025>, <1, 0.15, 0.025>
            rotate x*12
            rotate y*30
            translate <0, 1.45, 0.075>
        }
    }
    pigment { rgb <0.7, 0.4, 0> }
    finish {
    	diffuse 2
    	ambient .6
    	reflection 0.5
    }
}

#declare AlfilBlanco = merge {
    object {
        baseAlfil
        scale <1.05, 1.3, 1.05>
    }
    difference {
        sphere {
            0, 0.17
            scale <1, 1.5, 1>
            translate <0, 1.3, 0>
        }
        box {
            <-1, -0.15, -0.025>, <1, 0.15, 0.025>
            rotate x*12
            rotate y*30
            translate <0, 1.45, 0.075>
        }
    }
    pigment { rgb <1, 1, 1> }
    finish {
    	diffuse 2
    	ambient .6
    	reflection 0.5
    }
}
// ————————————————————————————

// ————————————————————————————
// Reina
#declare baseReina = difference {
    box { 0.4, -0.5 }
    torus { 0.8,0.7 }
    translate <0, 0.5, 0>
}

#declare ReinaCafe = merge {
    object {
        baseReina
        scale <1.2, 1.5, 1.2>
    }
    #local i = 0;
    #while (i < 7)
        sphere {
            0, 0.07
            translate <0.17, 1.55*0.9, 0>
            rotate y*360/7*i
        }
        #local i = i + 1;
    #end
   pigment { rgb <0.7, 0.4, 0> }
    finish {
    	diffuse 2
    	ambient .6
    	reflection 0.5
    }
}

#declare ReinaBlanca = merge {
    object {
        baseReina
        scale <1.2, 1.5, 1.2>
    }
    #local i = 0;
    #while (i < 7)
        sphere {
            0, 0.07
            translate <0.17, 1.55*0.9, 0>
            rotate y*360/7*i
        }
        #local i = i + 1;
    #end
    pigment { rgb <1, 1, 1> }
    finish {
    	diffuse 2
    	ambient .6
    	reflection 0.5
    }
}
// ————————————————————————————

// ————————————————————————————
// Rey
#declare baseRey = difference {
    box { 0.4, -0.5 }
    torus { 0.8,0.7 }
    translate <0, 0.5, 0>
}

#declare ReyCafe = merge {
    object {
       baseRey
        scale <1.2, 1.5, 1.2>
    }
    box {
        <0.03, 1, 0.05>,
        <-0.03, 1.5*0.9+0.4, -0.05>
    }
    box {
        <-0.03001, 1.5*0.9+0.20, -0.15>
        < 0.03001, 1.5*0.9+0.30,  0.15>
    }
    pigment { rgb <0.7, 0.4, 0> }
    finish {
    	diffuse 2
    	ambient .6
    	reflection 0.5
    }
}

#declare ReyBlanco = merge {
    object {
       baseRey
        scale <1.2, 1.5, 1.2>
    }
    box {
        <0.03, 1, 0.05>,
        <-0.03, 1.5*0.9+0.4, -0.05>
    }
    box {
        <-0.03001, 1.5*0.9+0.20, -0.15>
        < 0.03001, 1.5*0.9+0.30,  0.15>
    }
    pigment { rgb <1, 1, 1> }
    finish {
    	diffuse 2
    	ambient .6
    	reflection 0.5
    }
}
// ————————————————————————————

// ————————————————————————————
// Caballo
#declare CaballoCafe = union{
  sphere{ <0,1,0>, 0.1 }
  cone  { <0,0,0>, 0.2, <0,1,0>, 0.0}
  pigment { rgb <0.7, 0.4, 0> }
  finish {
  	diffuse 2
    	ambient .6
    	reflection 0.5
   }
}

#declare CaballoBlanco = union{
  sphere{ <0,1,0>, 0.1 }
  cone  { <0,0,0>, 0.2, <0,1,0>, 0.0}
  pigment { rgb <1, 1, 1> }
  finish {
  	diffuse 2
    	ambient .6
    	reflection 0.5
   }
}
// ————————————————————————————

// ————————————————————————————
// Colocar piezas

// Posicionar tablero
object { 
	Tablero
	translate <1,0,1>
	scale 3
	rotate <0,0,0>
} 

// Peones cafes
object { PeonCafe translate <0.3,0,0.75> }
object { PeonCafe translate <1,0,0.75> }
object { PeonCafe translate <1.72,0,0.75> }
object { PeonCafe translate <2.45,0,0.75> }
object { PeonCafe translate <3.15,0,0.75> }
object { PeonCafe translate <3.85,0,0.75> }
object { PeonCafe translate <4.55,0,0.75> }
object { PeonCafe translate <5.25,0,0.75> }

// Peones blancos
object { PeonBlanco translate <0.34,0,4.3> }
object { PeonBlanco translate <1.05,0,4.3> }
object { PeonBlanco translate <1.72,0,4.3> }
object { PeonBlanco translate <2.45,0,4.3> }
object { PeonBlanco translate <3.15,0,4.3> }
object { PeonBlanco translate <3.85,0,4.3> }
object { PeonBlanco translate <4.55,0,4.3> }
object { PeonBlanco translate <5.25,0,4.3> }

// Castillos cafes
object { CastilloCafe translate <0.35,0,0.40> }
object { CastilloCafe translate <5.65,0,0.40> }

// Castillos blancos
object { CastilloBlanco translate <0.35,0,5.6> }
object { CastilloBlanco translate <5.65,0,5.6> }

// Alfiles cafes
object { AlfilCafe translate <1.85,0,0.40> }
object { AlfilCafe translate <4.2,0,0.40> }

// Alfiles blancos
object { AlfilBlanco translate <1.85,0,5.6> }
object { AlfilBlanco translate <4.1,0,5.6> }

// Reina cafe
object { ReinaCafe translate <3.35,0,0.40> }

// Reina blanca
object { ReinaBlanca translate <3.35,0,5.6> }

// Rey cafe
object { ReyCafe translate <2.6,0,0.40> }

// Rey blanco
object { ReyBlanco translate <2.6,0,5.6> }

// Caballo cafe
object { CaballoCafe translate <1.05,0.5,0.12> }
object { CaballoCafe translate <4.50,0.5,0.12> }

// Caballo blanco
object { CaballoBlanco translate <1.05,0.5,5> }
object { CaballoBlanco translate <4.50,0.5,5> }

// ————————————————————————————


