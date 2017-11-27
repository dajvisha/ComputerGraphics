// Persistence of Vision Ray Tracer Scene Description File
// File: Boat.pov
// Vers: 3.1
// Auth: Mick Hazelgrove

#include "colors.inc"  

#declare B_Tex =texture { 
	pigment {
		gradient y
			color_map {
				[(1-cos(radians(120)))/2 color rgb <0.4, 0.3, 0>]
				[(1-cos(radians( 30)))/2 color rgb <0.3, 0, 0.1> ]
				[(1-cos(radians( 30)))/2 color rgb <0.4, 0.2, 0> ]
                  }
                  scale 5
                  translate -1
           }
          finish {
          	 ambient 0.98
          	 specular 1 
          	 metallic
          	 reflection 0.35
        } 
 } 

#declare Prow = union{

#declare Count = 0;
#declare Radius = 1;
#declare Angle = 0;
#declare SphRad = .01;

#while(Count<140)

sphere{0,SphRad 
        translate<Count/25,pow(Count,2)/750,0>
        rotate z*Angle
        }
        
#declare Count = Count +1;
#declare Angle = Angle + 5;
#declare SphRad = SphRad + 0.03;
#declare Radius =  Radius +Radius;

#end        
rotate x*180
}

#declare Prow2 = union{

#declare Count = 0;
#declare Radius = 100;
#declare Angle = 280;
#declare SphRad = 4.2;

#while(Count<40)

sphere{0,SphRad 
        translate <0,Radius,0>
        rotate z*Angle
        }
        
#declare Count = Count +1;
#declare Angle = Angle + 1;
#declare SphRad = SphRad + 0.03;

#end        
rotate x*180
}


#declare FProw = union{
        object{Prow
                scale 0.025
                rotate z*35 
                
        }

        object{Prow2
                scale 0.025 
                translate<-1.8495,0.15,0>        
        }
        object {torus{0.1,0.075}
                translate<0.6,-0.175,0>
        }
        translate <4.85,1,0>       
}
#declare Post = difference{
cylinder{z*-0.05,z*0.05,2.1}
cylinder{z*-0.2,z*0.2,1.95}
scale<2.5,1.25,1>
clipped_by{sphere{0,20 inverse translate<1,19.1,0>}}
}
 
#declare Bsphere = difference{
        sphere{0,2}
        sphere{0,1.95}
        }
          
#declare BtShape = union{
 object{Bsphere
        scale <2.5,1.25,1>
        clipped_by{sphere{0,20 inverse translate<1,18,0>}}
        texture{B_Tex}
        }
        
   object{Bsphere
        scale <2.5,1.25,1>
        clipped_by{sphere{0,20 inverse translate<1,18.2,0>}}
        clipped_by{sphere{0,20 translate<1,18,0>}}
        texture{B_Tex}
        scale 1.01
        }       
       
   object{Bsphere
        scale <2.5,1.25,1>
        clipped_by{sphere{0,20 inverse translate<1,18.4,0>}}
        clipped_by{sphere{0,20 translate<1,18.2,0>}}
        texture{B_Tex}
        scale 1.02
        }
        
              
   object{Bsphere
        scale <2.5,1.25,1>
        clipped_by{sphere{0,20 inverse translate<1,18.6,0>}}
        clipped_by{sphere{0,20 translate<1,18.4,0>}}
        texture{B_Tex}
        scale 1.03
        }       
         
   object{Bsphere
        scale <2.5,1.25,1>
        clipped_by{sphere{0,20 inverse translate<1,18.8,0>}}
        clipped_by{sphere{0,20 translate<1,18.6,0>}} 
        texture{B_Tex}
        scale 1.04
        }
      
  object{Bsphere
        scale <2.5,1.25,1>
        clipped_by{sphere{0,20 inverse translate<1,19,0>}}
        clipped_by{sphere{0,20 translate<1,18.8,0>}}
        texture{B_Tex}
        scale 1.05
        }                    
 }
 
#declare boat = union{        
object{BtShape clipped_by{plane{z,-0.4 }}translate<0,0,.4>}
object{BtShape clipped_by{plane{z,0.4 inverse }}translate<0,0,-.4>}
object{FProw texture{B_Tex}scale 0.75 rotate z*18 translate <1.4,-1.25,0>}
object{Post texture{B_Tex rotate z*45}}
rotate z*10
}

//------------------------------------------------------------