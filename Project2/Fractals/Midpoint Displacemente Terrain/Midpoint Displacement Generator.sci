// Función que itera todas las partes del mapa de altura
// siguiendo el mismo algoritmo.
function mapa_iteracion = midpoint(mapa_iteracion, izq_x, der_x, abajo_y, arriba_y, amplitude, smoothing, ene)
    // Inicialización de los puntos medios de la parte a resolver
    midx = (izq_x + der_x) / 2;
    midy = (abajo_y + arriba_y) / 2;
    
    // Se obtienen los valores de los lados arriba y abajo, 
    // los renglones.
    mapa_iteracion(izq_x,midy) = 1/2 * (mapa_iteracion(izq_x,abajo_y) + mapa_iteracion(izq_x,arriba_y)) + amplitude * (-1+(2*rand(1))) * (2^(-smoothing * ene));
    
    mapa_iteracion(der_x,midy) = 1/2 * (mapa_iteracion(der_x,abajo_y) + mapa_iteracion(der_x,arriba_y)) + amplitude * (-1+(2*rand(1))) * (2^(-smoothing * ene));
    
    // Se obtienen los valores de los lados izquierda y derecha, 
    // las columnas.
    mapa_iteracion(midx,abajo_y) = 1/2 * (mapa_iteracion(izq_x,abajo_y) + mapa_iteracion(der_x,abajo_y)) + amplitude * (-1+(2*rand(1))) * (2^(-smoothing * ene));
    
    mapa_iteracion(midx,arriba_y) = 1/2 * (mapa_iteracion(izq_x,arriba_y) + mapa_iteracion(der_x,arriba_y)) + amplitude * (-1+(2*rand(1))) * (2^(-smoothing * ene));
    
    // Se obtienen los valores de la casilla de en medio, 
    // el centro.
    mapa_iteracion(midx,midy) = 1/4 * (mapa_iteracion(izq_x,midy) + mapa_iteracion(der_x,midy) + mapa_iteracion(midx,abajo_y) + mapa_iteracion(midx,arriba_y)) + amplitude * (-1+(2*rand(1))) * (2^(-smoothing * ene));
    
endfunction

// Función principal que inicializa los valores del mapa de altura
//  y manda llamar a la función de iteraciones dándole el pedazo
// del mapa a resolver. Despliega al final el mapa en forma gráfica.
function midpoint_displacement(n, bb, bl, lb, ll, amp, smo)
    // La función lee en orden los valores de n, A(1,1), A(1,last),
    // A(last,1), A(last,last), inicializa el mapa en ceros y
    // añade los valores al mapa.
    beg = 1;
    last = (2^n) + 1
    mapa_final = zeros(last, last)
    mapa_final(beg,beg) = bb;
    mapa_final(beg,last) = bl;
    mapa_final(last,beg) = lb;
    mapa_final(last,last) = ll;
    
    // Estructura de repetición que divide el mapa para su iteración
    // de tal forma que se usa una metodología algorítmica 
    // divide and conquer que obtiene el mapa resultante de 
    // aplicar el algoritmo a todo el mapa.
    i = 0;
    while i < n 
        pedazos = (2^i);
        pedazos_ancho = (2^n) / pedazos;
        xpedazo = 0
        while xpedazo < pedazos 
            ypedazo = 0
            while ypedazo < pedazos
                // Inicia los valores a pasar donde se indica
                // el pedazo a resolver de forma divide and 
                // conquer
                izq_x = pedazos_ancho * xpedazo;
                der_x = pedazos_ancho + izq_x;
                abajo_y = pedazos_ancho * ypedazo;
                arriba_y = pedazos_ancho + abajo_y;
                // Llamada a la función recursiva
                mapa_final = midpoint(mapa_final, izq_x + 1, der_x + 1, abajo_y + 1, arriba_y + 1, amp, smo, i);
                ypedazo = ypedazo + 1;
            end
            xpedazo = xpedazo + 1;
        end
        i = i + 1;
    end
    // Muestra del resultado final de forma gráfica
   surf(mapa_final);
   disp(mapa_final);
   
    i = 1;
    j = size(mapa_final,2)
    while i < j
        k = 1;
        while k < j
            disp("triangle {")
            mprintf("<%f, %f, %f>",i, mapa_final(i,k), k)
            mprintf("<%f, %f, %f>",(i + 1), mapa_final(i + 1,k), k)
            mprintf("<%f, %f, %f>",i, mapa_final(i,(k + 1)), (k + 1))
            disp("texture { Red }}")
        
            disp("triangle {")
            mprintf("<%f, %f, %f>",(i + 1), mapa_final(i + 1,k), k)
            mprintf("<%f, %f, %f>",(i + 1), mapa_final((i + 1),(k + 1)), (k + 1))
            mprintf("<%f, %f, %f>",i, mapa_final(i,(k + 1)), (k + 1))
            disp("texture { Blue }}")
            k = k + 1;
        end
        i = i + 1;
    end
   
endfunction
