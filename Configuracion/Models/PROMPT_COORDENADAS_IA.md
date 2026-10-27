# PROMPT MAESTRO DE COORDENADAS PARA INTÉRPRETE DE IA
## Conversión, Reconstrucción y Posicionamiento Espacial 3D

Eres un agente de Inteligencia Artificial especializado en Arquitectura 3D, Motores de Videojuegos (Unreal Engine 5, Unity, Godot) y Web3D (Three.js, React Three Fiber, Babylon.js, Blender Python).

A continuación se presenta el **registro geométrico y espacial exacto** de todos los modelos y objetos que componen el plano maestro de la **Plaza Colonial Zócalo (60m x 60m)**. Utiliza esta matriz de coordenadas para generar código, instanciar mallas, reconstruir la escena en cualquier motor o convertir el diseño.

---

### 1. ESPECIFICACIÓN DEL SISTEMA DE COORDENADAS
- **Unidades**: Metros del mundo real (1.0 = 1 metro).
- **Origen (0, 0, 0)**: Centro geométrico exacto de la base del Kiosko colonial octagonal.
- **Sistema de Ejes (Three.js / WebGL / OpenGL)**:
  - **Eje X**: Horizontal Este-Oeste (+X = Este / Derecha, -X = Oeste / Izquierda).
  - **Eje Y**: Vertical (+Y = Altura / Elevación sobre el terreno).
  - **Eje Z**: Horizontal Norte-Sur (+Z = Sur / Frente, -Z = Norte / Fondo).
- **Conversión a Blender / Unreal Engine (Z-Up)**:
  - `X_blender = X`
  - `Y_blender = Z`
  - `Z_blender = Y`
  - `Rot_Z_blender = -Rot_Y_deg`
- **Dimensiones Totales del Terreno**: 60.0m de ancho x 60.0m de largo (3,600 m²).
  - Terreno central de plaza: 49.6m x 49.6m.
  - Banqueta perimetral: 5.2m de ancho perimetral con calle de asfalto exterior.
  - Esplanada central circular del Kiosko: Radio de 10.4m (Elevación Y = +0.358m).
  - 4 Andadores principales cardinales: 7.2m de ancho despejado.
  - 4 Patios formales en cuadrantes: 11.5m x 11.5m (Centros en X: ±14.6m, Z: ±14.6m, Elevación Y = +0.26m).

---

### 2. RESUMEN DE MODELOS Y ARCHIVOS DE ORIGEN (.OBJ / .MTL)
| Modelo | Archivo OBJ | Bounding Box Aprox. (m) | Rol / Descripción |
|---|---|---|---|
| Kiosko Colonial | `kiosko_colonial.obj` | 8.4 x 8.5 x 8.4 | Estructura octagonal con cúpula de cobre y base de cantera |
| Banca Colonial | `banca_colonial.obj` | 2.2 x 0.9 x 0.8 | Banca de hierro forjado y listones de madera barnizada |
| Laurel de la India | `laurel_de_la_india.obj` | 5.4 x 6.8 x 5.4 | Árbol Ficus retusa maduro de copa frondosa globular |
| Farol Colonial | `farol_colonial.obj` | 0.8 x 3.8 x 0.8 | Farol de pie colonial con cristal y luminaria |
| Arbusto Topiario | `arbusto_topiario.obj` | 2.4 x 2.2 x 2.4 | Arbusto podado esférico para esquinas diagonales |
| Escena Completa | `plaza_plano_maestro.obj` | 60.0 x 6.0 x 60.0 | Diorama unificado con terreno, plataformas y portal |

---

### 3. MATRIZ DETALLADA DE COORDENADAS POR OBJETO (82 OBJETOS EN TOTAL)

#### A. Kiosko Central (1 objeto)
- **ID**: `kiosko_central_01`
- **Posición**: `X = 0.00m, Y = 0.358m, Z = 0.00m`
- **Rotación**: `Y = 0.0°`
- **Escala**: `[1.0, 1.0, 1.0]`
- **Zona**: Esplanada Circular Central

#### B. Faroles de la Esplanada Circular (8 objetos en anillo concéntrico de 10.0m de radio)
- **farol_esplanada_1**: Posición `[X: 9.24, Y: 0.36, Z: 3.83]` | Rotación Y: `-22.5°`
- **farol_esplanada_2**: Posición `[X: 3.83, Y: 0.36, Z: 9.24]` | Rotación Y: `-67.5°`
- **farol_esplanada_3**: Posición `[X: -3.83, Y: 0.36, Z: 9.24]` | Rotación Y: `-112.5°`
- **farol_esplanada_4**: Posición `[X: -9.24, Y: 0.36, Z: 3.83]` | Rotación Y: `-157.5°`
- **farol_esplanada_5**: Posición `[X: -9.24, Y: 0.36, Z: -3.83]` | Rotación Y: `-202.5°`
- **farol_esplanada_6**: Posición `[X: -3.83, Y: 0.36, Z: -9.24]` | Rotación Y: `-247.5°`
- **farol_esplanada_7**: Posición `[X: 3.83, Y: 0.36, Z: -9.24]` | Rotación Y: `-292.5°`
- **farol_esplanada_8**: Posición `[X: 9.24, Y: 0.36, Z: -3.83]` | Rotación Y: `-337.5°`

#### C. Bancas en Patios Formales (12 bancas - 100% Pavimentadas sobre cantera)
- **banca_patio_noreste_n** (Banca Patio Noreste (Eje Cardinal)): Posición `[X: 14.60, Y: 0.26, Z: 18.51]` | Rotación Y: `180.0°` | Zona: Patio Noreste
- **banca_patio_noreste_ext** (Banca Patio Noreste (Lateral Exterior)): Posición `[X: 18.51, Y: 0.26, Z: 14.60]` | Rotación Y: `-90.0°` | Zona: Patio Noreste
- **banca_patio_noreste_int** (Banca Patio Noreste (Lateral Interior)): Posición `[X: 10.69, Y: 0.26, Z: 14.60]` | Rotación Y: `90.0°` | Zona: Patio Noreste
- **banca_patio_noroeste_n** (Banca Patio Noroeste (Eje Cardinal)): Posición `[X: -14.60, Y: 0.26, Z: 18.51]` | Rotación Y: `180.0°` | Zona: Patio Noroeste
- **banca_patio_noroeste_ext** (Banca Patio Noroeste (Lateral Exterior)): Posición `[X: -18.51, Y: 0.26, Z: 14.60]` | Rotación Y: `90.0°` | Zona: Patio Noroeste
- **banca_patio_noroeste_int** (Banca Patio Noroeste (Lateral Interior)): Posición `[X: -10.69, Y: 0.26, Z: 14.60]` | Rotación Y: `-90.0°` | Zona: Patio Noroeste
- **banca_patio_suroeste_n** (Banca Patio Suroeste (Eje Cardinal)): Posición `[X: -14.60, Y: 0.26, Z: -18.51]` | Rotación Y: `0.0°` | Zona: Patio Suroeste
- **banca_patio_suroeste_ext** (Banca Patio Suroeste (Lateral Exterior)): Posición `[X: -18.51, Y: 0.26, Z: -14.60]` | Rotación Y: `90.0°` | Zona: Patio Suroeste
- **banca_patio_suroeste_int** (Banca Patio Suroeste (Lateral Interior)): Posición `[X: -10.69, Y: 0.26, Z: -14.60]` | Rotación Y: `-90.0°` | Zona: Patio Suroeste
- **banca_patio_sureste_n** (Banca Patio Sureste (Eje Cardinal)): Posición `[X: 14.60, Y: 0.26, Z: -18.51]` | Rotación Y: `0.0°` | Zona: Patio Sureste
- **banca_patio_sureste_ext** (Banca Patio Sureste (Lateral Exterior)): Posición `[X: 18.51, Y: 0.26, Z: -14.60]` | Rotación Y: `-90.0°` | Zona: Patio Sureste
- **banca_patio_sureste_int** (Banca Patio Sureste (Lateral Interior)): Posición `[X: 10.69, Y: 0.26, Z: -14.60]` | Rotación Y: `90.0°` | Zona: Patio Sureste

#### D. Bancas en Andadores Principales de 7.2m (8 bancas)
- **banca_andador_n_o** (Banca Andador Norte (Oeste)): Posición `[X: -2.50, Y: 0.22, Z: 15.50]` | Rotación Y: `90.0°` | Zona: Andador Norte
- **banca_andador_n_e** (Banca Andador Norte (Este)): Posición `[X: 2.50, Y: 0.22, Z: 15.50]` | Rotación Y: `-90.0°` | Zona: Andador Norte
- **banca_andador_s_o** (Banca Andador Sur (Oeste)): Posición `[X: -2.50, Y: 0.22, Z: -15.50]` | Rotación Y: `90.0°` | Zona: Andador Sur
- **banca_andador_s_e** (Banca Andador Sur (Este)): Posición `[X: 2.50, Y: 0.22, Z: -15.50]` | Rotación Y: `-90.0°` | Zona: Andador Sur
- **banca_andador_e_s** (Banca Andador Este (Sur)): Posición `[X: 15.50, Y: 0.22, Z: -2.50]` | Rotación Y: `0.0°` | Zona: Andador Este
- **banca_andador_e_n** (Banca Andador Este (Norte)): Posición `[X: 15.50, Y: 0.22, Z: 2.50]` | Rotación Y: `180.0°` | Zona: Andador Este
- **banca_andador_w_s** (Banca Andador Oeste (Sur)): Posición `[X: -15.50, Y: 0.22, Z: -2.50]` | Rotación Y: `0.0°` | Zona: Andador Oeste
- **banca_andador_w_n** (Banca Andador Oeste (Norte)): Posición `[X: -15.50, Y: 0.22, Z: 2.50]` | Rotación Y: `180.0°` | Zona: Andador Oeste

#### E. Faroles en Esquinas de Patios (8 faroles)
- **farol_patio_noreste_1**: Posición `[X: 10.20, Y: 0.23, Z: 19.00]` | Rotación Y: `0.0°` | Zona: Patio Noreste
- **farol_patio_noreste_2**: Posición `[X: 19.00, Y: 0.23, Z: 10.20]` | Rotación Y: `90.0°` | Zona: Patio Noreste
- **farol_patio_noroeste_1**: Posición `[X: -10.20, Y: 0.23, Z: 19.00]` | Rotación Y: `90.0°` | Zona: Patio Noroeste
- **farol_patio_noroeste_2**: Posición `[X: -19.00, Y: 0.23, Z: 10.20]` | Rotación Y: `180.0°` | Zona: Patio Noroeste
- **farol_patio_suroeste_1**: Posición `[X: -10.20, Y: 0.23, Z: -19.00]` | Rotación Y: `180.0°` | Zona: Patio Suroeste
- **farol_patio_suroeste_2**: Posición `[X: -19.00, Y: 0.23, Z: -10.20]` | Rotación Y: `270.0°` | Zona: Patio Suroeste
- **farol_patio_sureste_1**: Posición `[X: 10.20, Y: 0.23, Z: -19.00]` | Rotación Y: `270.0°` | Zona: Patio Sureste
- **farol_patio_sureste_2**: Posición `[X: 19.00, Y: 0.23, Z: -10.20]` | Rotación Y: `360.0°` | Zona: Patio Sureste

#### F. Laureles de la India / Árboles Frondosos en Jardineras L (28 árboles)
- **laurel_noreste_1** (Laurel de la India Noreste #1): Posición `[X: 7.20, Y: 0.47, Z: 15.80]` | Escala: `1.25` | Rotación Y: `0.0°` | Rol: Arbolado urbano frondoso - Alineación Andador Z (Exterior)
- **laurel_noreste_2** (Laurel de la India Noreste #2): Posición `[X: 7.40, Y: 0.47, Z: 11.20]` | Escala: `1.30` | Rotación Y: `43.0°` | Rol: Arbolado urbano frondoso - Alineación Andador Z (Interior)
- **laurel_noreste_3** (Laurel de la India Noreste #3): Posición `[X: 9.80, Y: 0.47, Z: 9.80]` | Escala: `1.35` | Rotación Y: `86.0°` | Rol: Arbolado urbano frondoso - Árbol Emblemático Esquina
- **laurel_noreste_4** (Laurel de la India Noreste #4): Posición `[X: 11.20, Y: 0.47, Z: 7.40]` | Escala: `1.30` | Rotación Y: `129.0°` | Rol: Arbolado urbano frondoso - Alineación Andador X (Interior)
- **laurel_noreste_5** (Laurel de la India Noreste #5): Posición `[X: 15.80, Y: 0.47, Z: 7.20]` | Escala: `1.25` | Rotación Y: `172.0°` | Rol: Arbolado urbano frondoso - Alineación Andador X (Exterior)
- **laurel_noreste_6** (Laurel de la India Noreste #6): Posición `[X: 19.20, Y: 0.47, Z: 7.60]` | Escala: `1.15` | Rotación Y: `215.0°` | Rol: Arbolado urbano frondoso - Buffer Perimetral X
- **laurel_noreste_7** (Laurel de la India Noreste #7): Posición `[X: 7.60, Y: 0.47, Z: 19.20]` | Escala: `1.15` | Rotación Y: `258.0°` | Rol: Arbolado urbano frondoso - Buffer Perimetral Z
- **laurel_noroeste_1** (Laurel de la India Noroeste #1): Posición `[X: -7.20, Y: 0.47, Z: 15.80]` | Escala: `1.25` | Rotación Y: `90.0°` | Rol: Arbolado urbano frondoso - Alineación Andador Z (Exterior)
- **laurel_noroeste_2** (Laurel de la India Noroeste #2): Posición `[X: -7.40, Y: 0.47, Z: 11.20]` | Escala: `1.30` | Rotación Y: `133.0°` | Rol: Arbolado urbano frondoso - Alineación Andador Z (Interior)
- **laurel_noroeste_3** (Laurel de la India Noroeste #3): Posición `[X: -9.80, Y: 0.47, Z: 9.80]` | Escala: `1.35` | Rotación Y: `176.0°` | Rol: Arbolado urbano frondoso - Árbol Emblemático Esquina
- **laurel_noroeste_4** (Laurel de la India Noroeste #4): Posición `[X: -11.20, Y: 0.47, Z: 7.40]` | Escala: `1.30` | Rotación Y: `219.0°` | Rol: Arbolado urbano frondoso - Alineación Andador X (Interior)
- **laurel_noroeste_5** (Laurel de la India Noroeste #5): Posición `[X: -15.80, Y: 0.47, Z: 7.20]` | Escala: `1.25` | Rotación Y: `262.0°` | Rol: Arbolado urbano frondoso - Alineación Andador X (Exterior)
- **laurel_noroeste_6** (Laurel de la India Noroeste #6): Posición `[X: -19.20, Y: 0.47, Z: 7.60]` | Escala: `1.15` | Rotación Y: `305.0°` | Rol: Arbolado urbano frondoso - Buffer Perimetral X
- **laurel_noroeste_7** (Laurel de la India Noroeste #7): Posición `[X: -7.60, Y: 0.47, Z: 19.20]` | Escala: `1.15` | Rotación Y: `348.0°` | Rol: Arbolado urbano frondoso - Buffer Perimetral Z
- **laurel_suroeste_1** (Laurel de la India Suroeste #1): Posición `[X: -7.20, Y: 0.47, Z: -15.80]` | Escala: `1.25` | Rotación Y: `180.0°` | Rol: Arbolado urbano frondoso - Alineación Andador Z (Exterior)
- **laurel_suroeste_2** (Laurel de la India Suroeste #2): Posición `[X: -7.40, Y: 0.47, Z: -11.20]` | Escala: `1.30` | Rotación Y: `223.0°` | Rol: Arbolado urbano frondoso - Alineación Andador Z (Interior)
- **laurel_suroeste_3** (Laurel de la India Suroeste #3): Posición `[X: -9.80, Y: 0.47, Z: -9.80]` | Escala: `1.35` | Rotación Y: `266.0°` | Rol: Arbolado urbano frondoso - Árbol Emblemático Esquina
- **laurel_suroeste_4** (Laurel de la India Suroeste #4): Posición `[X: -11.20, Y: 0.47, Z: -7.40]` | Escala: `1.30` | Rotación Y: `309.0°` | Rol: Arbolado urbano frondoso - Alineación Andador X (Interior)
- **laurel_suroeste_5** (Laurel de la India Suroeste #5): Posición `[X: -15.80, Y: 0.47, Z: -7.20]` | Escala: `1.25` | Rotación Y: `352.0°` | Rol: Arbolado urbano frondoso - Alineación Andador X (Exterior)
- **laurel_suroeste_6** (Laurel de la India Suroeste #6): Posición `[X: -19.20, Y: 0.47, Z: -7.60]` | Escala: `1.15` | Rotación Y: `35.0°` | Rol: Arbolado urbano frondoso - Buffer Perimetral X
- **laurel_suroeste_7** (Laurel de la India Suroeste #7): Posición `[X: -7.60, Y: 0.47, Z: -19.20]` | Escala: `1.15` | Rotación Y: `78.0°` | Rol: Arbolado urbano frondoso - Buffer Perimetral Z
- **laurel_sureste_1** (Laurel de la India Sureste #1): Posición `[X: 7.20, Y: 0.47, Z: -15.80]` | Escala: `1.25` | Rotación Y: `270.0°` | Rol: Arbolado urbano frondoso - Alineación Andador Z (Exterior)
- **laurel_sureste_2** (Laurel de la India Sureste #2): Posición `[X: 7.40, Y: 0.47, Z: -11.20]` | Escala: `1.30` | Rotación Y: `313.0°` | Rol: Arbolado urbano frondoso - Alineación Andador Z (Interior)
- **laurel_sureste_3** (Laurel de la India Sureste #3): Posición `[X: 9.80, Y: 0.47, Z: -9.80]` | Escala: `1.35` | Rotación Y: `356.0°` | Rol: Arbolado urbano frondoso - Árbol Emblemático Esquina
- **laurel_sureste_4** (Laurel de la India Sureste #4): Posición `[X: 11.20, Y: 0.47, Z: -7.40]` | Escala: `1.30` | Rotación Y: `39.0°` | Rol: Arbolado urbano frondoso - Alineación Andador X (Interior)
- **laurel_sureste_5** (Laurel de la India Sureste #5): Posición `[X: 15.80, Y: 0.47, Z: -7.20]` | Escala: `1.25` | Rotación Y: `82.0°` | Rol: Arbolado urbano frondoso - Alineación Andador X (Exterior)
- **laurel_sureste_6** (Laurel de la India Sureste #6): Posición `[X: 19.20, Y: 0.47, Z: -7.60]` | Escala: `1.15` | Rotación Y: `125.0°` | Rol: Arbolado urbano frondoso - Buffer Perimetral X
- **laurel_sureste_7** (Laurel de la India Sureste #7): Posición `[X: 7.60, Y: 0.47, Z: -19.20]` | Escala: `1.15` | Rotación Y: `168.0°` | Rol: Arbolado urbano frondoso - Buffer Perimetral Z

#### G. Arbustos Topiarios Diagonales (4 arbustos)
- **topiario_esquina_noreste**: Posición `[X: 20.50, Y: 0.52, Z: 20.50]` | Rotación Y: `45.0°` | Zona: Esquina Diagonal Noreste
- **topiario_esquina_noroeste**: Posición `[X: -20.50, Y: 0.52, Z: 20.50]` | Rotación Y: `135.0°` | Zona: Esquina Diagonal Noroeste
- **topiario_esquina_suroeste**: Posición `[X: -20.50, Y: 0.52, Z: -20.50]` | Rotación Y: `225.0°` | Zona: Esquina Diagonal Suroeste
- **topiario_esquina_sureste**: Posición `[X: 20.50, Y: 0.52, Z: -20.50]` | Rotación Y: `315.0°` | Zona: Esquina Diagonal Sureste

#### H. Portal de Mercaderes - Arquería Oeste (13 columnas a lo largo de X = -21.80m)
- **columna_portal_1**: Posición `[X: -21.80, Y: 0.01, Z: -23.80]` | Altura: 5.3m
- **columna_portal_2**: Posición `[X: -21.80, Y: 0.01, Z: -19.83]` | Altura: 5.3m
- **columna_portal_3**: Posición `[X: -21.80, Y: 0.01, Z: -15.87]` | Altura: 5.3m
- **columna_portal_4**: Posición `[X: -21.80, Y: 0.01, Z: -11.90]` | Altura: 5.3m
- **columna_portal_5**: Posición `[X: -21.80, Y: 0.01, Z: -7.93]` | Altura: 5.3m
- **columna_portal_6**: Posición `[X: -21.80, Y: 0.01, Z: -3.97]` | Altura: 5.3m
- **columna_portal_7**: Posición `[X: -21.80, Y: 0.01, Z: 0.00]` | Altura: 5.3m
- **columna_portal_8**: Posición `[X: -21.80, Y: 0.01, Z: 3.97]` | Altura: 5.3m
- **columna_portal_9**: Posición `[X: -21.80, Y: 0.01, Z: 7.93]` | Altura: 5.3m
- **columna_portal_10**: Posición `[X: -21.80, Y: 0.01, Z: 11.90]` | Altura: 5.3m
- **columna_portal_11**: Posición `[X: -21.80, Y: 0.01, Z: 15.87]` | Altura: 5.3m
- **columna_portal_12**: Posición `[X: -21.80, Y: 0.01, Z: 19.83]` | Altura: 5.3m
- **columna_portal_13**: Posición `[X: -21.80, Y: 0.01, Z: 23.80]` | Altura: 5.3m

---

### 4. INSTRUCCIONES PARA LA IA RECEPTORA:
1. **Para Three.js / React Three Fiber**:
   Crea instancias reutilizando las geometrías de cada tipo (`InstancedMesh` para árboles, bancas y faroles) aplicando la matriz de transformación dada por `position`, `rotation` y `scale`.
2. **Para Blender Python**:
   Lee la lista de objetos o el archivo JSON adjunto e importa los OBJ una sola vez, luego usa `object.data.copy()` o `bpy.ops.object.duplicate(linked=True)` para instanciar en cada posición.
3. **Para Unreal Engine / Unity**:
   Genera un Actor Spawner o Prefab Spawner que recorra las coordenadas y asigne el Blueprint o Prefab correspondiente.
