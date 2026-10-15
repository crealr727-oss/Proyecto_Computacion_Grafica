# Integracion del proyecto

## Bitacora de agregados

### 2026-10-09 - Terreno base delimitado

Primera etapa: se incorpora un unico piso plano para iniciar la maqueta del entorno del Zocalo de la Ciudad de Oaxaca. No se agregan edificios, mobiliario ni vegetacion en esta etapa.

- Referencia del mapa: area aproximada de 43,144.92 m2 y perimetro de 830.98 m.
- Como las cotas de cada lado no son legibles en la referencia, se usa un rectangulo equivalente aproximado de 211.36 x 204.13 m. Estas medidas coinciden aproximadamente con el area y el perimetro mostrados; no representan aun el contorno irregular exacto.
- Escala: 1:100. Las dimensiones del modelo son 2.1136 x 2.0413 unidades, manteniendo la proporcion del terreno real.
- El piso lleva una textura de pavimento de piedra y un perimetro rojo para distinguir el limite de la zona.

Archivos agregados:

- `Configuracion/Models/Terreno_Zocalo.obj`: malla plana del terreno con coordenadas UV y normales.
- `Configuracion/Models/Terreno_Zocalo.mtl`: material que enlaza la textura del pavimento.
- `Configuracion/Models/Textures/textura_patio_piedra.jpg`: textura de piedra para el piso base.

Integracion en la escena:

- `Configuracion/Carga de Modelos.cpp`: carga el terreno en lugar del modelo de prueba, eleva e inclina la camara y configura la iluminacion para observar el piso.
- `Configuracion/Mesh.h`: activa el muestreo del mapa difuso en meshes con textura.

Pendiente para la siguiente iteracion: sustituir el rectangulo equivalente por el poligono real cuando se cuente con las longitudes o coordenadas de sus vertices. Los siguientes agregados al proyecto se registraran en esta bitacora.

### 2026-10-09 - Escena ejecutada desde Main.cpp

- `Configuracion/Main.cpp` ahora contiene el punto de entrada de la escena: inicializa OpenGL, carga el terreno y permite mover la camara con WASD/flechas y raton.
- `Configuracion/Configuracion.vcxproj` y `Configuracion/Configuracion.vcxproj.filters` compilan y muestran `Main.cpp` como archivo fuente activo, en lugar de `Carga de Modelos.cpp`.
- La proyeccion convierte el zoom de grados a radianes para encuadrar correctamente el terreno.

### 2026-10-09 - Calles, banquetas y Alameda

- Se conserva la huella total de 2.1136 x 2.0413 unidades (211.36 x 204.13 m a escala 1:100).
- Se agregan cuatro franjas de calle de 8.5 m reales y cuatro banquetas de 2.5 m, contenidas dentro de esa huella para no alterar las dimensiones generales.
- El pavimento de piedra cubre la base; al noroeste se representa una zona verde dividida por dos andadores de piedra, como aproximacion de la Alameda del mapa.
- `Configuracion/Models/Terreno_Zocalo.mtl` asigna las texturas existentes: `textura_asfalto_calle.jpg`, `textura_banqueta.jpg`, `textura_patio_piedra.jpg` y `textura_suelo_arbol.jpg`, todas dentro de `Configuracion/Models/Textures/`.
- `Configuracion/Models/Terreno_Zocalo.obj` incorpora las superficies con UV repetidas aproximadamente cada 5 m reales. Las franjas se elevan 5 cm respecto de la base para evitar parpadeo entre superficies.
- El ancho de calles, banquetas y la division exacta de la Alameda son estimaciones visuales; el mapa compartido no proporciona cotas individuales de esos elementos.

### 2026-10-09 - Carga de texturas RGBA

- `Configuracion/Model.h` solicita imagenes en RGBA para conservar transparencias, valida el puntero y las dimensiones antes de crear la textura, e imprime la ruta y el motivo de SOIL si falla la carga.
- Antes de subir los pixeles configura `GL_UNPACK_ALIGNMENT` en 1 y restaura la alineacion previa al terminar.

### 2026-10-09 - Personaje humano controlable

- `Configuracion/Character.h` agrega una clase derivada de `Model` con posicion, velocidad, rotacion, movimiento WASD, gravedad, raycast vertical al plano del terreno y limites de colision.
- `Configuracion/Main.cpp` carga `Models/ASIAN MAN.obj` a escala 0.01 (aproximadamente 1.65 m en el terreno a escala 1:100), lo dibuja cada frame y activa/desactiva el control con 8 (tambien acepta 8 del teclado numerico).
- WASD controla al personaje en modo activo; C alterna entre camara de seguimiento y vista libre. Fuera del modo de personaje, WASD conserva el movimiento de la camara.
- `Configuracion/Model.h` omite mapas difusos que no se pudieron cargar para que el material se renderice con el color base en vez de enlazar una textura OpenGL invalida.
- El archivo `ASIAN MAN.mtl` referencia imagenes bajo una ruta absoluta de Descargas que no existe en este equipo. El modelo se carga sin esos mapas; se requieren las texturas originales copiadas a `Models/Textures` y rutas relativas en el MTL para recuperar sus colores/texturas.
