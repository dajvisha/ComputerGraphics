#declare casita = 

union {
    // main house
union {
// main
difference {
box {-1,1 scale <32,13,12>}
plane {-y,0 rotate -25*x translate 13*y}
plane {-y,0 rotate 25*x translate 13*y}
 pigment {rgb 1.1}
        normal {gradient y .2 scale <1,.5,1>}
        finish {ambient .2 diffuse .7 specular .15 roughness .5
                }
 translate <-40,14,-40>
}
// roof
difference {
box {-1,1 rotate 45*x scale <38,7.5,15> translate <-40,17.5,-40>}
box {-1,1 rotate 45*x scale <38.1,7.5,15> translate <-40,17,-40>}
        pigment {rgb<1,.33,.25>}
        normal {brick .1 scale <1.5,.25,1>}
        finish {ambient .1 diffuse .67 specular .125 roughness .5
                }
}
// upper porch
box {-1,1 scale <37.5,1.75,17.5> translate <-40,12,-40>
        pigment {gradient x color_map {[.25 rgb 1.1][.25 rgbf 1]} scale 2}
        finish {ambient .2 diffuse .7 specular .15 roughness .5}
}
box {-1,1 scale <37.5,.5,17.5> translate <-40,10.25,-40>
        pigment {rgb 1.1}
        normal {brick .1 scale <5,1,5>}
        finish {ambient .2 diffuse .7 specular .15 roughness .5

                }
}
difference {
box {-1,1 scale <37.5,.5,17.5> translate <-40,13.75,-40>}
box {-1,1 scale <37.25,.51,17.25> translate <-40,13.75,-40>}
        pigment {rgb 1.1}
        normal {brick .1 scale <5,1,5>}
        finish {ambient .2 diffuse .7 specular .15 roughness .5

                }
}
// lower porch
box {-1,1 scale <37.5,1.75,17.5> translate <-40,4,-40>
        pigment {gradient x color_map {[.25 rgb 1.1][.25 rgbf 1]} scale 2}
        finish {ambient .2 diffuse .7 specular .15 roughness .5}
}
box {-1,1 scale <37.5,.5,17.5> translate <-40,2.25,-40>
        pigment {rgb 1.1}
        normal {brick .1 scale <5,1,5>}
        finish {ambient .2 diffuse .7 specular .15 roughness .5

                }
}
difference {
box {-1,1 scale <37.5,.5,17.5> translate <-40,5.75,-40>}
box {-1,1 scale <37.25,.51,17.25> translate <-40,5.75,-40>}
        pigment {rgb 1.1}
        normal {brick .1 scale <5,1,5>}
        finish {ambient .2 diffuse .7 specular .15 roughness .5
                }
}



}}