#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPIRMENTAL
#include <glm/gtx/quaternion.hpp>
namespace Engine{
	class Camera{
		public:
		enum CameraMode{
			Orthographic, Perspective
		};
		Camera(){}
		void perspective(float aspectRatio, float fov = 90.0f, float near_ = -1.0f, float far_ = 1.0f){
			projMat = glm::perspective(glm::radians(fov), aspectRatio, near_, far_);
			mode = CameraMode::Perspective;
			viewMat = glm::mat4x4(1);
			updateMat();
		}
		void orthographic(int width, int height, float _zoom = 1, float near_ = -1.0f, float far_ = 1.0f){
			nearPlane = near_;
			farPlane = far_;
			zoom = _zoom;
			aspect = (float)width / (float)height;
			projMat = glm::ortho(-aspect * zoom, aspect * zoom, zoom, -zoom);
			updateMat();
		}
		void orthographic(float _aspect, float _zoom = 1.0f, float near_ = -1.0f, float far_ = 1.0f){
			nearPlane = near_;
			farPlane = far_;
			zoom = _zoom;
			aspect = _aspect;
			projMat = glm::ortho(-aspect * zoom, aspect * zoom, zoom, -zoom);
			updateMat();
		}
		void orthographic(){
			projMat = glm::ortho(-aspect * zoom, aspect * zoom, zoom, -zoom);
			updateMat();
		}
		glm::vec3 getPos(){return pos;}
		glm::vec3 getRot(){return rot;}
		glm::mat4x4 getProjMat(){return projMat;}
		glm::mat4x4 getViewMat(){return viewMat;}
		const glm::mat4x4 getViewProjMat() const {return viewProjMat;}
		void setPos(const glm::vec3& newPos){pos = newPos; updateMat();}
		void setRot(const glm::vec3& newRot){rot = newRot; updateMat();}
		float& getNear(){return nearPlane;}
		float& getFar(){return farPlane;}
		float& getZoom(){return zoom;}
		float& getAspect(){return aspect;}

		private:
		glm::mat4x4 projMat;
		glm::mat4x4 viewMat = glm::mat4x4(1.0f);
		glm::mat4x4 viewProjMat;
		glm::vec3 pos = {0.0f, 0.0f, 0.0f};
		glm::vec3 rot = {0.0f, 0.0f, 0.0f};
		CameraMode mode;
		float nearPlane = -1.0f;
		float farPlane = 1.0f;
		float aspect = 0;
		float zoom = 1.0f;
		void updateMat(){
			glm::mat4x4 transform = glm::translate(glm::mat4x4(1.0f), pos) * glm::toMat4(glm::quat(glm::vec3(glm::radians(rot.x), glm::radians(rot.y), glm::radians(rot.z))));
			viewMat = glm::inverse(transform);
			viewProjMat = viewMat * projMat;
		}
	};
}