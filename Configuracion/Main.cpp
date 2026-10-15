#include<iostream>
#include<vector>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Character.h"
#include "Model.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const GLint WIDTH = 800, HEIGHT = 600;
// Camara inicial con vista isometrica del terreno completo
Camera camera(glm::vec3(0.0f, 5.8f, 6.2f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -43.0f);
bool keys[1024] = {};
GLfloat lastX = 400.0f, lastY = 300.0f;
bool firstMouse = true;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void DoMovement();
void UpdateWindowTitle(GLFWwindow* window);

Character* controlledCharacter = nullptr;
bool characterControlMode = true;
bool followCharacterCamera = true;
GLfloat tpsDistance = 0.55f;

// Shaders
const GLchar* vertexShaderSource = 
{
	"#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"
	"void main()\n"
	"{\n"
	"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
	"}\0" 
};
const GLchar* fragmentShaderSource = 
{
	"#version 330 core\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0"
};

// Funciones de configuracion del shader

void CrearShader(void);




int OldTriangleMain() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 0", nullptr, nullptr);
	
	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificaci�n de errores de creacion  ventana
	if (nullptr == window) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);

	//CrearShader();

	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f, // Left
		0.5f, -0.5f, 0.0f, // Right
		0.0f,  0.5f, 0.0f  // Top
	};


	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	



	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void CrearShader()
{
    // Creamos el vertex shader y guardamos su identificador
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);


	// Verificamos los errores en tiempo de ejecuci�n
	GLint success;
	GLchar infoLog[512];


	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	// Creamos el fragment shader y guardamos su identificador
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Verificamos los errores en tiempo de ejecuci�n

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Creamos un nuevo programa y se asignamos
	// sus correspondientes vertex y fragment shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Verificamos que no hay error en el programa
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


}

int main()
{
	if (glfwInit() != GLFW_TRUE)
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return EXIT_FAILURE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Zocalo de Oaxaca – Vista del Terreno", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetScrollCallback(window, ScrollCallback);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glEnable(GL_DEPTH_TEST);
	// Alpha cutout para follaje
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader shader("Shader/modelLoading.vs", "Shader/modelLoading.frag");

	// ── Terreno: Plaza Zocalo – 7 zonas texturizadas segun el plano
	// (piso base, calles, banquetas, andadores, rotonda, tierra, jardineras)
	char plazaPath[] = "Models/Plaza_Zocalo.obj";
	Model plaza(plazaPath);

	// ── Personaje controlable
	char characterPath[] = "Models/ASIAN_MAN_rigged.glb";
	Character character(characterPath, 0.14f);
	controlledCharacter = &character;

	// ── Arbol (mesh unico, instanciado por cuadrante)
	char treePath[] = "Models/arbol_plaza.obj";
	Model treeModel(treePath);

	UpdateWindowTitle(window);

	// Proyeccion: near corto para ver detalles, far amplio para toda la plaza
	glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()),
		static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 0.0001f, 120.0f);

	// ─────────────────────────────────────────────────────────────────────
	// Posiciones de arboles alineadas con las zonas de TIERRA (AreaVerde)
	// del Plaza_Zocalo.obj. Solo en AreaVerde, NUNCA en Jardineras/Andadores.
	//
	// Zonas AreaVerde por cuadrante:
	//   NW – Norte: x[-2.85,-0.40] z[-2.85,-1.50]
	//   NW – Oeste: x[-2.85,-2.05] z[-1.50,-0.40]
	//   NE – Norte: x[+0.40,+2.85] z[-2.85,-1.50]
	//   NE – Este:  x[+2.05,+2.85] z[-1.50,-0.40]
	//   SW – Sur:   x[-2.85,-0.40] z[+1.50,+2.85]
	//   SW – Oeste: x[-2.85,-2.05] z[+0.40,+1.50]
	//   SE – Sur:   x[+0.40,+2.85] z[+1.50,+2.85]
	//   SE – Este:  x[+2.05,+2.85] z[+0.40,+1.50]
	//
	// Formato: { x, z, escala }
	// ─────────────────────────────────────────────────────────────────────
	struct TreeInstance { float x, z, scale; };

	const std::vector<TreeInstance> trees = {
		// ── Cuadrante NW – bloque Norte (x[-2.85,-0.40] z[-2.85,-1.50])
		{ -2.40f, -2.50f, 0.90f },
		{ -1.70f, -2.40f, 0.82f },
		{ -1.00f, -2.30f, 0.78f },
		{ -2.60f, -1.80f, 0.86f },
		{ -1.90f, -1.70f, 0.80f },
		{ -1.20f, -1.60f, 0.76f },
		{ -0.70f, -2.10f, 0.72f },

		// ── Cuadrante NW – bloque Oeste (x[-2.85,-2.05] z[-1.50,-0.40])
		{ -2.55f, -1.10f, 0.74f },
		{ -2.45f, -0.75f, 0.70f },

		// ── Cuadrante NE – bloque Norte (x[+0.40,+2.85] z[-2.85,-1.50])
		{  0.90f, -2.30f, 0.76f },
		{  1.60f, -2.40f, 0.82f },
		{  2.30f, -2.50f, 0.88f },
		{  1.10f, -1.65f, 0.74f },
		{  1.85f, -1.70f, 0.80f },
		{  2.55f, -1.80f, 0.84f },
		{  0.65f, -2.10f, 0.70f },

		// ── Cuadrante NE – bloque Este (x[+2.05,+2.85] z[-1.50,-0.40])
		{  2.45f, -1.10f, 0.72f },
		{  2.55f, -0.75f, 0.68f },

		// ── Cuadrante SW – bloque Sur (x[-2.85,-0.40] z[+1.50,+2.85])
		{ -2.40f,  2.50f, 0.90f },
		{ -1.70f,  2.40f, 0.84f },
		{ -1.00f,  2.30f, 0.78f },
		{ -2.60f,  1.80f, 0.86f },
		{ -1.90f,  1.70f, 0.80f },
		{ -1.20f,  1.60f, 0.76f },
		{ -0.70f,  2.10f, 0.72f },

		// ── Cuadrante SW – bloque Oeste (x[-2.85,-2.05] z[+0.40,+1.50])
		{ -2.55f,  0.75f, 0.70f },
		{ -2.45f,  1.10f, 0.74f },

		// ── Cuadrante SE – bloque Sur (x[+0.40,+2.85] z[+1.50,+2.85])
		{  0.90f,  2.30f, 0.76f },
		{  1.60f,  2.40f, 0.82f },
		{  2.30f,  2.50f, 0.88f },
		{  1.10f,  1.65f, 0.76f },
		{  1.85f,  1.70f, 0.80f },
		{  2.55f,  1.80f, 0.84f },
		{  0.65f,  2.10f, 0.72f },

		// ── Cuadrante SE – bloque Este (x[+2.05,+2.85] z[+0.40,+1.50])
		{  2.45f,  0.75f, 0.70f },
		{  2.55f,  1.10f, 0.72f },
	};

	// ────────────────────────────────────────────────────────────────────────
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = static_cast<GLfloat>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		DoMovement();

		// Animacion de personaje con cadencia sincronizada a la velocidad de translacion
		float charSpeed = glm::length(glm::vec2(character.GetVelocity().x, character.GetVelocity().z));
		float animPlayRate = character.IsMoving() ? std::max(0.6f, charSpeed / 0.30f) : 1.0f;
		character.UpdateAnimation(character.IsMoving() ? "Walk" : "Idle", deltaTime * animPlayRate);

		// Cielo de dia (azul claro)
		glClearColor(0.53f, 0.81f, 0.94f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();

		// Luz solar desde arriba-delante (dia)
		glUniform3f(glGetUniformLocation(shader.Program, "light.position"),  2.0f, 8.0f, 4.0f);
		glUniform3f(glGetUniformLocation(shader.Program, "light.ambient"),   0.55f, 0.52f, 0.45f);
		glUniform3f(glGetUniformLocation(shader.Program, "light.diffuse"),   0.90f, 0.88f, 0.80f);
		glUniform3f(glGetUniformLocation(shader.Program, "light.specular"),  0.20f, 0.20f, 0.18f);
		glUniform3f(glGetUniformLocation(shader.Program, "material.ambient"),  1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(shader.Program, "material.diffuse"),  1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(shader.Program, "material.specular"), 0.06f, 0.06f, 0.06f);

		// Vista con seguimiento de personaje estilo videojuego tercera persona
		glm::mat4 view = camera.GetViewMatrix();
		glm::vec3 activeViewPos = camera.GetPosition();

		if (characterControlMode && followCharacterCamera)
		{
			const glm::vec3 characterPosition = character.GetPosition();
			const float charScale = character.GetModelScale();
			// Foco en el pecho/hombros del personaje
			const glm::vec3 target = characterPosition + glm::vec3(0.0f, charScale * 1.35f, 0.0f);

			// Direccion frontal de la camara (manejada por mouse)
			glm::vec3 front = camera.GetFront();

			// Posicion deseada orbitando detras y arriba del personaje
			glm::vec3 desiredPos = target - front * tpsDistance;

			// Evitar que la camara baje del suelo
			if (desiredPos.y < 0.025f)
				desiredPos.y = 0.025f;

			// Suavizado cinemático estilo videojuego moderno (lerp exponencial)
			static glm::vec3 currentTPSPos = desiredPos;
			static bool initTPS = true;
			if (initTPS)
			{
				currentTPSPos = desiredPos;
				initTPS = false;
			}
			else
			{
				float tpsLerp = std::min(1.0f, 12.0f * deltaTime);
				currentTPSPos = glm::mix(currentTPSPos, desiredPos, tpsLerp);
			}

			view = glm::lookAt(currentTPSPos, target, glm::vec3(0.0f, 1.0f, 0.0f));
			activeViewPos = currentTPSPos;
		}

		// Posicion de vista para iluminacion especular en el shader
		glUniform3f(glGetUniformLocation(shader.Program, "viewPos"),
			activeViewPos.x, activeViewPos.y, activeViewPos.z);

		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

		// ── Terreno / Plaza (7 zonas texturizadas segun el plano arquitectonico)
		// Zona 1: Base Pavimento interior
		// Zona 2: Calles exteriores (asfalto)
		// Zona 3: Banquetas perimetrales
		// Zona 4: Andadores principales en cruz (piedra)
		// Zona 5: Rotonda central (banqueta + pavimento)
		// Zona 6: Tierra / suelo de arboles (textura_suelo_arbol)
		// Zona 7: Jardineras Formales (textura_patio_piedra)
		glm::mat4 model(1.0f);
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		plaza.Draw(shader);

		// ── Arboles en zonas de tierra (SOLO en AreaVerde, no en Jardineras)
		for (const auto& t : trees)
		{
			glm::mat4 tMat(1.0f);
			tMat = glm::translate(tMat, glm::vec3(t.x, 0.0f, t.z));
			tMat = glm::scale(tMat, glm::vec3(t.scale));
			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(tMat));
			treeModel.Draw(shader);
		}

		// ── Personaje
		model = character.GetModelMatrix();
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		character.Draw(shader);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}


void DoMovement()
{
	if (characterControlMode && controlledCharacter != nullptr)
	{
		controlledCharacter->Update(deltaTime, keys, camera.GetFront());
		return;
	}

	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if ((key == GLFW_KEY_8 || key == GLFW_KEY_KP_8) && action == GLFW_PRESS && controlledCharacter != nullptr)
	{
		characterControlMode = !characterControlMode;
		UpdateWindowTitle(window);
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS && characterControlMode)
	{
		followCharacterCamera = !followCharacterCamera;
		UpdateWindowTitle(window);
	}

	if (key >= 0 && key < 1024)
		keys[key] = action != GLFW_RELEASE;
}

void UpdateWindowTitle(GLFWwindow* window)
{
	if (!characterControlMode)
		glfwSetWindowTitle(window, "Zocalo de Oaxaca | Camara Libre (8: Modo Personaje)");
	else if (followCharacterCamera)
		glfwSetWindowTitle(window, "Zocalo de Oaxaca | Tercera Persona [WASD: Caminar | Mouse: Orbitar | Rueda: Zoom | C: Libre]");
	else
		glfwSetWindowTitle(window, "Zocalo de Oaxaca | Personaje (C: Camara Tercera Persona)");
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = static_cast<GLfloat>(xPos);
		lastY = static_cast<GLfloat>(yPos);
		firstMouse = false;
	}

	GLfloat xOffset = static_cast<GLfloat>(xPos) - lastX;
	GLfloat yOffset = lastY - static_cast<GLfloat>(yPos);
	lastX = static_cast<GLfloat>(xPos);
	lastY = static_cast<GLfloat>(yPos);
	camera.ProcessMouseMovement(xOffset, yOffset);

	if (characterControlMode && followCharacterCamera)
	{
		camera.ClampPitch(-65.0f, 20.0f);
	}
}

void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	tpsDistance -= static_cast<GLfloat>(yOffset) * 0.05f;
	if (tpsDistance < 0.20f) tpsDistance = 0.20f;
	if (tpsDistance > 1.80f) tpsDistance = 1.80f;
}

