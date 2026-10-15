# Plan de orquestación del proyecto

## Recorrido virtual: Noche de los Rábanos

| Dato | Definición |
|---|---|
| Equipo | Equipo 4 |
| Curso | Computación Gráfica e Interacción Humano-Computadora, semestre 2027-1 |
| Fecha de corte de este plan | 9 de octubre de 2026 |
| Periodo propuesto | 7 de octubre–25 de noviembre de 2026 |
| Estado | Arranque y validaciones iniciales; aprobación del profesor y estado del repositorio por confirmar |
| Base técnica actual | Visual Studio, C++, OpenGL, GLFW, GLEW, GLM, Assimp y SOIL2 |

> Este documento organiza la ejecución a partir de la propuesta del equipo y los requisitos del curso. La aprobación del profesor es una puerta de control: cualquier cambio de celebración o alcance obligatorio debe acordarse con él. Los requisitos oficiales del curso prevalecen si difieren de la propuesta.

## 1. Objetivo

Construir una experiencia 3D interactiva en tiempo real que permita recorrer una representación del Zócalo de Oaxaca de Juárez durante la Noche de los Rábanos. El usuario deberá poder desplazarse por el espacio, explorar puestos y consultar información breve y documentada sobre las esculturas de rábano, el totomoxtle, la flor inmortal y el contexto de la celebración.

La experiencia debe demostrar técnicas de computación gráfica vistas en el curso, conservar una representación cultural respetuosa y ser reproducible desde el proyecto de Visual Studio entregado.

## 2. Decisiones de alcance

### Compromisos del equipo

- Mantener C++ y OpenGL para el renderizado, en vez de migrar a Unity o Godot; esta elección permite implementar y explicar directamente cámara, transformaciones, mallas, texturas, iluminación e interacción.
- Usar Blender para crear y preparar la mayor parte del escenario y sus objetos. Los recursos externos se limitarán a los necesarios y llevarán créditos y licencia.
- Representar el Zócalo, el kiosco y pasillos con puestos de exhibición; la distribución exacta de las seis zonas debe quedar fijada en el plano y storyboard del segundo corte.
- Entregar cinco animaciones vinculadas con acciones de la celebración, como propone el equipo. La modalidad del curso (laboratorio o teoría) se debe confirmar con el profesor; el documento de requisitos marca mínimos distintos (2 y 5, respectivamente).
- Mantener un recorrido explorable con puntos de interacción y fichas culturales breves, no una secuencia de pantallas de texto.

### Fuera del alcance obligatorio

- Migrar a un motor de juego, construir una aplicación web o implementar multijugador.
- Añadir audio espacial, partículas complejas, efectos avanzados o personajes adicionales antes de cerrar navegación, contenidos, animaciones y documentación.
- Simular físicamente el tallado. La propuesta permite representar la acción con poses, jerarquías y cambios de estado del modelo.

Los elementos opcionales solo entran al backlog cuando los criterios obligatorios estén integrados y probados.

## 3. Estado de partida y primera verificación

El repositorio ya contiene una solución de Visual Studio y una implementación preliminar de carga de modelos, cámara, shaders e importación mediante Assimp. También están presentes `RedDog.obj`, su material y textura. Esto sirve para probar la tubería de importación, pero no constituye todavía el entorno cultural del proyecto.

Hay dos puntos de entrada visibles: [Main.cpp](Configuracion/Main.cpp) contiene una práctica de triángulo y [Carga de Modelos.cpp](Configuracion/Carga%20de%20Modelos.cpp) contiene la escena de carga de modelos. El archivo de proyecto incluye este último como fuente de compilación. Antes de agregar funcionalidades, compilar y ejecutar la configuración acordada (preferentemente x64 Debug) desde una copia limpia y registrar el resultado. Verificar también las rutas de bibliotecas x64, DLL y recursos relativos; no asumir que el ejecutable existente demuestra una compilación reproducible.

**Resultado esperado del primer corte:** una compilación reproducible, repositorio exclusivo accesible para el equipo, tablero de tareas y alcance aprobado o con observaciones anotadas.

## 4. Requisitos y criterios de aceptación

| ID | Requisito | Criterio verificable |
|---|---|---|
| R1 | Entorno cultural | Plaza y puestos reconocibles, con geometría desarrollada por el equipo y distribución aprobada en plano/storyboard. |
| R2 | Recorrido | El usuario se desplaza por el entorno; cámara, límites transitables y salida funcionan de forma consistente. |
| R3 | Interacción cultural | Se pueden seleccionar puntos u objetos y consultar fichas legibles con información respaldada por fuentes. |
| R4 | Gráficos | Mallas, transformaciones, texturas y luz funcionan en la escena integrada; los materiales son coherentes con los objetos representados. |
| R5 | Animación | Cinco secuencias completas, reproducibles, relacionadas con la celebración y aprobadas en la propuesta; al menos una usa KeyFrames. No reutilizar animaciones de prácticas. |
| R6 | Cultura y licencias | Cada elemento cultural tiene fuente de justificación; cada recurso externo tiene autor, fuente, licencia y crédito. |
| R7 | Entrega ejecutable | El proyecto compila desde una copia limpia en Visual Studio e incluye código y recursos necesarios. |
| R8 | Evidencias | Repositorio exclusivo con actividad continua, tres videos distintos, manual de usuario PDF y manual técnico PDF. |
| R9 | Gestión y documentación | Se conservan tablero, revisiones, cronograma real, responsabilidades ejecutadas, pruebas y evidencias de colaboración para el manual técnico. |

**Definición de terminado para cada tarea:** cumple su criterio de aceptación, compila cuando corresponda, está integrada en la rama principal, tiene evidencia (captura, video o prueba), incluye atribuciones necesarias y recibió revisión de otro integrante.

## 5. Experiencia mínima del usuario

1. Iniciar en un punto claro de la plaza y reconocer la distribución general.
2. Recorrer libremente los pasillos y acercarse a las piezas expuestas.
3. Activar una ficha contextual de una pieza o estación y cerrarla sin perder la navegación.
4. Observar al menos una animación desde una ubicación que permita entender la acción.
5. Salir de la experiencia de manera clara.

Como propuesta inicial, usar WASD o flechas para desplazarse, mouse para orientar la cámara, una tecla de interacción para abrir/cerrar fichas y Escape para salir. Confirmar y documentar los controles antes del segundo corte. Si la selección con cursor requiere ocultar o capturar el mouse, resolverlo explícitamente para que la navegación y la interacción no compitan.

## 6. Plan de animaciones

Las cinco animaciones previstas son:

| ID | Secuencia | Técnica y prueba de aceptación |
|---|---|---|
| A1 | Tallado de un rábano | KeyFrames para torso, brazos y herramienta; la secuencia presenta acercamiento, corte y retirada. Puede alternar versiones de la pieza en lugar de simular un corte físico. |
| A2 | Montaje de una figura de totomoxtle | La pieza sigue la mano durante el traslado y queda asociada a la estructura al terminar. |
| A3 | Visitante recorre los puestos | Sigue una trayectoria, se detiene ante una obra, la mira y continúa. |
| A4 | Composición de flor inmortal | Presenta tomar, colocar y ajustar; la flor pasa de la mano a la composición. |
| A5 | Colocación de una escultura | El artesano levanta, gira, coloca y suelta la pieza sin atravesar el pedestal; usar KeyFrames y jerarquías. |

Definir para cada secuencia duración, estados o fotogramas, objetos implicados, evento de inicio, forma de repetición y responsable de integración. Probar cada animación en una escena pequeña antes de integrarla a los puestos. Los ciclos decorativos de luz o humo no cuentan como sustituto de estas secuencias.

## 7. Cronograma y entregables

El cronograma conserva las fechas planteadas por el equipo. Como el periodo ya comenzó, la primera revisión debe validar qué tareas están realmente hechas y reajustar capacidad sin mover la entrega final sin autorización.

| Corte | Fecha | Prioridad y actividades | Entregable de salida | Coordinación |
|---|---|---|---|---|
| 1 | 13 oct 2026 | Aprobar alcance con profesor; cerrar fuentes culturales, seis zonas y cinco animaciones; compilar base; crear repositorio y backlog. | Alcance y criterios acordados, fichas de fuentes, tablero activo y compilación inicial documentada. | RAC |
| 2 | 20 oct 2026 | Terminar plano/storyboard; crear blockout, cámara y límites; importar un modelo de prueba; definir controles e interacción. | Escena gris recorrible con escala común y un modelo importado. | SLC |
| 3 | 27 oct 2026 | Modelar kiosco, piso, jardineras y seis puestos modulares; probar colisiones y escala. | Escenario base exportado desde Blender e integrado en OpenGL. | CPD |
| 4 | 3 nov 2026 | Crear tres esculturas de rábano, una de totomoxtle y una de flor; preparar personaje, UV y texturas. | Activos nombrados, con pivotes acordados, texturas y licencias registradas. | CPD |
| 5 | 10 nov 2026 | Integrar modelos; completar iluminación, colisiones y fichas culturales; probar entrada y salida de la experiencia. | Recorrido integrado con seis zonas, fichas legibles y límites transitables. | SLC |
| 6 | 17 nov 2026 | Producir e integrar A1–A5; sincronizar personajes y objetos; hacer revisión cruzada de animaciones. | Cinco secuencias reproducibles, fuentes editables y video de evidencia. | CPD + SLC |
| 7 | 24 nov 2026 | Revisar textos, fuentes y licencias; corregir fallos; preparar manuales y tres videos; probar en una copia limpia. | Versión candidata, lista de pruebas, manuales y videos revisados. | RAC |
| Cierre | 25 nov 2026 | Compilar desde copia limpia, comprobar recursos, empaquetar y ensayar demostración. | Proyecto Visual Studio, repositorio, recursos, manuales, evidencias y presentación listos. | SLC |

**Capacidad estimada en la propuesta:** 12 horas por integrante por semana completa y 4 horas de cierre; total estimado de 88 horas por persona y 264 horas de equipo. Registrar las horas reales semanalmente y renegociar el alcance si el avance cae detrás de un corte.

## 8. Responsables y coordinación

Abreviaturas: RAC = Rea Alberto Cristian; CPD = Cadena Palafox Diego Aarón; SLC = Sánchez Luján César Ricardo. La persona responsable coordina y presenta el resultado; no significa que trabaje sin apoyo. Todos participan en pruebas y revisión cruzada.

| Área | Responsable | Apoyo / consulta |
|---|---|---|
| Investigación cultural, organización y documentación | RAC | CPD y SLC revisan la correspondencia entre fuente y representación. |
| Plano y storyboard | RAC | CPD aporta restricciones de modelado; SLC valida recorrido e interacción. |
| Modelado, UV, texturas, rigging y animación | CPD | SLC valida pivotes, escala e integración; RAC valida contexto cultural. |
| C++/OpenGL, cámara, carga de modelos, interacción y colisiones | SLC | CPD prepara recursos integrables; RAC prueba claridad de uso y contenido. |
| Iluminación | SLC | CPD apoya con materiales; RAC revisa legibilidad y atmósfera. |
| Repositorio y compilación integrada | SLC | Cada integrante entrega cambios pequeños y revisables. |
| Pruebas | SLC coordina | RAC ejecuta pruebas de recorrido y documentación; CPD prueba activos y animaciones. |
| Manuales, fuentes y entregables | RAC coordina | CPD documenta herramientas/animaciones; SLC documenta arquitectura y compilación. |

La Matriz RACI propuesta en la propuesta inicial debe conservarse en el repositorio y actualizarse al final para reflejar las contribuciones reales. No presentar la asignación planeada como evidencia de trabajo ya ejecutado.

## 9. Método de trabajo

Usar Scrum académico adaptado, con cortes semanales y cuatro revisiones de incremento: 20 de octubre, 3 de noviembre, 17 de noviembre y 24 de noviembre. Mantener un tablero Kanban como apoyo, con columnas `Pendiente`, `En curso`, `En revisión`, `Bloqueada` y `Terminado`, y no más de una tarea activa por persona salvo acuerdo explícito.

- **Inicio de semana:** elegir tareas del backlog que tengan responsable, dependencia y criterio de aceptación.
- **Durante la semana:** integrar con frecuencia; registrar bloqueos el mismo día; evitar que modelos, animaciones o cambios de interfaz se acumulen hasta el final.
- **Cierre de corte:** ejecutar compilación y pruebas del incremento, guardar evidencia, revisar trabajo de otra persona y actualizar riesgos y cronograma.
- **Retro breve:** anotar una cosa que funcionó, un problema y una acción concreta para el siguiente corte.

Cada integrante debe usar Git con cambios pequeños y mensajes descriptivos. Acordar un formato de recursos (`Models`, `Textures`, `Shader`, `Docs` u otro) y nombres/pivotes antes de que crezcan los activos. No subir binarios temporales, carpetas de compilación ni recursos cuya licencia no esté clara.

## 10. Pruebas y control de calidad

| Momento | Comprobación mínima |
|---|---|
| Cada integración | Compila en la configuración acordada; inicia sin faltar DLL, shader, modelo o textura; no rompe el recorrido existente. |
| Escena gris | Movimiento, orientación, límites, escala y distribución funcionan sin depender de arte final. |
| Recursos | Modelo aparece con escala, orientación, pivote y materiales correctos; ruta de textura relativa comprobada. |
| Interacciones | Cada punto abre la ficha correcta; texto se puede leer; cerrar la ficha devuelve el control al recorrido. |
| Animaciones | Inician y terminan de forma determinista; los objetos no se separan ni atraviesan superficies; la versión final usa KeyFrames. |
| Entrega | Clonar o copiar el repositorio a una carpeta limpia, abrir la solución, compilar, ejecutar y reproducir la demostración siguiendo el manual. |

Conservar una lista corta de pruebas con fecha, configuración, resultado, responsable y evidencia. Probar en el mismo equipo/configuración objetivo; registrar cualquier limitación conocida.

## 11. Riesgos y respuestas

| Riesgo | Señal temprana | Respuesta |
|---|---|---|
| La aprobación o modalidad de evaluación no está confirmada | No hay visto bueno ni claridad sobre laboratorio/teoría | Resolverlo en el primer contacto con el profesor; mantener cinco animaciones en el alcance de trabajo por ahora. |
| La solución no compila en una copia limpia | Errores de linker, DLL o rutas relativas | Validar x64/Win32 y dependencias al inicio; fijar una configuración de equipo y documentar pasos de compilación. |
| La integración de modelos y animaciones llega tarde | Activos sin escala, pivotes o nombres comunes | Acordar convenciones en el corte 2; importar un modelo de prueba; integrar cada incremento al repositorio principal. |
| Cinco animaciones superan el tiempo disponible | A1 no es reproducible al cierre del corte 5 | Prototipar pronto una secuencia KeyFrames; priorizar A1 y reutilizar una jerarquía de personaje, no reducir el mínimo sin autorización. |
| La representación cultural no está suficientemente sustentada | Objetos o textos sin fuente primaria/confiable | Mantener una matriz objeto–significado–fuente y revisión cultural antes de cerrar modelos y fichas. |
| Las fichas dificultan la navegación | Cámara y cursor compiten o el texto tapa la escena | Probar el modelo de control con usuarios del equipo en el blockout; mantener fichas breves y salida clara. |
| La documentación se deja para el último día | No hay capturas, bitácora ni evidencias semanales | Crear desde ahora carpetas de evidencias y actualizar manuales al cierre de cada corte. |
| Recursos externos carecen de licencia verificable | Archivo sin autor, URL o licencia | No integrarlo hasta registrar procedencia, licencia y crédito; preferir recursos propios. |

## 12. Decisiones que deben cerrarse

- [ ] Visto bueno formal del profesor para la Noche de los Rábanos y el espacio representado.
- [ ] Confirmar si aplica la rúbrica de laboratorio o teoría y validar las cinco animaciones propuestas.
- [ ] Fijar las seis zonas del recorrido en el plano/storyboard.
- [ ] Confirmar controles, interacción y conducta del cursor.
- [ ] Confirmar configuración de Visual Studio y arquitectura objetivo, y dejar una compilación base reproducible.
- [ ] Crear/verificar repositorio exclusivo y elegir herramienta de seguimiento (GitHub Projects o Trello).
- [ ] Revisar presupuesto y fuentes de tarifas: son estimaciones de la propuesta, no gasto aprobado.

## 13. Entrega final: lista de control

- [ ] Solución de Visual Studio completa y compilable desde copia limpia.
- [ ] Repositorio exclusivo con código, recursos, historial de cambios y licencias.
- [ ] Escena, desplazamiento, interacción, iluminación y modelos propios funcionando.
- [ ] Animaciones acordadas; al menos una desarrollada con KeyFrames y ninguna reutilizada de prácticas.
- [ ] Tres videos: entorno principal; recorrido y navegación; animaciones e interacciones culturales.
- [ ] Manual de usuario PDF con capturas e instrucciones para ejecutar, navegar e interactuar.
- [ ] Manual técnico PDF con arquitectura, tecnologías, investigación cultural, cronograma real, RACI real, metodología y evidencias, aprendizaje autónomo por integrante, animaciones, conclusiones, bibliografía APA 7 y créditos/licencias.
- [ ] Manual técnico con conclusiones técnicas, sociales, económicas, ambientales y culturales sustentadas en resultados.
- [ ] Bibliografía final con al menos cinco fuentes pertinentes y actualizadas, en formato APA 7.
- [ ] Texto individual en inglés de cada integrante.
- [ ] Ensayo de demostración y respaldo de los archivos finales.

## 14. Fuentes de trabajo

- Propuesta del equipo: `Propuesta_Equipo4_41947650_318273130_321195414.pdf`.
- Requisitos oficiales: `Requerimientos para el Proyecto Final de Computación Gráfica e Interacción Humano-Computadora Semestre 2027-1.pdf`.
- Fuentes culturales citadas en la propuesta: Sistema de Información Cultural, Gobierno de Oaxaca y referencias institucionales listadas en el PDF. Verificar cada afirmación y conservar referencias completas en formato APA 7 en el manual técnico final.
- Referencias de estado del arte de la propuesta: recorridos virtuales del INAH, Museo de las Constituciones de la UNAM y Museo Digital Memoria y Tolerancia.

---

**Regla de priorización:** primero una experiencia mínima completa y demostrable; después calidad visual; al final, extras. Si una tarea no mejora un criterio obligatorio ni reduce un riesgo de entrega, no desplaza trabajo comprometido.
