#pragma once

#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Model.h"

// ────────────────────────────────────────────────────────────────────────────
// Personaje humanoide con esqueleto jerárquico, animación de caminata natural
// de brazos y piernas, proporciones armonizadas y acabado de contorno en OpenGL.
// ────────────────────────────────────────────────────────────────────────────
class Character
{
public:
	Character(const char* dummyPath = nullptr, GLfloat modelScale = 0.14f)
		: position(0.0f, 0.002f, 0.0f), velocity(0.0f, 0.0f, 0.0f),
		rotationY(0.0f), modelScale(modelScale), movementSpeed(0.42f), acceleration(7.5f),
		rotationSpeed(9.5f), gravity(9.81f), groundHeight(0.002f),
		collisionRadius(0.90f * modelScale + 0.02f),
		walkCycle(0.0f), idleCycle(0.0f),
		hipPitchL(0.0f), hipPitchR(0.0f), kneePitchL(0.0f), kneePitchR(0.0f), anklePitchL(0.0f), anklePitchR(0.0f),
		armPitchL(0.0f), armPitchR(0.0f), elbowPitchL(0.0f), elbowPitchR(0.0f),
		bodyBob(0.0f), bodyYaw(0.0f), torsoYaw(0.0f), torsoPitch(0.0f), torsoScaleY(1.0f)
	{
		InitMeshes();
	}

	void Update(GLfloat deltaTime, const bool* keys, const glm::vec3& cameraFront)
	{
		const GLfloat step = std::min(deltaTime, 0.05f);
		glm::vec2 forward(cameraFront.x, cameraFront.z);
		if (glm::length(forward) > 0.0f)
			forward = glm::normalize(forward);
		else
			forward = glm::vec2(0.0f, -1.0f);
		const glm::vec2 right(-forward.y, forward.x);

		glm::vec2 movement = forward * (static_cast<GLfloat>(keys[GLFW_KEY_W]) -
			static_cast<GLfloat>(keys[GLFW_KEY_S])) +
			right * (static_cast<GLfloat>(keys[GLFW_KEY_D]) -
				static_cast<GLfloat>(keys[GLFW_KEY_A]));

		const bool hasInput = glm::length(movement) > 0.0f;
		if (hasInput)
		{
			movement = glm::normalize(movement);
			const GLfloat targetRotation = std::atan2(-movement.x, -movement.y);
			const GLfloat angleDifference = std::atan2(std::sin(targetRotation - rotationY),
				std::cos(targetRotation - rotationY));
			rotationY += angleDifference * std::min(1.0f, rotationSpeed * step);
		}

		const glm::vec2 targetVelocity = hasInput
			? movement * movementSpeed
			: glm::vec2(0.0f);
		const GLfloat velocityBlend = std::min(1.0f, acceleration * step);
		velocity.x += (targetVelocity.x - velocity.x) * velocityBlend;
		velocity.z += (targetVelocity.y - velocity.z) * velocityBlend;

		velocity.y -= gravity * step;
		position += velocity * step;

		position.x = glm::clamp(position.x, terrainMinX + collisionRadius, terrainMaxX - collisionRadius);
		position.z = glm::clamp(position.z, terrainMinZ + collisionRadius, terrainMaxZ - collisionRadius);
		if (position.x == terrainMinX + collisionRadius || position.x == terrainMaxX - collisionRadius)
			velocity.x = 0.0f;
		if (position.z == terrainMinZ + collisionRadius || position.z == terrainMaxZ - collisionRadius)
			velocity.z = 0.0f;

		GLfloat hitHeight = groundHeight;
		const glm::vec3 rayOrigin(position.x, std::max(position.y + modelScale * 2.0f, groundHeight + 0.001f), position.z);
		if (RaycastGround(rayOrigin, glm::vec3(0.0f, -1.0f, 0.0f), hitHeight) && position.y <= hitHeight)
		{
			position.y = hitHeight;
			velocity.y = 0.0f;
		}
	}

	void UpdateAnimation(const string& animationName, GLfloat deltaTime)
	{
		const bool moving = IsMoving();
		const float blendSpeed = 10.0f * deltaTime;

		if (moving)
		{
			// Frecuencia de zancada sincronizada con el desplazamiento
			const float speedMag = glm::length(glm::vec2(velocity.x, velocity.z));
			const float cadence = std::max(4.0f, (speedMag / modelScale) * 2.6f);
			walkCycle += deltaTime * cadence;

			const float s = std::sin(walkCycle);
			const float c = std::cos(walkCycle);

			// Piernas: oscilación de cadera y flexión natural de rodilla en el avance
			const float targetHipL = s * 34.0f;
			const float targetKneeL = (s < 0.0f) ? (-s * 52.0f) : 3.0f;
			const float targetAnkleL = c * 14.0f;

			const float targetHipR = -s * 34.0f;
			const float targetKneeR = (-s < 0.0f) ? (s * 52.0f) : 3.0f;
			const float targetAnkleR = -c * 14.0f;

			// Brazos: contra-balanceo respecto a las piernas (brazo izquierdo acompaña pierna derecha)
			const float targetArmL = -s * 30.0f;
			const float targetElbowL = 14.0f + std::max(0.0f, -s) * 24.0f;

			const float targetArmR = s * 30.0f;
			const float targetElbowR = 14.0f + std::max(0.0f, s) * 24.0f;

			// Dinámica pélvica y del torso
			const float targetBob = -std::abs(s) * 0.016f;
			const float targetBodyYaw = s * 3.8f;
			const float targetTorsoYaw = -s * 3.2f;
			const float targetTorsoPitch = 3.5f;

			// Mezcla suave
			hipPitchL = glm::mix(hipPitchL, targetHipL, blendSpeed);
			kneePitchL = glm::mix(kneePitchL, targetKneeL, blendSpeed);
			anklePitchL = glm::mix(anklePitchL, targetAnkleL, blendSpeed);

			hipPitchR = glm::mix(hipPitchR, targetHipR, blendSpeed);
			kneePitchR = glm::mix(kneePitchR, targetKneeR, blendSpeed);
			anklePitchR = glm::mix(anklePitchR, targetAnkleR, blendSpeed);

			armPitchL = glm::mix(armPitchL, targetArmL, blendSpeed);
			elbowPitchL = glm::mix(elbowPitchL, targetElbowL, blendSpeed);

			armPitchR = glm::mix(armPitchR, targetArmR, blendSpeed);
			elbowPitchR = glm::mix(elbowPitchR, targetElbowR, blendSpeed);

			bodyBob = glm::mix(bodyBob, targetBob, blendSpeed);
			bodyYaw = glm::mix(bodyYaw, targetBodyYaw, blendSpeed);
			torsoYaw = glm::mix(torsoYaw, targetTorsoYaw, blendSpeed);
			torsoPitch = glm::mix(torsoPitch, targetTorsoPitch, blendSpeed);
			torsoScaleY = 1.0f;
		}
		else
		{
			// Modo reposo (Idle) con respiración y relajación de articulaciones
			idleCycle += deltaTime * 2.2f;
			const float breath = std::sin(idleCycle);

			hipPitchL = glm::mix(hipPitchL, 0.0f, blendSpeed * 0.8f);
			kneePitchL = glm::mix(kneePitchL, 0.0f, blendSpeed * 0.8f);
			anklePitchL = glm::mix(anklePitchL, 0.0f, blendSpeed * 0.8f);

			hipPitchR = glm::mix(hipPitchR, 0.0f, blendSpeed * 0.8f);
			kneePitchR = glm::mix(kneePitchR, 0.0f, blendSpeed * 0.8f);
			anklePitchR = glm::mix(anklePitchR, 0.0f, blendSpeed * 0.8f);

			armPitchL = glm::mix(armPitchL, breath * 1.5f, blendSpeed * 0.8f);
			elbowPitchL = glm::mix(elbowPitchL, 8.0f + breath * 1.2f, blendSpeed * 0.8f);

			armPitchR = glm::mix(armPitchR, breath * 1.5f, blendSpeed * 0.8f);
			elbowPitchR = glm::mix(elbowPitchR, 8.0f + breath * 1.2f, blendSpeed * 0.8f);

			bodyBob = glm::mix(bodyBob, 0.0f, blendSpeed);
			bodyYaw = glm::mix(bodyYaw, 0.0f, blendSpeed);
			torsoYaw = glm::mix(torsoYaw, 0.0f, blendSpeed);
			torsoPitch = glm::mix(torsoPitch, 0.0f, blendSpeed);
			torsoScaleY = 1.0f + breath * 0.014f;
		}
	}

	// ────────────────────────────────────────────────────────────────────────
	// Renderizado con Acabado de Contorno (Silhouette Outline + Rim Edge)
	// ────────────────────────────────────────────────────────────────────────
	void Draw(Shader shader)
	{
		// ── PASE 1: Contorno exterior tipo silueta (Inverted Hull en OpenGL)
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT); // Dibuja caras traseras infladas
		glDepthMask(GL_TRUE);

		glUniform1i(glGetUniformLocation(shader.Program, "hasTexture"), 0);
		glUniform1i(glGetUniformLocation(shader.Program, "enableOutline"), 2); // Modo contorno plano
		glUniform3f(glGetUniformLocation(shader.Program, "outlineColor"), 0.04f, 0.04f, 0.06f);

		RenderSkeletonHierarchy(shader, 1.034f);

		// ── PASE 2: Pase principal con texturas y acabado de contorno en bordes
		glCullFace(GL_BACK); // Culling estándar
		glUniform1i(glGetUniformLocation(shader.Program, "hasTexture"), 1);
		glUniform1i(glGetUniformLocation(shader.Program, "enableOutline"), 1); // Modo silueta suave
		glUniform3f(glGetUniformLocation(shader.Program, "outlineColor"), 0.06f, 0.06f, 0.08f);

		RenderSkeletonHierarchy(shader, 1.0f);

		// Restaurar estado para los demás modelos
		glUniform1i(glGetUniformLocation(shader.Program, "enableOutline"), 0);
	}

	glm::mat4 GetModelMatrix() const
	{
		glm::mat4 transform(1.0f);
		transform = glm::translate(transform, position);
		transform = glm::rotate(transform, rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
		return glm::scale(transform, glm::vec3(modelScale));
	}

	glm::vec3 GetPosition() const { return position; }
	glm::vec3 GetVelocity() const { return velocity; }
	GLfloat GetRotation() const { return rotationY; }
	GLfloat GetModelScale() const { return modelScale; }
	bool IsMoving() const { return glm::length(glm::vec2(velocity.x, velocity.z)) > movementSpeed * 0.08f; }

private:
	// ────────────────────────────────────────────────────────────────────────
	// Recorrido jerárquico del esqueleto y dibujo de cada extremidad
	// ────────────────────────────────────────────────────────────────────────
	void RenderSkeletonHierarchy(Shader shader, float outlineFactor)
	{
		const GLint modelLoc = glGetUniformLocation(shader.Program, "model");

		// Matriz Raíz del personaje en el mundo
		glm::mat4 root = glm::mat4(1.0f);
		root = glm::translate(root, position + glm::vec3(0.0f, bodyBob * modelScale, 0.0f));
		root = glm::rotate(root, rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
		root = glm::scale(root, glm::vec3(modelScale * outlineFactor));

		// ── 1. Pelvis / Caderas (Root del cuerpo a y = 0.88m)
		glm::mat4 mPelvis = glm::translate(root, glm::vec3(0.0f, 0.88f, 0.0f));
		mPelvis = glm::rotate(mPelvis, glm::radians(bodyYaw), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mPelvis));
		pelvisMesh->Draw(shader);

		// ── 2. Torso / Pecho (Hijo de Pelvis)
		glm::mat4 mTorso = glm::translate(mPelvis, glm::vec3(0.0f, 0.02f, 0.0f));
		mTorso = glm::rotate(mTorso, glm::radians(torsoPitch), glm::vec3(1.0f, 0.0f, 0.0f));
		mTorso = glm::rotate(mTorso, glm::radians(torsoYaw), glm::vec3(0.0f, 1.0f, 0.0f));
		mTorso = glm::scale(mTorso, glm::vec3(1.0f, torsoScaleY, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mTorso));
		torsoMesh->Draw(shader);

		// ── 3. Cuello y Cabeza (Hijo de Torso)
		glm::mat4 mNeck = glm::translate(mTorso, glm::vec3(0.0f, 0.54f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mNeck));
		neckMesh->Draw(shader);

		glm::mat4 mHead = glm::translate(mNeck, glm::vec3(0.0f, 0.12f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mHead));
		headMesh->Draw(shader);
		hairMesh->Draw(shader);

		// ── 4. Brazo Izquierdo (Hijo de Torso)
		glm::mat4 mShoulderL = glm::translate(mTorso, glm::vec3(0.20f, 0.50f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mShoulderL));
		shoulderMeshL->Draw(shader);

		glm::mat4 mUpperArmL = glm::rotate(mShoulderL, glm::radians(armPitchL), glm::vec3(1.0f, 0.0f, 0.0f));
		mUpperArmL = glm::rotate(mUpperArmL, glm::radians(-8.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mUpperArmL));
		upperArmMeshL->Draw(shader);

		glm::mat4 mElbowL = glm::translate(mUpperArmL, glm::vec3(0.0f, -0.30f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mElbowL));
		elbowMeshL->Draw(shader);

		glm::mat4 mForearmL = glm::rotate(mElbowL, glm::radians(elbowPitchL), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mForearmL));
		forearmMeshL->Draw(shader);

		glm::mat4 mHandL = glm::translate(mForearmL, glm::vec3(0.0f, -0.26f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mHandL));
		handMeshL->Draw(shader);

		// ── 5. Brazo Derecho (Hijo de Torso)
		glm::mat4 mShoulderR = glm::translate(mTorso, glm::vec3(-0.20f, 0.50f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mShoulderR));
		shoulderMeshR->Draw(shader);

		glm::mat4 mUpperArmR = glm::rotate(mShoulderR, glm::radians(armPitchR), glm::vec3(1.0f, 0.0f, 0.0f));
		mUpperArmR = glm::rotate(mUpperArmR, glm::radians(8.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mUpperArmR));
		upperArmMeshR->Draw(shader);

		glm::mat4 mElbowR = glm::translate(mUpperArmR, glm::vec3(0.0f, -0.30f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mElbowR));
		elbowMeshR->Draw(shader);

		glm::mat4 mForearmR = glm::rotate(mElbowR, glm::radians(elbowPitchR), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mForearmR));
		forearmMeshR->Draw(shader);

		glm::mat4 mHandR = glm::translate(mForearmR, glm::vec3(0.0f, -0.26f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mHandR));
		handMeshR->Draw(shader);

		// ── 6. Pierna Izquierda (Hijo de Pelvis)
		glm::mat4 mHipL = glm::translate(mPelvis, glm::vec3(0.10f, -0.04f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mHipL));
		hipJointMeshL->Draw(shader);

		glm::mat4 mThighL = glm::rotate(mHipL, glm::radians(hipPitchL), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mThighL));
		thighMeshL->Draw(shader);

		glm::mat4 mKneeL = glm::translate(mThighL, glm::vec3(0.0f, -0.40f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mKneeL));
		kneeJointMeshL->Draw(shader);

		glm::mat4 mCalfL = glm::rotate(mKneeL, glm::radians(kneePitchL), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mCalfL));
		calfMeshL->Draw(shader);

		glm::mat4 mFootL = glm::translate(mCalfL, glm::vec3(0.0f, -0.40f, 0.0f));
		mFootL = glm::rotate(mFootL, glm::radians(anklePitchL), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mFootL));
		footMeshL->Draw(shader);

		// ── 7. Pierna Derecha (Hijo de Pelvis)
		glm::mat4 mHipR = glm::translate(mPelvis, glm::vec3(-0.10f, -0.04f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mHipR));
		hipJointMeshR->Draw(shader);

		glm::mat4 mThighR = glm::rotate(mHipR, glm::radians(hipPitchR), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mThighR));
		thighMeshR->Draw(shader);

		glm::mat4 mKneeR = glm::translate(mThighR, glm::vec3(0.0f, -0.40f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mKneeR));
		kneeJointMeshR->Draw(shader);

		glm::mat4 mCalfR = glm::rotate(mKneeR, glm::radians(kneePitchR), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mCalfR));
		calfMeshR->Draw(shader);

		glm::mat4 mFootR = glm::translate(mCalfR, glm::vec3(0.0f, -0.40f, 0.0f));
		mFootR = glm::rotate(mFootR, glm::radians(anklePitchR), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mFootR));
		footMeshR->Draw(shader);
	}

private:
	struct RingItem { float y, rx, rz, v; };

	// ────────────────────────────────────────────────────────────────────────
	// Inicialización y Construcción de Mallas Armonizadas (Curvas Suaves)
	// ────────────────────────────────────────────────────────────────────────
	void InitMeshes()
	{
		GLuint texId = TextureFromFile("Textures/textures_hombre/hombre_diffuse.png", "Models");
		Texture tex;
		tex.id = texId;
		tex.type = "texture_diffuse";
		tex.path.Set("Textures/textures_hombre/hombre_diffuse.png");
		vector<Texture> textures = { tex };

		// 1. Torso: Curvatura pectoral, cintura y dobladillo con greca geométrica
		vector<RingItem> torsoProfile = {
			{ 0.00f, 0.145f, 0.095f, 0.88f }, // Dobladillo con greca
			{ 0.05f, 0.140f, 0.092f, 0.82f }, // Cintura baja
			{ 0.16f, 0.135f, 0.088f, 0.72f }, // Cintura
			{ 0.28f, 0.150f, 0.098f, 0.62f }, // Abdomen superior
			{ 0.40f, 0.175f, 0.110f, 0.54f }, // Pectorales
			{ 0.50f, 0.185f, 0.105f, 0.48f }, // Hombros
			{ 0.54f, 0.110f, 0.075f, 0.46f }  // Cuello base
		};
		torsoMesh = BuildContouredMesh(torsoProfile, 28, 0.05f, 0.45f, textures);

		// 2. Pelvis: Unión anatómica curvada para los pantalones negros
		vector<RingItem> pelvisProfile = {
			{ -0.10f, 0.130f, 0.080f, 0.18f },
			{ -0.05f, 0.140f, 0.088f, 0.12f },
			{  0.02f, 0.145f, 0.094f, 0.06f }
		};
		pelvisMesh = BuildContouredMesh(pelvisProfile, 28, 0.76f, 0.98f, textures);

		// 3. Cabeza: Esferoide suave deformado con rostro proporcionado
		headMesh = BuildHeadMesh(textures);
		hairMesh = BuildHairMesh(textures);

		// 4. Cuello: Cilindro suave
		vector<RingItem> neckProfile = {
			{ 0.00f, 0.050f, 0.048f, 0.42f },
			{ 0.06f, 0.046f, 0.045f, 0.38f },
			{ 0.12f, 0.048f, 0.047f, 0.35f }
		};
		neckMesh = BuildContouredMesh(neckProfile, 20, 0.10f, 0.28f, textures);

		// 5. Articulaciones esféricas suaves (evitan huecos al rotar)
		shoulderMeshL = BuildEllipsoidMesh(0.052f, 0.052f, 0.052f, 16, 20, 0.08f, 0.50f, 0.35f, 0.65f, textures);
		shoulderMeshR = BuildEllipsoidMesh(0.052f, 0.052f, 0.052f, 16, 20, 0.08f, 0.50f, 0.35f, 0.65f, textures);
		elbowMeshL    = BuildEllipsoidMesh(0.038f, 0.038f, 0.038f, 14, 18, 0.55f, 0.55f, 0.70f, 0.65f, textures);
		elbowMeshR    = BuildEllipsoidMesh(0.038f, 0.038f, 0.038f, 14, 18, 0.55f, 0.55f, 0.70f, 0.65f, textures);
		hipJointMeshL = BuildEllipsoidMesh(0.062f, 0.062f, 0.062f, 16, 20, 0.78f, 0.10f, 0.95f, 0.25f, textures);
		hipJointMeshR = BuildEllipsoidMesh(0.062f, 0.062f, 0.062f, 16, 20, 0.78f, 0.10f, 0.95f, 0.25f, textures);
		kneeJointMeshL= BuildEllipsoidMesh(0.046f, 0.046f, 0.046f, 16, 20, 0.78f, 0.25f, 0.95f, 0.35f, textures);
		kneeJointMeshR= BuildEllipsoidMesh(0.046f, 0.046f, 0.046f, 16, 20, 0.78f, 0.25f, 0.95f, 0.35f, textures);

		// 6. Brazos superiores: Manga blanca con greca y brazo visible
		vector<RingItem> armProfile = {
			{  0.00f, 0.050f, 0.048f, 0.52f }, // Hombro
			{ -0.10f, 0.048f, 0.046f, 0.60f }, // Biceps manga
			{ -0.15f, 0.046f, 0.045f, 0.88f }, // Manga con greca geométrica
			{ -0.22f, 0.041f, 0.040f, 0.45f }, // Piel
			{ -0.30f, 0.037f, 0.036f, 0.52f }  // Codo
		};
		upperArmMeshL = BuildContouredMesh(armProfile, 20, 0.05f, 0.40f, textures);
		upperArmMeshR = BuildContouredMesh(armProfile, 20, 0.05f, 0.40f, textures);

		// 7. Antebrazos: Perfil muscular que estrecha suavemente hacia la muñeca
		vector<RingItem> forearmProfile = {
			{  0.00f, 0.038f, 0.036f, 0.54f },
			{ -0.10f, 0.040f, 0.038f, 0.62f },
			{ -0.20f, 0.033f, 0.030f, 0.70f },
			{ -0.26f, 0.028f, 0.025f, 0.75f }
		};
		forearmMeshL = BuildContouredMesh(forearmProfile, 18, 0.52f, 0.72f, textures);
		forearmMeshR = BuildContouredMesh(forearmProfile, 18, 0.52f, 0.72f, textures);

		// 8. Manos esculpidas con dedos y palma redondeada
		handMeshL = BuildSculptedHand(true, textures);
		handMeshR = BuildSculptedHand(false, textures);

		// 9. Muslos: Musculatura anatómica en pantalón negro
		vector<RingItem> thighProfile = {
			{  0.00f, 0.068f, 0.070f, 0.08f },
			{ -0.15f, 0.063f, 0.065f, 0.18f },
			{ -0.30f, 0.055f, 0.057f, 0.28f },
			{ -0.40f, 0.048f, 0.049f, 0.35f }
		};
		thighMeshL = BuildContouredMesh(thighProfile, 22, 0.76f, 0.98f, textures);
		thighMeshR = BuildContouredMesh(thighProfile, 22, 0.76f, 0.98f, textures);

		// 10. Pantorrillas: Curva de los gemelos que estrecha hacia los tobillos
		vector<RingItem> calfProfile = {
			{  0.00f, 0.047f, 0.048f, 0.38f },
			{ -0.12f, 0.052f, 0.054f, 0.46f },
			{ -0.26f, 0.043f, 0.044f, 0.54f },
			{ -0.38f, 0.036f, 0.036f, 0.62f },
			{ -0.40f, 0.035f, 0.035f, 0.64f }
		};
		calfMeshL = BuildContouredMesh(calfProfile, 22, 0.76f, 0.98f, textures);
		calfMeshR = BuildContouredMesh(calfProfile, 22, 0.76f, 0.98f, textures);

		// 11. Zapatos: Tenis deportivos con suela y puntera curva
		footMeshL = BuildCurvedShoe(textures);
		footMeshR = BuildCurvedShoe(textures);
	}

	// ────────────────────────────────────────────────────────────────────────
	// Generadores de Mallas Suaves y Orgánicas (Geometría Libre de Cuadrados)
	// ────────────────────────────────────────────────────────────────────────
	Mesh* BuildContouredMesh(const vector<RingItem>& profile, int sectors,
		float uMin, float uMax, const vector<Texture>& textures)
	{
		vector<Vertex> verts;
		vector<GLuint> inds;

		for (size_t r = 0; r < profile.size(); ++r)
		{
			const auto& ring = profile[r];
			for (int s = 0; s <= sectors; ++s)
			{
				float theta = static_cast<float>(s) / static_cast<float>(sectors) * 2.0f * 3.14159265f;
				float cosT = std::cos(theta);
				float sinT = std::sin(theta);

				Vertex v;
				v.Position = glm::vec3(ring.rx * cosT, ring.y, ring.rz * sinT);

				// Normal perpendicular suave
				v.Normal = glm::normalize(glm::vec3(cosT / ring.rx, 0.0f, sinT / ring.rz));
				v.TexCoords = glm::vec2(uMin + (static_cast<float>(s) / sectors) * (uMax - uMin), ring.v);
				verts.push_back(v);
			}
		}

		const int stride = sectors + 1;
		for (size_t r = 0; r + 1 < profile.size(); ++r)
		{
			for (int s = 0; s < sectors; ++s)
			{
				GLuint i0 = static_cast<GLuint>(r * stride + s);
				GLuint i1 = static_cast<GLuint>((r + 1) * stride + s);
				GLuint i2 = static_cast<GLuint>(i1 + 1);
				GLuint i3 = static_cast<GLuint>(i0 + 1);

				inds.push_back(i0); inds.push_back(i1); inds.push_back(i2);
				inds.push_back(i0); inds.push_back(i2); inds.push_back(i3);
			}
		}

		return new Mesh(verts, inds, textures);
	}

	Mesh* BuildEllipsoidMesh(float rx, float ry, float rz, int rings, int sectors,
		float u0, float v0, float u1, float v1, const vector<Texture>& textures)
	{
		vector<Vertex> verts;
		vector<GLuint> inds;

		for (int r = 0; r <= rings; ++r)
		{
			float phi = static_cast<float>(r) / static_cast<float>(rings) * 3.14159265f;
			float sinP = std::sin(phi);
			float cosP = std::cos(phi);

			for (int s = 0; s <= sectors; ++s)
			{
				float theta = static_cast<float>(s) / static_cast<float>(sectors) * 2.0f * 3.14159265f;
				float sinT = std::sin(theta);
				float cosT = std::cos(theta);

				Vertex v;
				v.Position = glm::vec3(rx * sinP * cosT, ry * cosP, rz * sinP * sinT);
				v.Normal = glm::normalize(glm::vec3((sinP * cosT) / rx, cosP / ry, (sinP * sinT) / rz));
				v.TexCoords = glm::vec2(u0 + (static_cast<float>(s) / sectors) * (u1 - u0),
					v0 + (static_cast<float>(r) / rings) * (v1 - v0));
				verts.push_back(v);
			}
		}

		const int stride = sectors + 1;
		for (int r = 0; r < rings; ++r)
		{
			for (int s = 0; s < sectors; ++s)
			{
				GLuint i0 = r * stride + s;
				GLuint i1 = (r + 1) * stride + s;
				GLuint i2 = i1 + 1;
				GLuint i3 = i0 + 1;
				inds.push_back(i0); inds.push_back(i1); inds.push_back(i2);
				inds.push_back(i0); inds.push_back(i2); inds.push_back(i3);
			}
		}

		return new Mesh(verts, inds, textures);
	}

	Mesh* BuildHeadMesh(const vector<Texture>& textures)
	{
		const int rings = 22;
		const int sectors = 28;
		const float rx = 0.082f;
		const float ry = 0.108f;
		const float rz = 0.092f;

		vector<Vertex> verts;
		vector<GLuint> inds;

		for (int r = 0; r <= rings; ++r)
		{
			float phi = static_cast<float>(r) / static_cast<float>(rings) * 3.14159265f;
			float sinP = std::sin(phi);
			float cosP = std::cos(phi);

			for (int s = 0; s <= sectors; ++s)
			{
				float theta = static_cast<float>(s) / static_cast<float>(sectors) * 2.0f * 3.14159265f;
				float sinT = std::sin(theta);
				float cosT = std::cos(theta);

				float px = rx * sinP * cosT;
				float py = ry * cosP;
				float pz = rz * sinP * sinT;

				// Nariz suave en la parte frontal (+Z)
				if (py > -0.02f && py < 0.035f && pz > 0.04f && std::abs(px) < 0.035f)
				{
					float nFactor = std::sin((py + 0.02f) / 0.055f * 3.14159f) * (1.0f - std::abs(px) / 0.035f);
					pz += 0.022f * nFactor;
				}
				// Mentón redondeado
				if (py < -0.05f && pz > 0.015f && std::abs(px) < 0.04f)
				{
					pz += 0.014f * (1.0f - std::abs(px) / 0.04f);
				}

				Vertex v;
				v.Position = glm::vec3(px, py, pz);
				v.Normal = glm::normalize(glm::vec3(px / (rx * rx), py / (ry * ry), pz / (rz * rz)));

				// Mapeo a región facial (0.0 a 0.35, v: 0.05 a 0.42)
				float uRatio = (static_cast<float>(s) / sectors);
				v.TexCoords = glm::vec2(0.04f + uRatio * 0.28f, 0.08f + (static_cast<float>(r) / rings) * 0.30f);
				verts.push_back(v);
			}
		}

		const int stride = sectors + 1;
		for (int r = 0; r < rings; ++r)
		{
			for (int s = 0; s < sectors; ++s)
			{
				GLuint i0 = r * stride + s;
				GLuint i1 = (r + 1) * stride + s;
				GLuint i2 = i1 + 1;
				GLuint i3 = i0 + 1;
				inds.push_back(i0); inds.push_back(i1); inds.push_back(i2);
				inds.push_back(i0); inds.push_back(i2); inds.push_back(i3);
			}
		}

		return new Mesh(verts, inds, textures);
	}

	Mesh* BuildHairMesh(const vector<Texture>& textures)
	{
		// Casquete de cabello con volumen orgánico sobre la cabeza
		const int rings = 14;
		const int sectors = 26;
		const float rx = 0.086f;
		const float ry = 0.112f;
		const float rz = 0.096f;

		vector<Vertex> verts;
		vector<GLuint> inds;

		for (int r = 0; r <= rings; ++r)
		{
			// Cubre la parte superior y trasera (phi de 0 a ~0.60*pi)
			float phi = static_cast<float>(r) / static_cast<float>(rings) * (3.14159265f * 0.58f);
			float sinP = std::sin(phi);
			float cosP = std::cos(phi);

			for (int s = 0; s <= sectors; ++s)
			{
				float theta = static_cast<float>(s) / static_cast<float>(sectors) * 2.0f * 3.14159265f;
				float sinT = std::sin(theta);
				float cosT = std::cos(theta);

				float px = rx * sinP * cosT;
				float py = ry * cosP + 0.005f; // Ligero volumen extra
				float pz = rz * sinP * sinT;

				Vertex v;
				v.Position = glm::vec3(px, py, pz);
				v.Normal = glm::normalize(glm::vec3(px, py, pz));
				v.TexCoords = glm::vec2(0.38f + (static_cast<float>(s) / sectors) * 0.24f,
					0.05f + (static_cast<float>(r) / rings) * 0.25f);
				verts.push_back(v);
			}
		}

		const int stride = sectors + 1;
		for (int r = 0; r < rings; ++r)
		{
			for (int s = 0; s < sectors; ++s)
			{
				GLuint i0 = r * stride + s;
				GLuint i1 = (r + 1) * stride + s;
				GLuint i2 = i1 + 1;
				GLuint i3 = i0 + 1;
				inds.push_back(i0); inds.push_back(i1); inds.push_back(i2);
				inds.push_back(i0); inds.push_back(i2); inds.push_back(i3);
			}
		}

		return new Mesh(verts, inds, textures);
	}

	Mesh* BuildSculptedHand(bool isLeft, const vector<Texture>& textures)
	{
		// Palma y dedos esculpidos con curvatura suave (evita cajas planas)
		const float sign = isLeft ? 1.0f : -1.0f;
		vector<Vertex> verts;
		vector<GLuint> inds;

		// Palma elipsoidal
		const int rings = 12;
		const int sectors = 16;
		for (int r = 0; r <= rings; ++r)
		{
			float phi = static_cast<float>(r) / static_cast<float>(rings) * 3.14159f;
			float sinP = std::sin(phi);
			float cosP = std::cos(phi);

			for (int s = 0; s <= sectors; ++s)
			{
				float theta = static_cast<float>(s) / static_cast<float>(sectors) * 2.0f * 3.14159f;
				float cosT = std::cos(theta);
				float sinT = std::sin(theta);

				float px = 0.024f * sinP * cosT;
				float py = -0.045f - 0.040f * cosP;
				float pz = 0.016f * sinP * sinT;

				// Inclinación del pulgar
				if (cosT * sign > 0.4f && py > -0.065f)
					px += sign * 0.010f;

				Vertex v;
				v.Position = glm::vec3(px, py, pz);
				v.Normal = glm::normalize(glm::vec3(px, 0.0f, pz));
				v.TexCoords = glm::vec2(0.55f + (static_cast<float>(s) / sectors) * 0.18f, 0.74f + (static_cast<float>(r) / rings) * 0.10f);
				verts.push_back(v);
			}
		}

		const int stride = sectors + 1;
		for (int r = 0; r < rings; ++r)
		{
			for (int s = 0; s < sectors; ++s)
			{
				GLuint i0 = r * stride + s;
				GLuint i1 = (r + 1) * stride + s;
				GLuint i2 = i1 + 1;
				GLuint i3 = i0 + 1;
				inds.push_back(i0); inds.push_back(i1); inds.push_back(i2);
				inds.push_back(i0); inds.push_back(i2); inds.push_back(i3);
			}
		}

		return new Mesh(verts, inds, textures);
	}

	Mesh* BuildCurvedShoe(const vector<Texture>& textures)
	{
		// Tenis deportivo con suela de goma curva, empeine arqueado y puntera redondeada
		vector<Vertex> verts;
		vector<GLuint> inds;

		const int lengthRings = 14;
		const int crossSectors = 16;

		for (int l = 0; l <= lengthRings; ++l)
		{
			float t = static_cast<float>(l) / static_cast<float>(lengthRings); // 0 (talon) a 1 (punta)
			float z = -0.07f + t * 0.20f; // Longitud del pie hacia adelante (+Z)

			// Ancho y alto del calzado en cada punto longitudinal
			float width = (t < 0.2f) ? (0.042f + t * 0.025f) : (0.048f * std::sin(t * 3.14159f * 0.85f + 0.35f));
			float height = (t < 0.35f) ? 0.062f : (0.062f - (t - 0.35f) * 0.042f);

			for (int s = 0; s <= crossSectors; ++s)
			{
				float theta = static_cast<float>(s) / static_cast<float>(crossSectors) * 3.14159265f; // Semicilindro superior
				float cosT = std::cos(theta);
				float sinT = std::sin(theta);

				float px = width * cosT;
				float py = (s == 0 || s == crossSectors) ? 0.0f : (height * sinT);

				Vertex v;
				v.Position = glm::vec3(px, py, z);
				v.Normal = glm::normalize(glm::vec3(cosT, sinT, 0.2f * (0.5f - t)));
				v.TexCoords = glm::vec2(0.76f + (px + 0.05f) * 2.2f, 0.66f + t * 0.17f);
				verts.push_back(v);
			}
		}

		const int stride = crossSectors + 1;
		for (int l = 0; l < lengthRings; ++l)
		{
			for (int s = 0; s < crossSectors; ++s)
			{
				GLuint i0 = l * stride + s;
				GLuint i1 = (l + 1) * stride + s;
				GLuint i2 = i1 + 1;
				GLuint i3 = i0 + 1;
				inds.push_back(i0); inds.push_back(i1); inds.push_back(i2);
				inds.push_back(i0); inds.push_back(i2); inds.push_back(i3);
			}
		}

		return new Mesh(verts, inds, textures);
	}

	bool RaycastGround(const glm::vec3& origin, const glm::vec3& direction, GLfloat& hitHeight) const
	{
		if (direction.y >= 0.0f || origin.x < terrainMinX || origin.x > terrainMaxX ||
			origin.z < terrainMinZ || origin.z > terrainMaxZ)
			return false;

		const GLfloat distance = (groundHeight - origin.y) / direction.y;
		if (distance < 0.0f)
			return false;

		const glm::vec3 hitPoint = origin + direction * distance;
		if (hitPoint.x < terrainMinX || hitPoint.x > terrainMaxX ||
			hitPoint.z < terrainMinZ || hitPoint.z > terrainMaxZ)
			return false;

		hitHeight = hitPoint.y;
		return true;
	}

	// ── Variables de movimiento y física
	glm::vec3 position;
	glm::vec3 velocity;
	GLfloat rotationY;
	GLfloat modelScale;
	GLfloat movementSpeed;
	GLfloat acceleration;
	GLfloat rotationSpeed;
	GLfloat gravity;
	GLfloat groundHeight;
	GLfloat collisionRadius;

	// ── Articulaciones cinemáticas del esqueleto
	float walkCycle;
	float idleCycle;
	float hipPitchL, hipPitchR;
	float kneePitchL, kneePitchR;
	float anklePitchL, anklePitchR;
	float armPitchL, armPitchR;
	float elbowPitchL, elbowPitchR;
	float bodyBob, bodyYaw, torsoYaw, torsoPitch;
	float torsoScaleY;

	// ── Mallas del cuerpo
	Mesh* torsoMesh = nullptr;
	Mesh* pelvisMesh = nullptr;
	Mesh* headMesh = nullptr;
	Mesh* hairMesh = nullptr;
	Mesh* neckMesh = nullptr;

	Mesh* shoulderMeshL = nullptr;
	Mesh* shoulderMeshR = nullptr;
	Mesh* upperArmMeshL = nullptr;
	Mesh* upperArmMeshR = nullptr;
	Mesh* elbowMeshL = nullptr;
	Mesh* elbowMeshR = nullptr;
	Mesh* forearmMeshL = nullptr;
	Mesh* forearmMeshR = nullptr;
	Mesh* handMeshL = nullptr;
	Mesh* handMeshR = nullptr;

	Mesh* hipJointMeshL = nullptr;
	Mesh* hipJointMeshR = nullptr;
	Mesh* thighMeshL = nullptr;
	Mesh* thighMeshR = nullptr;
	Mesh* kneeJointMeshL = nullptr;
	Mesh* kneeJointMeshR = nullptr;
	Mesh* calfMeshL = nullptr;
	Mesh* calfMeshR = nullptr;
	Mesh* footMeshL = nullptr;
	Mesh* footMeshR = nullptr;

	static constexpr GLfloat terrainMinX = -3.25f;
	static constexpr GLfloat terrainMaxX = 3.25f;
	static constexpr GLfloat terrainMinZ = -3.25f;
	static constexpr GLfloat terrainMaxZ = 3.25f;
};