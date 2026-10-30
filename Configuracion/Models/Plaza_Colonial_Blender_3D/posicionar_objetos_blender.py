"""
===================================================================
Script de Posicionamiento Automático para Blender 3.x / 4.x
Generado automáticamente para Inteligencias Artificiales y Diseñadores 3D.
Instancia y posiciona exactamente cada elemento del Plano Maestro de la Plaza.
===================================================================
"""

import bpy
import os
import math
import json

# Matriz completa de coordenadas (Mapeada a Blender Z-Up)
OBJECT_COORDINATES = [
  {
    "id": "kiosko_central_01",
    "name": "Kiosko Colonial Octagonal",
    "cat": "estructura_central",
    "model": "kiosko_colonial.obj",
    "x": 0,
    "y": 0,
    "z": 0.38,
    "rot_z_deg": 0,
    "scale": 1.25,
    "zone": "Esplanada Circular Central"
  },
  {
    "id": "farol_esplanada_1",
    "name": "Farol Esplanada (NE_A)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": 18.2,
    "y": 12.27,
    "z": 0.57,
    "rot_z_deg": 34,
    "scale": 0.95,
    "zone": "Esplanada Circular Central"
  },
  {
    "id": "farol_esplanada_2",
    "name": "Farol Esplanada (NE_B)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": 12.27,
    "y": 18.2,
    "z": 0.57,
    "rot_z_deg": 56,
    "scale": 0.95,
    "zone": "Esplanada Circular Central"
  },
  {
    "id": "farol_esplanada_3",
    "name": "Farol Esplanada (NW_A)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": -12.27,
    "y": 18.2,
    "z": 0.57,
    "rot_z_deg": 124,
    "scale": 0.95,
    "zone": "Esplanada Circular Central"
  },
  {
    "id": "farol_esplanada_4",
    "name": "Farol Esplanada (NW_B)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": -18.2,
    "y": 12.27,
    "z": 0.57,
    "rot_z_deg": 146,
    "scale": 0.95,
    "zone": "Esplanada Circular Central"
  },
  {
    "id": "farol_esplanada_5",
    "name": "Farol Esplanada (SW_A)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": -18.2,
    "y": -12.27,
    "z": 0.57,
    "rot_z_deg": 214,
    "scale": 0.95,
    "zone": "Esplanada Circular Central"
  },
  {
    "id": "farol_esplanada_6",
    "name": "Farol Esplanada (SW_B)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": -12.27,
    "y": -18.2,
    "z": 0.57,
    "rot_z_deg": 236,
    "scale": 0.95,
    "zone": "Esplanada Circular Central"
  },
  {
    "id": "farol_esplanada_7",
    "name": "Farol Esplanada (SE_A)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": 12.27,
    "y": -18.2,
    "z": 0.57,
    "rot_z_deg": 304,
    "scale": 0.95,
    "zone": "Esplanada Circular Central"
  },
  {
    "id": "farol_esplanada_8",
    "name": "Farol Esplanada (SE_B)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": 18.2,
    "y": -12.27,
    "z": 0.57,
    "rot_z_deg": 326,
    "scale": 0.95,
    "zone": "Esplanada Circular Central"
  },
  {
    "id": "banca_patio_noreste_n",
    "name": "Banca Patio Noreste (Eje Cardinal)",
    "cat": "banca",
    "model": "banca_colonial.obj",
    "x": 28,
    "y": 35.7,
    "z": 0.272,
    "rot_z_deg": -180,
    "scale": 1,
    "zone": "Patio Noreste"
  },
  {
    "id": "banca_patio_noreste_ext",
    "name": "Banca Patio Noreste (Lateral Exterior)",
    "cat": "banca",
    "model": "banca_colonial.obj",
    "x": 35.7,
    "y": 28,
    "z": 0.272,
    "rot_z_deg": 90,
    "scale": 1,
    "zone": "Patio Noreste"
  },
  {
    "id": "banca_patio_noreste_int",
    "name": "Banca Patio Noreste (Lateral Interior)",
    "cat": "banca",
    "model": "banca_colonial.obj",
    "x": 20.3,
    "y": 28,
    "z": 0.272,
    "rot_z_deg": -90,
    "scale": 1,
    "zone": "Patio Noreste"
  },
  {
    "id": "farol_patio_noreste_1",
    "name": "Farol Borde Patio Noreste A",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": 25,
    "y": 39.5,
    "z": 0.372,
    "rot_z_deg": 0,
    "scale": 0.95,
    "zone": "Patio Noreste"
  },
  {
    "id": "farol_patio_noreste_2",
    "name": "Farol Borde Patio Noreste B",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": 39.5,
    "y": 25,
    "z": 0.372,
    "rot_z_deg": -90,
    "scale": 0.95,
    "zone": "Patio Noreste"
  },
  {
    "id": "laurel_noreste_1",
    "name": "Laurel de la India Noreste #1",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": 12,
    "y": 36.5,
    "z": 0.57,
    "rot_z_deg": 0,
    "scale": 1.48,
    "zone": "Jardinera en L Noreste"
  },
  {
    "id": "laurel_noreste_2",
    "name": "Laurel de la India Noreste #2",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": 12,
    "y": 29.2,
    "z": 0.57,
    "rot_z_deg": -43,
    "scale": 1.55,
    "zone": "Jardinera en L Noreste"
  },
  {
    "id": "laurel_noreste_3",
    "name": "Laurel de la India Noreste #3",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": 12,
    "y": 22,
    "z": 0.57,
    "rot_z_deg": -86,
    "scale": 1.42,
    "zone": "Jardinera en L Noreste"
  },
  {
    "id": "laurel_noreste_4",
    "name": "Laurel de la India Noreste #4",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": 16.5,
    "y": 16.5,
    "z": 0.57,
    "rot_z_deg": -129,
    "scale": 1.62,
    "zone": "Jardinera en L Noreste"
  },
  {
    "id": "laurel_noreste_5",
    "name": "Laurel de la India Noreste #5",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": 22,
    "y": 12,
    "z": 0.57,
    "rot_z_deg": -172,
    "scale": 1.44,
    "zone": "Jardinera en L Noreste"
  },
  {
    "id": "laurel_noreste_6",
    "name": "Laurel de la India Noreste #6",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": 29.2,
    "y": 12,
    "z": 0.57,
    "rot_z_deg": -215,
    "scale": 1.52,
    "zone": "Jardinera en L Noreste"
  },
  {
    "id": "laurel_noreste_7",
    "name": "Laurel de la India Noreste #7",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": 36.5,
    "y": 12,
    "z": 0.57,
    "rot_z_deg": -258,
    "scale": 1.46,
    "zone": "Jardinera en L Noreste"
  },
  {
    "id": "topiario_esquina_noreste",
    "name": "Arbusto Topiario Jardinera Noreste",
    "cat": "topiario",
    "model": "arbusto_topiario.obj",
    "x": 9.2,
    "y": 25.6,
    "z": 0.57,
    "rot_z_deg": -45,
    "scale": 1,
    "zone": "Jardinera en L Noreste"
  },
  {
    "id": "banca_patio_noroeste_n",
    "name": "Banca Patio Noroeste (Eje Cardinal)",
    "cat": "banca",
    "model": "banca_colonial.obj",
    "x": -28,
    "y": 35.7,
    "z": 0.272,
    "rot_z_deg": -180,
    "scale": 1,
    "zone": "Patio Noroeste"
  },
  {
    "id": "banca_patio_noroeste_ext",
    "name": "Banca Patio Noroeste (Lateral Exterior)",
    "cat": "banca",
    "model": "banca_colonial.obj",
    "x": -35.7,
    "y": 28,
    "z": 0.272,
    "rot_z_deg": -90,
    "scale": 1,
    "zone": "Patio Noroeste"
  },
  {
    "id": "banca_patio_noroeste_int",
    "name": "Banca Patio Noroeste (Lateral Interior)",
    "cat": "banca",
    "model": "banca_colonial.obj",
    "x": -20.3,
    "y": 28,
    "z": 0.272,
    "rot_z_deg": 90,
    "scale": 1,
    "zone": "Patio Noroeste"
  },
  {
    "id": "farol_patio_noroeste_1",
    "name": "Farol Borde Patio Noroeste A",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": -25,
    "y": 39.5,
    "z": 0.372,
    "rot_z_deg": -90,
    "scale": 0.95,
    "zone": "Patio Noroeste"
  },
  {
    "id": "farol_patio_noroeste_2",
    "name": "Farol Borde Patio Noroeste B",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": -39.5,
    "y": 25,
    "z": 0.372,
    "rot_z_deg": -180,
    "scale": 0.95,
    "zone": "Patio Noroeste"
  },
  {
    "id": "laurel_noroeste_1",
    "name": "Laurel de la India Noroeste #1",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": -12,
    "y": 36.5,
    "z": 0.57,
    "rot_z_deg": -90,
    "scale": 1.48,
    "zone": "Jardinera en L Noroeste"
  },
  {
    "id": "laurel_noroeste_2",
    "name": "Laurel de la India Noroeste #2",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": -12,
    "y": 29.2,
    "z": 0.57,
    "rot_z_deg": -133,
    "scale": 1.55,
    "zone": "Jardinera en L Noroeste"
  },
  {
    "id": "laurel_noroeste_3",
    "name": "Laurel de la India Noroeste #3",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": -12,
    "y": 22,
    "z": 0.57,
    "rot_z_deg": -176,
    "scale": 1.42,
    "zone": "Jardinera en L Noroeste"
  },
  {
    "id": "laurel_noroeste_4",
    "name": "Laurel de la India Noroeste #4",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": -16.5,
    "y": 16.5,
    "z": 0.57,
    "rot_z_deg": -219,
    "scale": 1.62,
    "zone": "Jardinera en L Noroeste"
  },
  {
    "id": "laurel_noroeste_5",
    "name": "Laurel de la India Noroeste #5",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": -22,
    "y": 12,
    "z": 0.57,
    "rot_z_deg": -262,
    "scale": 1.44,
    "zone": "Jardinera en L Noroeste"
  },
  {
    "id": "laurel_noroeste_6",
    "name": "Laurel de la India Noroeste #6",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": -29.2,
    "y": 12,
    "z": 0.57,
    "rot_z_deg": -305,
    "scale": 1.52,
    "zone": "Jardinera en L Noroeste"
  },
  {
    "id": "laurel_noroeste_7",
    "name": "Laurel de la India Noroeste #7",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": -36.5,
    "y": 12,
    "z": 0.57,
    "rot_z_deg": -348,
    "scale": 1.46,
    "zone": "Jardinera en L Noroeste"
  },
  {
    "id": "topiario_esquina_noroeste",
    "name": "Arbusto Topiario Jardinera Noroeste",
    "cat": "topiario",
    "model": "arbusto_topiario.obj",
    "x": -9.2,
    "y": 25.6,
    "z": 0.57,
    "rot_z_deg": -135,
    "scale": 1,
    "zone": "Jardinera en L Noroeste"
  },
  {
    "id": "banca_patio_suroeste_n",
    "name": "Banca Patio Suroeste (Eje Cardinal)",
    "cat": "banca",
    "model": "banca_colonial.obj",
    "x": -28,
    "y": -35.7,
    "z": 0.272,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Patio Suroeste"
  },
  {
    "id": "banca_patio_suroeste_ext",
    "name": "Banca Patio Suroeste (Lateral Exterior)",
    "cat": "banca",
    "model": "banca_colonial.obj",
    "x": -35.7,
    "y": -28,
    "z": 0.272,
    "rot_z_deg": -90,
    "scale": 1,
    "zone": "Patio Suroeste"
  },
  {
    "id": "banca_patio_suroeste_int",
    "name": "Banca Patio Suroeste (Lateral Interior)",
    "cat": "banca",
    "model": "banca_colonial.obj",
    "x": -20.3,
    "y": -28,
    "z": 0.272,
    "rot_z_deg": 90,
    "scale": 1,
    "zone": "Patio Suroeste"
  },
  {
    "id": "farol_patio_suroeste_1",
    "name": "Farol Borde Patio Suroeste A",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": -25,
    "y": -39.5,
    "z": 0.372,
    "rot_z_deg": -180,
    "scale": 0.95,
    "zone": "Patio Suroeste"
  },
  {
    "id": "farol_patio_suroeste_2",
    "name": "Farol Borde Patio Suroeste B",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": -39.5,
    "y": -25,
    "z": 0.372,
    "rot_z_deg": -270,
    "scale": 0.95,
    "zone": "Patio Suroeste"
  },
  {
    "id": "laurel_suroeste_1",
    "name": "Laurel de la India Suroeste #1",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": -12,
    "y": -36.5,
    "z": 0.57,
    "rot_z_deg": -180,
    "scale": 1.48,
    "zone": "Jardinera en L Suroeste"
  },
  {
    "id": "laurel_suroeste_2",
    "name": "Laurel de la India Suroeste #2",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": -12,
    "y": -29.2,
    "z": 0.57,
    "rot_z_deg": -223,
    "scale": 1.55,
    "zone": "Jardinera en L Suroeste"
  },
  {
    "id": "laurel_suroeste_3",
    "name": "Laurel de la India Suroeste #3",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": -12,
    "y": -22,
    "z": 0.57,
    "rot_z_deg": -266,
    "scale": 1.42,
    "zone": "Jardinera en L Suroeste"
  },
  {
    "id": "laurel_suroeste_4",
    "name": "Laurel de la India Suroeste #4",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": -16.5,
    "y": -16.5,
    "z": 0.57,
    "rot_z_deg": -309,
    "scale": 1.62,
    "zone": "Jardinera en L Suroeste"
  },
  {
    "id": "laurel_suroeste_5",
    "name": "Laurel de la India Suroeste #5",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": -22,
    "y": -12,
    "z": 0.57,
    "rot_z_deg": -352,
    "scale": 1.44,
    "zone": "Jardinera en L Suroeste"
  },
  {
    "id": "laurel_suroeste_6",
    "name": "Laurel de la India Suroeste #6",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": -29.2,
    "y": -12,
    "z": 0.57,
    "rot_z_deg": -35,
    "scale": 1.52,
    "zone": "Jardinera en L Suroeste"
  },
  {
    "id": "laurel_suroeste_7",
    "name": "Laurel de la India Suroeste #7",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": -36.5,
    "y": -12,
    "z": 0.57,
    "rot_z_deg": -78,
    "scale": 1.46,
    "zone": "Jardinera en L Suroeste"
  },
  {
    "id": "topiario_esquina_suroeste",
    "name": "Arbusto Topiario Jardinera Suroeste",
    "cat": "topiario",
    "model": "arbusto_topiario.obj",
    "x": -9.2,
    "y": -25.6,
    "z": 0.57,
    "rot_z_deg": -225,
    "scale": 1,
    "zone": "Jardinera en L Suroeste"
  },
  {
    "id": "banca_patio_sureste_n",
    "name": "Banca Patio Sureste (Eje Cardinal)",
    "cat": "banca",
    "model": "banca_colonial.obj",
    "x": 28,
    "y": -35.7,
    "z": 0.272,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Patio Sureste"
  },
  {
    "id": "banca_patio_sureste_ext",
    "name": "Banca Patio Sureste (Lateral Exterior)",
    "cat": "banca",
    "model": "banca_colonial.obj",
    "x": 35.7,
    "y": -28,
    "z": 0.272,
    "rot_z_deg": 90,
    "scale": 1,
    "zone": "Patio Sureste"
  },
  {
    "id": "banca_patio_sureste_int",
    "name": "Banca Patio Sureste (Lateral Interior)",
    "cat": "banca",
    "model": "banca_colonial.obj",
    "x": 20.3,
    "y": -28,
    "z": 0.272,
    "rot_z_deg": -90,
    "scale": 1,
    "zone": "Patio Sureste"
  },
  {
    "id": "farol_patio_sureste_1",
    "name": "Farol Borde Patio Sureste A",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": 25,
    "y": -39.5,
    "z": 0.372,
    "rot_z_deg": -270,
    "scale": 0.95,
    "zone": "Patio Sureste"
  },
  {
    "id": "farol_patio_sureste_2",
    "name": "Farol Borde Patio Sureste B",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": 39.5,
    "y": -25,
    "z": 0.372,
    "rot_z_deg": -360,
    "scale": 0.95,
    "zone": "Patio Sureste"
  },
  {
    "id": "laurel_sureste_1",
    "name": "Laurel de la India Sureste #1",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": 12,
    "y": -36.5,
    "z": 0.57,
    "rot_z_deg": -270,
    "scale": 1.48,
    "zone": "Jardinera en L Sureste"
  },
  {
    "id": "laurel_sureste_2",
    "name": "Laurel de la India Sureste #2",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": 12,
    "y": -29.2,
    "z": 0.57,
    "rot_z_deg": -313,
    "scale": 1.55,
    "zone": "Jardinera en L Sureste"
  },
  {
    "id": "laurel_sureste_3",
    "name": "Laurel de la India Sureste #3",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": 12,
    "y": -22,
    "z": 0.57,
    "rot_z_deg": -356,
    "scale": 1.42,
    "zone": "Jardinera en L Sureste"
  },
  {
    "id": "laurel_sureste_4",
    "name": "Laurel de la India Sureste #4",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": 16.5,
    "y": -16.5,
    "z": 0.57,
    "rot_z_deg": -39,
    "scale": 1.62,
    "zone": "Jardinera en L Sureste"
  },
  {
    "id": "laurel_sureste_5",
    "name": "Laurel de la India Sureste #5",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": 22,
    "y": -12,
    "z": 0.57,
    "rot_z_deg": -82,
    "scale": 1.44,
    "zone": "Jardinera en L Sureste"
  },
  {
    "id": "laurel_sureste_6",
    "name": "Laurel de la India Sureste #6",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": 29.2,
    "y": -12,
    "z": 0.57,
    "rot_z_deg": -125,
    "scale": 1.52,
    "zone": "Jardinera en L Sureste"
  },
  {
    "id": "laurel_sureste_7",
    "name": "Laurel de la India Sureste #7",
    "cat": "arbol",
    "model": "laurel_de_la_india.obj",
    "x": 36.5,
    "y": -12,
    "z": 0.57,
    "rot_z_deg": -168,
    "scale": 1.46,
    "zone": "Jardinera en L Sureste"
  },
  {
    "id": "topiario_esquina_sureste",
    "name": "Arbusto Topiario Jardinera Sureste",
    "cat": "topiario",
    "model": "arbusto_topiario.obj",
    "x": 9.2,
    "y": -25.6,
    "z": 0.57,
    "rot_z_deg": -315,
    "scale": 1,
    "zone": "Jardinera en L Sureste"
  },
  {
    "id": "banca_andador_n_o",
    "name": "Banca Andador Norte (Oeste)",
    "cat": "banca",
    "model": "banca_colonial.obj",
    "x": -6.35,
    "y": 29.2,
    "z": 0.15,
    "rot_z_deg": -90,
    "scale": 0.95,
    "zone": "Andador Norte"
  },
  {
    "id": "banca_andador_n_e",
    "name": "Banca Andador Norte (Este)",
    "cat": "banca",
    "model": "banca_colonial.obj",
    "x": 6.35,
    "y": 29.2,
    "z": 0.15,
    "rot_z_deg": 90,
    "scale": 0.95,
    "zone": "Andador Norte"
  },
  {
    "id": "banca_andador_s_o",
    "name": "Banca Andador Sur (Oeste)",
    "cat": "banca",
    "model": "banca_colonial.obj",
    "x": -6.35,
    "y": -29.2,
    "z": 0.15,
    "rot_z_deg": -90,
    "scale": 0.95,
    "zone": "Andador Sur"
  },
  {
    "id": "banca_andador_s_e",
    "name": "Banca Andador Sur (Este)",
    "cat": "banca",
    "model": "banca_colonial.obj",
    "x": 6.35,
    "y": -29.2,
    "z": 0.15,
    "rot_z_deg": 90,
    "scale": 0.95,
    "zone": "Andador Sur"
  },
  {
    "id": "banca_andador_e_s",
    "name": "Banca Andador Este (Sur)",
    "cat": "banca",
    "model": "banca_colonial.obj",
    "x": 29.2,
    "y": -6.35,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 0.95,
    "zone": "Andador Este"
  },
  {
    "id": "banca_andador_e_n",
    "name": "Banca Andador Este (Norte)",
    "cat": "banca",
    "model": "banca_colonial.obj",
    "x": 29.2,
    "y": 6.35,
    "z": 0.15,
    "rot_z_deg": -180,
    "scale": 0.95,
    "zone": "Andador Este"
  },
  {
    "id": "banca_andador_w_s",
    "name": "Banca Andador Oeste (Sur)",
    "cat": "banca",
    "model": "banca_colonial.obj",
    "x": -29.2,
    "y": -6.35,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 0.95,
    "zone": "Andador Oeste"
  },
  {
    "id": "banca_andador_w_n",
    "name": "Banca Andador Oeste (Norte)",
    "cat": "banca",
    "model": "banca_colonial.obj",
    "x": -29.2,
    "y": 6.35,
    "z": 0.15,
    "rot_z_deg": -180,
    "scale": 0.95,
    "zone": "Andador Oeste"
  },
  {
    "id": "farol_avenida_n_o_1",
    "name": "Farol Andador Norte (Oeste Int)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": -7.45,
    "y": 22.8,
    "z": 0.59,
    "rot_z_deg": 0,
    "scale": 0.95,
    "zone": "Andador Norte"
  },
  {
    "id": "farol_avenida_n_o_2",
    "name": "Farol Andador Norte (Oeste Ext)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": -7.45,
    "y": 35.6,
    "z": 0.59,
    "rot_z_deg": 0,
    "scale": 0.95,
    "zone": "Andador Norte"
  },
  {
    "id": "farol_avenida_n_e_1",
    "name": "Farol Andador Norte (Este Int)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": 7.45,
    "y": 22.8,
    "z": 0.59,
    "rot_z_deg": 0,
    "scale": 0.95,
    "zone": "Andador Norte"
  },
  {
    "id": "farol_avenida_n_e_2",
    "name": "Farol Andador Norte (Este Ext)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": 7.45,
    "y": 35.6,
    "z": 0.59,
    "rot_z_deg": 0,
    "scale": 0.95,
    "zone": "Andador Norte"
  },
  {
    "id": "farol_avenida_s_o_1",
    "name": "Farol Andador Sur (Oeste Int)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": -7.45,
    "y": -22.8,
    "z": 0.59,
    "rot_z_deg": 0,
    "scale": 0.95,
    "zone": "Andador Sur"
  },
  {
    "id": "farol_avenida_s_o_2",
    "name": "Farol Andador Sur (Oeste Ext)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": -7.45,
    "y": -35.6,
    "z": 0.59,
    "rot_z_deg": 0,
    "scale": 0.95,
    "zone": "Andador Sur"
  },
  {
    "id": "farol_avenida_s_e_1",
    "name": "Farol Andador Sur (Este Int)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": 7.45,
    "y": -22.8,
    "z": 0.59,
    "rot_z_deg": 0,
    "scale": 0.95,
    "zone": "Andador Sur"
  },
  {
    "id": "farol_avenida_s_e_2",
    "name": "Farol Andador Sur (Este Ext)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": 7.45,
    "y": -35.6,
    "z": 0.59,
    "rot_z_deg": 0,
    "scale": 0.95,
    "zone": "Andador Sur"
  },
  {
    "id": "farol_avenida_e_s_1",
    "name": "Farol Andador Este (Sur Int)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": 22.8,
    "y": -7.45,
    "z": 0.59,
    "rot_z_deg": 0,
    "scale": 0.95,
    "zone": "Andador Este"
  },
  {
    "id": "farol_avenida_e_s_2",
    "name": "Farol Andador Este (Sur Ext)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": 35.6,
    "y": -7.45,
    "z": 0.59,
    "rot_z_deg": 0,
    "scale": 0.95,
    "zone": "Andador Este"
  },
  {
    "id": "farol_avenida_e_n_1",
    "name": "Farol Andador Este (Norte Int)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": 22.8,
    "y": 7.45,
    "z": 0.59,
    "rot_z_deg": 0,
    "scale": 0.95,
    "zone": "Andador Este"
  },
  {
    "id": "farol_avenida_e_n_2",
    "name": "Farol Andador Este (Norte Ext)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": 35.6,
    "y": 7.45,
    "z": 0.59,
    "rot_z_deg": 0,
    "scale": 0.95,
    "zone": "Andador Este"
  },
  {
    "id": "farol_avenida_w_s_1",
    "name": "Farol Andador Oeste (Sur Int)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": -22.8,
    "y": -7.45,
    "z": 0.59,
    "rot_z_deg": 0,
    "scale": 0.95,
    "zone": "Andador Oeste"
  },
  {
    "id": "farol_avenida_w_s_2",
    "name": "Farol Andador Oeste (Sur Ext)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": -35.6,
    "y": -7.45,
    "z": 0.59,
    "rot_z_deg": 0,
    "scale": 0.95,
    "zone": "Andador Oeste"
  },
  {
    "id": "farol_avenida_w_n_1",
    "name": "Farol Andador Oeste (Norte Int)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": -22.8,
    "y": 7.45,
    "z": 0.59,
    "rot_z_deg": 0,
    "scale": 0.95,
    "zone": "Andador Oeste"
  },
  {
    "id": "farol_avenida_w_n_2",
    "name": "Farol Andador Oeste (Norte Ext)",
    "cat": "farol",
    "model": "farol_colonial.obj",
    "x": -35.6,
    "y": 7.45,
    "z": 0.59,
    "rot_z_deg": 0,
    "scale": 0.95,
    "zone": "Andador Oeste"
  },
  {
    "id": "columna_portal_1",
    "name": "Columna Portal de Mercaderes #1",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": -46,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_2",
    "name": "Columna Portal de Mercaderes #2",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": -42.17,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_3",
    "name": "Columna Portal de Mercaderes #3",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": -38.33,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_4",
    "name": "Columna Portal de Mercaderes #4",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": -34.5,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_5",
    "name": "Columna Portal de Mercaderes #5",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": -30.67,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_6",
    "name": "Columna Portal de Mercaderes #6",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": -26.83,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_7",
    "name": "Columna Portal de Mercaderes #7",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": -23,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_8",
    "name": "Columna Portal de Mercaderes #8",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": -19.17,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_9",
    "name": "Columna Portal de Mercaderes #9",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": -15.33,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_10",
    "name": "Columna Portal de Mercaderes #10",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": -11.5,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_11",
    "name": "Columna Portal de Mercaderes #11",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": -7.67,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_12",
    "name": "Columna Portal de Mercaderes #12",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": -3.83,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_13",
    "name": "Columna Portal de Mercaderes #13",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": 0,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_14",
    "name": "Columna Portal de Mercaderes #14",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": 3.83,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_15",
    "name": "Columna Portal de Mercaderes #15",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": 7.67,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_16",
    "name": "Columna Portal de Mercaderes #16",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": 11.5,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_17",
    "name": "Columna Portal de Mercaderes #17",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": 15.33,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_18",
    "name": "Columna Portal de Mercaderes #18",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": 19.17,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_19",
    "name": "Columna Portal de Mercaderes #19",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": 23,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_20",
    "name": "Columna Portal de Mercaderes #20",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": 26.83,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_21",
    "name": "Columna Portal de Mercaderes #21",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": 30.67,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_22",
    "name": "Columna Portal de Mercaderes #22",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": 34.5,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_23",
    "name": "Columna Portal de Mercaderes #23",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": 38.33,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_24",
    "name": "Columna Portal de Mercaderes #24",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": 42.17,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  },
  {
    "id": "columna_portal_25",
    "name": "Columna Portal de Mercaderes #25",
    "cat": "columna_portal",
    "model": "plaza_plano_maestro.obj",
    "x": -46.5,
    "y": 46,
    "z": 0.15,
    "rot_z_deg": 0,
    "scale": 1,
    "zone": "Portal de Mercaderes (Oeste)"
  }
]

def clear_existing_instances(collection_name="Plaza_Instancias_IA"):
    if collection_name in bpy.data.collections:
        col = bpy.data.collections[collection_name]
        for obj in list(col.objects):
            bpy.data.objects.remove(obj, do_unlink=True)
        bpy.data.collections.remove(col)

def create_or_get_collection(name):
    if name not in bpy.data.collections:
        col = bpy.data.collections.new(name)
        bpy.context.scene.collection.children.link(col)
        return col
    return bpy.data.collections[name]

def setup_scene_from_coordinates():
    script_dir = os.path.dirname(bpy.data.filepath) if bpy.data.filepath else os.path.expanduser("~")
    print(f"Directorio de trabajo: {script_dir}")
    
    root_col = create_or_get_collection("Plaza_Colonial_Plano_Maestro")
    sub_collections = {
        "kiosko": create_or_get_collection("01_Kiosko"),
        "arbol": create_or_get_collection("02_Laureles_India"),
        "banca": create_or_get_collection("03_Bancas_Coloniales"),
        "farol": create_or_get_collection("04_Faroles"),
        "topiario": create_or_get_collection("05_Topiarios"),
        "portal": create_or_get_collection("06_Portal_Mercaderes")
    }

    # Caché de modelos base importados
    base_prototypes = {}

    print(f"Posicionando {len(OBJECT_COORDINATES)} objetos en la escena...")

    for item in OBJECT_COORDINATES:
        model_file = item["model"]
        obj_name = item["name"]
        cat = item["cat"]

        # Si el archivo OBJ existe en la carpeta, se importa como prototipo
        obj_path = os.path.join(script_dir, model_file)
        
        # Determinar colección destino
        target_col = root_col
        for key in sub_collections:
            if key in cat or key in item["id"]:
                target_col = sub_collections[key]
                break

        # Si ya existe un prototipo base, instanciar como Linked Duplicate (Optimiza memoria VRAM)
        if model_file in base_prototypes:
            base_mesh_obj = base_prototypes[model_file]
            new_obj = bpy.data.objects.new(obj_name, base_mesh_obj.data)
            target_col.objects.link(new_obj)
        elif os.path.exists(obj_path):
            # Importar el OBJ por primera vez
            if hasattr(bpy.ops.wm, 'obj_import'):
                bpy.ops.wm.obj_import(filepath=obj_path)
            else:
                bpy.ops.import_scene.obj(filepath=obj_path)
            
            imported_obj = bpy.context.selected_objects[0]
            imported_obj.name = f"Prototipo_{model_file}"
            base_prototypes[model_file] = imported_obj
            new_obj = imported_obj
            # Mover a colección destino
            if new_obj.name not in target_col.objects:
                target_col.objects.link(new_obj)
        else:
            # Si aún no se importó el .obj, crear un marcador visual (Empty / Cubo)
            mesh = bpy.data.meshes.new(f"Mesh_{item['id']}")
            new_obj = bpy.data.objects.new(obj_name, mesh)
            target_col.objects.link(new_obj)
            new_obj.empty_display_type = 'CUBE'
            new_obj.empty_display_size = item["scale"]

        # Aplicar coordenadas exactas de posición (Blender: X, Z->Y, Y->Z)
        new_obj.location = (item["x"], item["y"], item["z"])
        new_obj.rotation_euler = (0, 0, math.radians(item["rot_z_deg"]))
        new_obj.scale = (item["scale"], item["scale"], item["scale"])

        # Asignar propiedades personalizadas para consultas
        new_obj["id"] = item["id"]
        new_obj["categoria"] = item["cat"]
        new_obj["zona"] = item["zone"]

    print("¡Posicionamiento completado exitosamente! Total de objetos:", len(OBJECT_COORDINATES))

if __name__ == "__main__":
    setup_scene_from_coordinates()
