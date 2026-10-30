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

### 2026-10-30 - Integracion del Plano Maestro: Centro Historico de Oaxaca (Plaza Colonial 3D / 310m x 310m)

Integracion completa del paquete `Plaza_Colonial_Blender_3D` y su matriz espacial de 9 cuadrantes urbanos:

1. **Escenario y Cuadrantes Urbanos (Escala 1:1 en Metros)**:
   - Carga del diorama maestro `Models/Plaza_Colonial_Blender_3D/plaza_plano_maestro.obj` (310.0m x 310.0m, 96,100 m²).
   - Incluye Cuadrante 5 (Zocalo central y Kiosko colonial octagonal), Cuadrante 4 (Catedral Metropolitana de Cantera Verde y Alameda de Leon), Cuadrante 6 (Palacio de Gobierno y Portal de Mercaderes), y los 6 cuadrantes de manzanas coloniales perimetrales con red vial de 2 carriles.
   - Posicionamiento exacto de los 110 elementos del plano maestro: 1 Kiosko central, 32 faroles coloniales (8 en esplanada circular, 8 en esquinas de patios, 16 en andadores), 20 bancas de hierro y madera (12 en patios, 8 en andadores), 28 Laureles de la India en jardineras L, 4 arbustos topiarios esculpidos y 25 columnas de arquería colonial.

2. **Cuidado de UVs y Eliminacion de Texturas Estiradas**:
   - En `Configuracion/Model.h`: eliminada la alteracion artificial de coordenadas de textura (`vec *= horizontalScale`), preservando intacto el desempaquetado UV nativo de cada malla.
   - Activado filtrado anisotropico de alta calidad (`GL_TEXTURE_MAX_ANISOTROPY_EXT` a 16x) junto con `GL_REPEAT` y mipmaps lineales, garantizando nitidez en angulos rasantes en empedrados, asfalto y cantera sin difuminado ni estiramiento.
   - Corregido en `plaza_plano_maestro.mtl`: `mat_calle_completa` vinculado a `textura_calle_completa.png` (en vez de textura de piedra estirada 19x), y generadas texturas dedicadas `textura_vidrio.png` y `textura_laton.png` para faroles coloniales.

3. **Prevencion de Planos Sobrepuestos (Anti Z-Fighting)**:
   - Optimizada la matriz de proyeccion en `Main.cpp`: near plane ajustado a `0.1f` (en lugar de `0.0001f`), incrementando en mas de 1,000x la precision del depth buffer de 24 bits y eliminando el parpadeo entre la calzada (-0.245m), cruceros (-0.243m), banquetas (0.150m) y piso del zocalo (0.152m).
   - En `import_to_blender.py`: estructurado el flujo de importacion para cargar el plano maestro unificado sin instanciar duplicados de prototipos en el origen (0,0,0), evitando caras coincidentes.

4. **Navegacion, Personaje y Camara**:
   - El personaje humanoide ahora opera en escala real 1:1 (`modelScale = 1.0f`, altura ~1.80m), con velocidad de caminata de 3.8 m/s y carrera a 7.2 m/s con Shift.
   - Limites de movimiento expandidos a `[-154.0m, +154.0m]` para recorrer los 9 cuadrantes urbanos.
   - Camara en tercera persona (TPS) calibrada a 3.8m con zoom por rueda del raton (`1.2m` a `16.0m`).
   - Modo de camara libre (tecla 8) con velocidad adaptable (`15.0 m/s`, `36.0 m/s` con Shift) para sobrevuelo general de la maqueta.
