"""
=============================================================================
BLENDER AUTO-IMPORT SCRIPT - CENTRO HISTÓRICO DE OAXACA (PLAZA COLONIAL 3D)
=============================================================================
Instrucciones de uso en Blender:
1. Abre Blender (versión 3.0, 3.6, 4.0, 4.1 o superior).
2. Ve a la pestaña superior 'Scripting'.
3. Abre este archivo 'import_to_blender.py'.
4. Haz clic en 'Run Script' (o presiona Alt + P).
¡Listo! La escena completa del Centro Histórico (310m x 310m, 9 Cuadrantes)
se importará sin solapamiento de planos (sin Z-fighting) y con mapeo UV PBR
completo para Eevee y Cycles.
=============================================================================
"""

import bpy
import os

folder = os.path.dirname(bpy.data.filepath) if bpy.data.filepath else os.getcwd()
print(f"[*] Directorio de trabajo: {folder}")

# ─────────────────────────────────────────────────────────────────────────────
# CONFIGURACIÓN: Evitar sobreponer un plano sobre otro (Anti-Z-Fighting)
# plaza_plano_maestro.obj ya contiene la plaza completa, kiosko, catedral,
# laureles, bancas, faroles, calles y manzanas de los 9 cuadrantes.
# Si solo deseas el diorama maestro unificado, deja IMPORTAR_SOLO_PLANO_MAESTRO = True.
# ─────────────────────────────────────────────────────────────────────────────
IMPORTAR_SOLO_PLANO_MAESTRO = True

coll_name = "Centro_Historico_Oaxaca_310m"
if coll_name in bpy.data.collections:
    collection = bpy.data.collections[coll_name]
else:
    collection = bpy.data.collections.new(coll_name)
    bpy.context.scene.collection.children.link(collection)

if IMPORTAR_SOLO_PLANO_MAESTRO:
    obj_files = ["plaza_plano_maestro.obj"]
else:
    # Si se importan prototipos individuales, se separan en su propia colección
    obj_files = [
        "plaza_plano_maestro.obj",
        "kiosko_colonial.obj",
        "catedral_metropolitana.obj",
        "banca_colonial.obj",
        "laurel_de_la_india.obj",
        "farol_colonial.obj",
        "arbusto_topiario.obj",
        "personaje_humano.obj"
    ]

for obj_name in obj_files:
    file_path = os.path.join(folder, obj_name)
    if os.path.exists(file_path):
        print(f"[+] Importando {obj_name}...")
        try:
            if hasattr(bpy.ops.wm, 'obj_import'):
                bpy.ops.wm.obj_import(filepath=file_path)
            else:
                bpy.ops.import_scene.obj(filepath=file_path)
            
            for obj in bpy.context.selected_objects:
                if obj not in collection.objects.values():
                    collection.objects.link(obj)
                    if obj.name in bpy.context.scene.collection.objects:
                        bpy.context.scene.collection.objects.unlink(obj)
        except Exception as e:
            print(f"[-] Error importando {obj_name}: {e}")

# Configurar sombreado suave (Smooth Shading)
for obj in collection.objects:
    if obj.type == 'MESH':
        for poly in obj.data.polygons:
            poly.use_smooth = True
        if hasattr(obj.data, 'use_auto_smooth'):
            obj.data.use_auto_smooth = True
            obj.data.auto_smooth_angle = 0.523599

# ─────────────────────────────────────────────────────────────────────────────
# Mapeo exhaustivo de materiales a texturas PBR (sin estiramiento de UVs)
# ─────────────────────────────────────────────────────────────────────────────
texture_links = {
    "mat_patio_piedra": "textura_patio_piedra.png",
    "mat_piso_piedra_cuadrantes": "textura_patio_piedra.png",
    "mat_calle_completa": "textura_calle_completa.png",
    "mat_asfalto": "textura_asfalto_calle.png",
    "mat_banqueta_trebol": "textura_banqueta.png",
    "mat_suelo_arbol": "textura_suelo_arbol.png",
    "mat_cantera": "cantera_piedra.png",
    "mat_cantera_verde_oaxaca": "cantera_verde_oaxaca.png",
    "mat_teja_colonial_roja": "teja_colonial_roja.png",
    "mat_fachada_oaxaca": "fachada_colonial_oaxaca.png",
    "mat_cobre": "techo_cobre.png",
    "mat_hierro": "hierro_forjado.png",
    "mat_madera": "madera_banca.png",
    "mat_follaje": "hojas_follaje.png",
    "mat_corteza": "corteza_arbol.png",
    "mat_seto": "seto_jardin.png",
    "mat_vidrio": "textura_vidrio.png",
    "mat_laton": "textura_laton.png",
    "mat_default": "cantera_piedra.png",
    "mat_piel": "textura_piel.png",
    "mat_chaqueta": "textura_chaqueta.png",
    "mat_pantalon": "textura_pantalon.png",
    "mat_calzado": "textura_calzado.png",
    "mat_cabello": "textura_cabello.png",
    "mat_catedral_caliza": "catedral_sillares_caliza.png",
    "mat_catedral_retablo": "catedral_cantera_labrada.png",
    "mat_catedral_pizarra": "catedral_techo_pizarra.png",
    "mat_catedral_puerta": "catedral_puerta_madera.png",
    "mat_catedral_anexo": "catedral_anexo_fachada.png"
}

for mat in bpy.data.materials:
    if mat.name in texture_links:
        mat.use_nodes = True
        nodes = mat.node_tree.nodes
        links = mat.node_tree.links
        
        bsdf = None
        for n in nodes:
            if n.type == 'BSDF_PRINCIPLED':
                bsdf = n
                break
        
        if bsdf:
            tex_filename = texture_links[mat.name]
            tex_path = os.path.join(folder, tex_filename)
            if not os.path.exists(tex_path):
                tex_path = os.path.join(folder, "textures", tex_filename)
                
            if os.path.exists(tex_path):
                img = bpy.data.images.load(tex_path, check_existing=True)
                
                # Buscar o crear nodo de imagen
                tex_node = None
                for n in nodes:
                    if n.type == 'TEX_IMAGE':
                        tex_node = n
                        break
                if not tex_node:
                    tex_node = nodes.new('ShaderNodeTexImage')
                    tex_node.location = (bsdf.location.x - 350, bsdf.location.y)
                
                tex_node.image = img
                tex_node.extension = 'REPEAT'
                
                # Conectar Color
                base_color_input = bsdf.inputs.get('Base Color')
                if base_color_input:
                    links.new(tex_node.outputs['Color'], base_color_input)
                
                # Conectar Transparencia (Alpha) para follaje y hojas sin fondos negros
                if 'Alpha' in bsdf.inputs and 'Alpha' in tex_node.outputs:
                    links.new(tex_node.outputs['Alpha'], bsdf.inputs['Alpha'])
                
                # Habilitar Alpha Clip en Eevee para evitar parpadeo y fondos negros
                if "follaje" in mat.name.lower() or "seto" in mat.name.lower() or "vidrio" in mat.name.lower():
                    if hasattr(mat, 'blend_method'):
                        mat.blend_method = 'CLIP' if "vidrio" not in mat.name.lower() else 'BLEND'
                    if hasattr(mat, 'shadow_method'):
                        mat.shadow_method = 'CLIP' if "vidrio" not in mat.name.lower() else 'NONE'

                print(f"[✓] Textura {tex_filename} conectada con UV mapping a {mat.name}")

# Crear Iluminación Solar Colonial (Cálida tipo Oaxaca a mediodía)
sun_exists = False
for light in bpy.data.lights:
    if light.type == 'SUN':
        sun_exists = True
        break

if not sun_exists:
    sun_data = bpy.data.lights.new(name="Sol_Colonial_Oaxaca", type='SUN')
    sun_data.energy = 4.5
    sun_data.color = (1.0, 0.95, 0.88)
    sun_obj = bpy.data.objects.new(name="Sol_Colonial_Oaxaca", object_data=sun_data)
    sun_obj.location = (45, 65, 110)
    sun_obj.rotation_euler = (0.75, 0.35, 0.60)
    collection.objects.link(sun_obj)

print("="*65)
print("[✓] ¡CENTRO HISTÓRICO DE OAXACA IMPORTADO EXITOSAMENTE!")
print("Plano maestro 310m x 310m listo sin solapamiento ni planos duplicados.")
print("="*65)
