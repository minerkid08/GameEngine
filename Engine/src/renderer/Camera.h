#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
		void orthographic(float left, float right, float up, float down, float near_ = -1.0f, float far_ = 1.0f){
			projMat = glm::ortho(left,right,down,up,near_,far_);
			mode = CameraMode::Orthographic;
			viewMat = glm::mat4x4(1);
			updateMat();
		}
		glm::vec3 getPos(){return pos;}
		float getRot(){return rot;}
		glm::mat4x4 getProjMat(){return projMat;}
		glm::mat4x4 getViewMat(){return viewMat;}
		glm::mat4x4 getViewProjMat(){return viewProjMat;}
		void setPos(const glm::vec3& newPos){pos = newPos; updateMat();}
		void setRot(const float newRot){rot = newRot; updateMat();}

		private:
		glm::mat4x4 projMat;
		glm::mat4x4 viewMat = glm::mat4x4(1.0f);
		glm::mat4x4 viewProjMat;
		glm::vec3 pos = {0.0f, 0.0f, 0.0f};\
		CameraMode mode;
		float rot = 0.0f;
		void updateMat(){
			glm::mat4x4 transform = glm::translate(glm::mat4x4(1.0f), pos) * glm::rotate(glm::mat4x4(1.0f), glm::radians(rot), glm::vec3(0,0,1));
			viewMat = glm::inverse(transform);
			viewProjMat = viewMat * projMat;
		}
	};
}