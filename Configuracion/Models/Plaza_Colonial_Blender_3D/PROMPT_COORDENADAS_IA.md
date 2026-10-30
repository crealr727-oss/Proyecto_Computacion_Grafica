# PROMPT MAESTRO DE COORDENADAS PARA INTÉRPRETE DE IA
## Conversión, Reconstrucción y Posicionamiento Espacial 3D

Eres un agente de Inteligencia Artificial especializado en Arquitectura 3D, Motores de Videojuegos (Unreal Engine 5, Unity, Godot) y Web3D (Three.js, React Three Fiber, Babylon.js, Blender Python).

A continuación se presenta el **registro geométrico y espacial exacto** de todos los modelos y objetos que componen el plano maestro del **Centro Histórico de Oaxaca (310m x 310m, 9 Cuadrantes Urbanos)**. Utiliza esta matriz de coordenadas para generar código, instanciar mallas, reconstruir la escena en cualquier motor o convertir el diseño.

---

### 1. ESPECIFICACIÓN DEL SISTEMA DE COORDENADAS
- **Unidades**: Metros del mundo real (1.0 = 1 metro).
- **Origen (0, 0, 0)**: Centro geométrico exacto de la base del Kiosko colonial octagonal en el Cuadrante 5 (Zócalo).
- **Sistema de Ejes (Three.js / WebGL / OpenGL)**:
  - **Eje X**: Horizontal Este-Oeste (+X = Este / Derecha [Palacio de Gobierno Q6], -X = Oeste / Izquierda [Catedral Metropolitana Q4]).
  - **Eje Y**: Vertical (+Y = Altura / Elevación sobre el terreno).
  - **Eje Z**: Horizontal Norte-Sur (+Z = Sur / Frente [Calle Trujano / Bustamante Q8], -Z = Norte / Fondo [Calle Independencia Q2]).
- **Conversión a Blender / Unreal Engine (Z-Up)**:
  - `X_blender = X`
  - `Y_blender = Z`
  - `Z_blender = Y`
  - `Rot_Z_blender = -Rot_Y_deg`
- **Dimensiones Totales del Terreno (Cuadrícula Urbana 3x3)**: 310.0m de ancho x 310.0m de largo (96,100 m²).
  - Cuadrante 5 (Zócalo Central): 96.0m x 96.0m con Kiosko central y 28 Laureles de la India.
  - Cuadrante 4 (Oeste): Catedral Metropolitana de Cantera Verde y gran explanada de la Alameda de León.
  - Cuadrante 6 (Este): Palacio de Gobierno del Estado y Portal de Mercaderes con arcadas coloniales.
  - Cuadrantes 1, 2, 3, 7, 8, 9: Manzanas coloniales de Oaxaca con patios interiores y techumbres de teja roja.
  - Calles perimetrales: Red vial de dos carriles de 24.0m de ancho con asfalto, banquetas de cantera y doble raya amarilla.

---

### 2. RESUMEN DE MODELOS Y ARCHIVOS DE ORIGEN (.OBJ / .MTL)
| Modelo | Archivo OBJ | Bounding Box Aprox. (m) | Rol / Descripción |
|---|---|---|---|
| Kiosko Colonial | `kiosko_colonial.obj` | 10.5 x 10.6 x 10.5 | Estructura octagonal con cúpula de cobre y base de cantera |
| Banca Colonial | `banca_colonial.obj` | 2.2 x 0.9 x 0.8 | Banca de hierro forjado y listones de madera barnizada |
| Laurel de la India | `laurel_de_la_india.obj` | 6.5 x 8.2 x 6.5 | Árbol Ficus retusa maduro de copa frondosa globular |
| Farol Colonial | `farol_colonial.obj` | 0.8 x 3.8 x 0.8 | Farol de pie colonial posicionado fuera de los pasos peatonales |
| Arbusto Topiario | `arbusto_topiario.obj` | 2.6 x 2.8 x 2.6 | Arbusto esculpido en urna de cantera con follaje orgánico isotrópico |
| Escena Completa | `plaza_plano_maestro.obj` | 160.0 x 6.5 x 160.0 | Diorama unificado con terreno ampliado, calle vehicular de 32m y portal |

---

### 3. MATRIZ DETALLADA DE COORDENADAS POR OBJETO (110 OBJETOS EN TOTAL)

#### A. Kiosko Central (1 objeto)
- **ID**: `kiosko_central_01`
- **Posición**: `X = 0.00m, Y = 0.38m, Z = 0.00m`
- **Rotación**: `Y = 0.0°`
- **Escala**: `[1.25, 1.25, 1.25]`
- **Zona**: Esplanada Circular Central

#### B. Faroles de la Esplanada Circular (8 objetos en arcos fuera del paso de las avenidas)
- **farol_esplanada_1**: Posición `[X: 18.20, Y: 0.57, Z: 12.27]` | Rotación Y: `-34.0°`
- **farol_esplanada_2**: Posición `[X: 12.27, Y: 0.57, Z: 18.20]` | Rotación Y: `-56.0°`
- **farol_esplanada_3**: Posición `[X: -12.27, Y: 0.57, Z: 18.20]` | Rotación Y: `-124.0°`
- **farol_esplanada_4**: Posición `[X: -18.20, Y: 0.57, Z: 12.27]` | Rotación Y: `-146.0°`
- **farol_esplanada_5**: Posición `[X: -18.20, Y: 0.57, Z: -12.27]` | Rotación Y: `-214.0°`
- **farol_esplanada_6**: Posición `[X: -12.27, Y: 0.57, Z: -18.20]` | Rotación Y: `-236.0°`
- **farol_esplanada_7**: Posición `[X: 12.27, Y: 0.57, Z: -18.20]` | Rotación Y: `-304.0°`
- **farol_esplanada_8**: Posición `[X: 18.20, Y: 0.57, Z: -12.27]` | Rotación Y: `-326.0°`

#### C. Bancas en Patios Formales (12 bancas - 100% Pavimentadas sobre cantera)
- **banca_patio_noreste_n** (Banca Patio Noreste (Eje Cardinal)): Posición `[X: 28.00, Y: 0.27, Z: 35.70]` | Rotación Y: `180.0°` | Zona: Patio Noreste
- **banca_patio_noreste_ext** (Banca Patio Noreste (Lateral Exterior)): Posición `[X: 35.70, Y: 0.27, Z: 28.00]` | Rotación Y: `-90.0°` | Zona: Patio Noreste
- **banca_patio_noreste_int** (Banca Patio Noreste (Lateral Interior)): Posición `[X: 20.30, Y: 0.27, Z: 28.00]` | Rotación Y: `90.0°` | Zona: Patio Noreste
- **banca_patio_noroeste_n** (Banca Patio Noroeste (Eje Cardinal)): Posición `[X: -28.00, Y: 0.27, Z: 35.70]` | Rotación Y: `180.0°` | Zona: Patio Noroeste
- **banca_patio_noroeste_ext** (Banca Patio Noroeste (Lateral Exterior)): Posición `[X: -35.70, Y: 0.27, Z: 28.00]` | Rotación Y: `90.0°` | Zona: Patio Noroeste
- **banca_patio_noroeste_int** (Banca Patio Noroeste (Lateral Interior)): Posición `[X: -20.30, Y: 0.27, Z: 28.00]` | Rotación Y: `-90.0°` | Zona: Patio Noroeste
- **banca_patio_suroeste_n** (Banca Patio Suroeste (Eje Cardinal)): Posición `[X: -28.00, Y: 0.27, Z: -35.70]` | Rotación Y: `0.0°` | Zona: Patio Suroeste
- **banca_patio_suroeste_ext** (Banca Patio Suroeste (Lateral Exterior)): Posición `[X: -35.70, Y: 0.27, Z: -28.00]` | Rotación Y: `90.0°` | Zona: Patio Suroeste
- **banca_patio_suroeste_int** (Banca Patio Suroeste (Lateral Interior)): Posición `[X: -20.30, Y: 0.27, Z: -28.00]` | Rotación Y: `-90.0°` | Zona: Patio Suroeste
- **banca_patio_sureste_n** (Banca Patio Sureste (Eje Cardinal)): Posición `[X: 28.00, Y: 0.27, Z: -35.70]` | Rotación Y: `0.0°` | Zona: Patio Sureste
- **banca_patio_sureste_ext** (Banca Patio Sureste (Lateral Exterior)): Posición `[X: 35.70, Y: 0.27, Z: -28.00]` | Rotación Y: `-90.0°` | Zona: Patio Sureste
- **banca_patio_sureste_int** (Banca Patio Sureste (Lateral Interior)): Posición `[X: 20.30, Y: 0.27, Z: -28.00]` | Rotación Y: `90.0°` | Zona: Patio Sureste

#### D. Bancas en Andadores Principales de 14.4m (8 bancas junto al brocal)
- **banca_andador_n_o** (Banca Andador Norte (Oeste)): Posición `[X: -6.35, Y: 0.15, Z: 29.20]` | Rotación Y: `90.0°` | Zona: Andador Norte
- **banca_andador_n_e** (Banca Andador Norte (Este)): Posición `[X: 6.35, Y: 0.15, Z: 29.20]` | Rotación Y: `-90.0°` | Zona: Andador Norte
- **banca_andador_s_o** (Banca Andador Sur (Oeste)): Posición `[X: -6.35, Y: 0.15, Z: -29.20]` | Rotación Y: `90.0°` | Zona: Andador Sur
- **banca_andador_s_e** (Banca Andador Sur (Este)): Posición `[X: 6.35, Y: 0.15, Z: -29.20]` | Rotación Y: `-90.0°` | Zona: Andador Sur
- **banca_andador_e_s** (Banca Andador Este (Sur)): Posición `[X: 29.20, Y: 0.15, Z: -6.35]` | Rotación Y: `0.0°` | Zona: Andador Este
- **banca_andador_e_n** (Banca Andador Este (Norte)): Posición `[X: 29.20, Y: 0.15, Z: 6.35]` | Rotación Y: `180.0°` | Zona: Andador Este
- **banca_andador_w_s** (Banca Andador Oeste (Sur)): Posición `[X: -29.20, Y: 0.15, Z: -6.35]` | Rotación Y: `0.0°` | Zona: Andador Oeste
- **banca_andador_w_n** (Banca Andador Oeste (Norte)): Posición `[X: -29.20, Y: 0.15, Z: 6.35]` | Rotación Y: `180.0°` | Zona: Andador Oeste

#### E. Faroles en Esquinas de Patios (8 faroles)
- **farol_patio_noreste_1**: Posición `[X: 25.00, Y: 0.37, Z: 39.50]` | Rotación Y: `0.0°` | Zona: Patio Noreste
- **farol_patio_noreste_2**: Posición `[X: 39.50, Y: 0.37, Z: 25.00]` | Rotación Y: `90.0°` | Zona: Patio Noreste
- **farol_patio_noroeste_1**: Posición `[X: -25.00, Y: 0.37, Z: 39.50]` | Rotación Y: `90.0°` | Zona: Patio Noroeste
- **farol_patio_noroeste_2**: Posición `[X: -39.50, Y: 0.37, Z: 25.00]` | Rotación Y: `180.0°` | Zona: Patio Noroeste
- **farol_patio_suroeste_1**: Posición `[X: -25.00, Y: 0.37, Z: -39.50]` | Rotación Y: `180.0°` | Zona: Patio Suroeste
- **farol_patio_suroeste_2**: Posición `[X: -39.50, Y: 0.37, Z: -25.00]` | Rotación Y: `270.0°` | Zona: Patio Suroeste
- **farol_patio_sureste_1**: Posición `[X: 25.00, Y: 0.37, Z: -39.50]` | Rotación Y: `270.0°` | Zona: Patio Sureste
- **farol_patio_sureste_2**: Posición `[X: 39.50, Y: 0.37, Z: -25.00]` | Rotación Y: `360.0°` | Zona: Patio Sureste

#### F. Faroles en Andadores Principales (8 faroles alineados al brocal sin obstruir el corredor)
- **farol_avenida_n_o_1**: Posición `[X: -7.45, Y: 0.59, Z: 22.80]` | Rotación Y: `0.0°` | Zona: Andador Norte
- **farol_avenida_n_o_2**: Posición `[X: -7.45, Y: 0.59, Z: 35.60]` | Rotación Y: `0.0°` | Zona: Andador Norte
- **farol_avenida_n_e_1**: Posición `[X: 7.45, Y: 0.59, Z: 22.80]` | Rotación Y: `0.0°` | Zona: Andador Norte
- **farol_avenida_n_e_2**: Posición `[X: 7.45, Y: 0.59, Z: 35.60]` | Rotación Y: `0.0°` | Zona: Andador Norte
- **farol_avenida_s_o_1**: Posición `[X: -7.45, Y: 0.59, Z: -22.80]` | Rotación Y: `0.0°` | Zona: Andador Sur
- **farol_avenida_s_o_2**: Posición `[X: -7.45, Y: 0.59, Z: -35.60]` | Rotación Y: `0.0°` | Zona: Andador Sur
- **farol_avenida_s_e_1**: Posición `[X: 7.45, Y: 0.59, Z: -22.80]` | Rotación Y: `0.0°` | Zona: Andador Sur
- **farol_avenida_s_e_2**: Posición `[X: 7.45, Y: 0.59, Z: -35.60]` | Rotación Y: `0.0°` | Zona: Andador Sur
- **farol_avenida_e_s_1**: Posición `[X: 22.80, Y: 0.59, Z: -7.45]` | Rotación Y: `0.0°` | Zona: Andador Este
- **farol_avenida_e_s_2**: Posición `[X: 35.60, Y: 0.59, Z: -7.45]` | Rotación Y: `0.0°` | Zona: Andador Este
- **farol_avenida_e_n_1**: Posición `[X: 22.80, Y: 0.59, Z: 7.45]` | Rotación Y: `0.0°` | Zona: Andador Este
- **farol_avenida_e_n_2**: Posición `[X: 35.60, Y: 0.59, Z: 7.45]` | Rotación Y: `0.0°` | Zona: Andador Este
- **farol_avenida_w_s_1**: Posición `[X: -22.80, Y: 0.59, Z: -7.45]` | Rotación Y: `0.0°` | Zona: Andador Oeste
- **farol_avenida_w_s_2**: Posición `[X: -35.60, Y: 0.59, Z: -7.45]` | Rotación Y: `0.0°` | Zona: Andador Oeste
- **farol_avenida_w_n_1**: Posición `[X: -22.80, Y: 0.59, Z: 7.45]` | Rotación Y: `0.0°` | Zona: Andador Oeste
- **farol_avenida_w_n_2**: Posición `[X: -35.60, Y: 0.59, Z: 7.45]` | Rotación Y: `0.0°` | Zona: Andador Oeste

#### G. Laureles de la India / Árboles Frondosos en Jardineras L (28 árboles)
- **laurel_noreste_1** (Laurel de la India Noreste #1): Posición `[X: 12.00, Y: 0.57, Z: 36.50]` | Escala: `1.48` | Rotación Y: `0.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo Z (Exterior)
- **laurel_noreste_2** (Laurel de la India Noreste #2): Posición `[X: 12.00, Y: 0.57, Z: 29.20]` | Escala: `1.55` | Rotación Y: `43.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo Z (Medio)
- **laurel_noreste_3** (Laurel de la India Noreste #3): Posición `[X: 12.00, Y: 0.57, Z: 22.00]` | Escala: `1.42` | Rotación Y: `86.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo Z (Interior)
- **laurel_noreste_4** (Laurel de la India Noreste #4): Posición `[X: 16.50, Y: 0.57, Z: 16.50]` | Escala: `1.62` | Rotación Y: `129.0°` | Rol: Arbolado urbano frondoso - Nodo Curvo Central de Jardinera
- **laurel_noreste_5** (Laurel de la India Noreste #5): Posición `[X: 22.00, Y: 0.57, Z: 12.00]` | Escala: `1.44` | Rotación Y: `172.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo X (Interior)
- **laurel_noreste_6** (Laurel de la India Noreste #6): Posición `[X: 29.20, Y: 0.57, Z: 12.00]` | Escala: `1.52` | Rotación Y: `215.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo X (Medio)
- **laurel_noreste_7** (Laurel de la India Noreste #7): Posición `[X: 36.50, Y: 0.57, Z: 12.00]` | Escala: `1.46` | Rotación Y: `258.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo X (Exterior)
- **laurel_noroeste_1** (Laurel de la India Noroeste #1): Posición `[X: -12.00, Y: 0.57, Z: 36.50]` | Escala: `1.48` | Rotación Y: `90.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo Z (Exterior)
- **laurel_noroeste_2** (Laurel de la India Noroeste #2): Posición `[X: -12.00, Y: 0.57, Z: 29.20]` | Escala: `1.55` | Rotación Y: `133.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo Z (Medio)
- **laurel_noroeste_3** (Laurel de la India Noroeste #3): Posición `[X: -12.00, Y: 0.57, Z: 22.00]` | Escala: `1.42` | Rotación Y: `176.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo Z (Interior)
- **laurel_noroeste_4** (Laurel de la India Noroeste #4): Posición `[X: -16.50, Y: 0.57, Z: 16.50]` | Escala: `1.62` | Rotación Y: `219.0°` | Rol: Arbolado urbano frondoso - Nodo Curvo Central de Jardinera
- **laurel_noroeste_5** (Laurel de la India Noroeste #5): Posición `[X: -22.00, Y: 0.57, Z: 12.00]` | Escala: `1.44` | Rotación Y: `262.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo X (Interior)
- **laurel_noroeste_6** (Laurel de la India Noroeste #6): Posición `[X: -29.20, Y: 0.57, Z: 12.00]` | Escala: `1.52` | Rotación Y: `305.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo X (Medio)
- **laurel_noroeste_7** (Laurel de la India Noroeste #7): Posición `[X: -36.50, Y: 0.57, Z: 12.00]` | Escala: `1.46` | Rotación Y: `348.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo X (Exterior)
- **laurel_suroeste_1** (Laurel de la India Suroeste #1): Posición `[X: -12.00, Y: 0.57, Z: -36.50]` | Escala: `1.48` | Rotación Y: `180.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo Z (Exterior)
- **laurel_suroeste_2** (Laurel de la India Suroeste #2): Posición `[X: -12.00, Y: 0.57, Z: -29.20]` | Escala: `1.55` | Rotación Y: `223.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo Z (Medio)
- **laurel_suroeste_3** (Laurel de la India Suroeste #3): Posición `[X: -12.00, Y: 0.57, Z: -22.00]` | Escala: `1.42` | Rotación Y: `266.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo Z (Interior)
- **laurel_suroeste_4** (Laurel de la India Suroeste #4): Posición `[X: -16.50, Y: 0.57, Z: -16.50]` | Escala: `1.62` | Rotación Y: `309.0°` | Rol: Arbolado urbano frondoso - Nodo Curvo Central de Jardinera
- **laurel_suroeste_5** (Laurel de la India Suroeste #5): Posición `[X: -22.00, Y: 0.57, Z: -12.00]` | Escala: `1.44` | Rotación Y: `352.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo X (Interior)
- **laurel_suroeste_6** (Laurel de la India Suroeste #6): Posición `[X: -29.20, Y: 0.57, Z: -12.00]` | Escala: `1.52` | Rotación Y: `35.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo X (Medio)
- **laurel_suroeste_7** (Laurel de la India Suroeste #7): Posición `[X: -36.50, Y: 0.57, Z: -12.00]` | Escala: `1.46` | Rotación Y: `78.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo X (Exterior)
- **laurel_sureste_1** (Laurel de la India Sureste #1): Posición `[X: 12.00, Y: 0.57, Z: -36.50]` | Escala: `1.48` | Rotación Y: `270.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo Z (Exterior)
- **laurel_sureste_2** (Laurel de la India Sureste #2): Posición `[X: 12.00, Y: 0.57, Z: -29.20]` | Escala: `1.55` | Rotación Y: `313.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo Z (Medio)
- **laurel_sureste_3** (Laurel de la India Sureste #3): Posición `[X: 12.00, Y: 0.57, Z: -22.00]` | Escala: `1.42` | Rotación Y: `356.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo Z (Interior)
- **laurel_sureste_4** (Laurel de la India Sureste #4): Posición `[X: 16.50, Y: 0.57, Z: -16.50]` | Escala: `1.62` | Rotación Y: `39.0°` | Rol: Arbolado urbano frondoso - Nodo Curvo Central de Jardinera
- **laurel_sureste_5** (Laurel de la India Sureste #5): Posición `[X: 22.00, Y: 0.57, Z: -12.00]` | Escala: `1.44` | Rotación Y: `82.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo X (Interior)
- **laurel_sureste_6** (Laurel de la India Sureste #6): Posición `[X: 29.20, Y: 0.57, Z: -12.00]` | Escala: `1.52` | Rotación Y: `125.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo X (Medio)
- **laurel_sureste_7** (Laurel de la India Sureste #7): Posición `[X: 36.50, Y: 0.57, Z: -12.00]` | Escala: `1.46` | Rotación Y: `168.0°` | Rol: Arbolado urbano frondoso - Jardinera Brazo X (Exterior)

#### H. Arbustos Topiarios Diagonales Esculpidos (4 arbustos)
- **topiario_esquina_noreste**: Posición `[X: 9.20, Y: 0.57, Z: 25.60]` | Rotación Y: `45.0°` | Zona: Jardinera en L Noreste
- **topiario_esquina_noroeste**: Posición `[X: -9.20, Y: 0.57, Z: 25.60]` | Rotación Y: `135.0°` | Zona: Jardinera en L Noroeste
- **topiario_esquina_suroeste**: Posición `[X: -9.20, Y: 0.57, Z: -25.60]` | Rotación Y: `225.0°` | Zona: Jardinera en L Suroeste
- **topiario_esquina_sureste**: Posición `[X: 9.20, Y: 0.57, Z: -25.60]` | Rotación Y: `315.0°` | Zona: Jardinera en L Sureste

#### I. Portal de Mercaderes - Arquería Oeste (25 columnas a lo largo de X = -46.50m)
- **columna_portal_1**: Posición `[X: -46.50, Y: 0.15, Z: -46.00]` | Altura: 5.80m
- **columna_portal_2**: Posición `[X: -46.50, Y: 0.15, Z: -42.17]` | Altura: 5.80m
- **columna_portal_3**: Posición `[X: -46.50, Y: 0.15, Z: -38.33]` | Altura: 5.80m
- **columna_portal_4**: Posición `[X: -46.50, Y: 0.15, Z: -34.50]` | Altura: 5.80m
- **columna_portal_5**: Posición `[X: -46.50, Y: 0.15, Z: -30.67]` | Altura: 5.80m
- **columna_portal_6**: Posición `[X: -46.50, Y: 0.15, Z: -26.83]` | Altura: 5.80m
- **columna_portal_7**: Posición `[X: -46.50, Y: 0.15, Z: -23.00]` | Altura: 5.80m
- **columna_portal_8**: Posición `[X: -46.50, Y: 0.15, Z: -19.17]` | Altura: 5.80m
- **columna_portal_9**: Posición `[X: -46.50, Y: 0.15, Z: -15.33]` | Altura: 5.80m
- **columna_portal_10**: Posición `[X: -46.50, Y: 0.15, Z: -11.50]` | Altura: 5.80m
- **columna_portal_11**: Posición `[X: -46.50, Y: 0.15, Z: -7.67]` | Altura: 5.80m
- **columna_portal_12**: Posición `[X: -46.50, Y: 0.15, Z: -3.83]` | Altura: 5.80m
- **columna_portal_13**: Posición `[X: -46.50, Y: 0.15, Z: 0.00]` | Altura: 5.80m
- **columna_portal_14**: Posición `[X: -46.50, Y: 0.15, Z: 3.83]` | Altura: 5.80m
- **columna_portal_15**: Posición `[X: -46.50, Y: 0.15, Z: 7.67]` | Altura: 5.80m
- **columna_portal_16**: Posición `[X: -46.50, Y: 0.15, Z: 11.50]` | Altura: 5.80m
- **columna_portal_17**: Posición `[X: -46.50, Y: 0.15, Z: 15.33]` | Altura: 5.80m
- **columna_portal_18**: Posición `[X: -46.50, Y: 0.15, Z: 19.17]` | Altura: 5.80m
- **columna_portal_19**: Posición `[X: -46.50, Y: 0.15, Z: 23.00]` | Altura: 5.80m
- **columna_portal_20**: Posición `[X: -46.50, Y: 0.15, Z: 26.83]` | Altura: 5.80m
- **columna_portal_21**: Posición `[X: -46.50, Y: 0.15, Z: 30.67]` | Altura: 5.80m
- **columna_portal_22**: Posición `[X: -46.50, Y: 0.15, Z: 34.50]` | Altura: 5.80m
- **columna_portal_23**: Posición `[X: -46.50, Y: 0.15, Z: 38.33]` | Altura: 5.80m
- **columna_portal_24**: Posición `[X: -46.50, Y: 0.15, Z: 42.17]` | Altura: 5.80m
- **columna_portal_25**: Posición `[X: -46.50, Y: 0.15, Z: 46.00]` | Altura: 5.80m

---

### 4. INSTRUCCIONES PARA LA IA RECEPTORA:
1. **Para Three.js / React Three Fiber**:
   Crea instancias reutilizando las geometrías de cada tipo (`InstancedMesh` para árboles, bancas y faroles) aplicando la matriz de transformación dada por `position`, `rotation` y `scale`.
2. **Para Blender Python**:
   Lee la lista de objetos o el archivo JSON adjunto e importa los OBJ una sola vez, luego usa `object.data.copy()` o `bpy.ops.object.duplicate(linked=True)` para instanciar en cada posición.
3. **Para Unreal Engine / Unity**:
   Genera un Actor Spawner o Prefab Spawner que recorra las coordenadas y asigne el Blueprint o Prefab correspondiente.
