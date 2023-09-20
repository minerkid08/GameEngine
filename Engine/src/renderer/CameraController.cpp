#include "CameraController.h"
#include "Core/Input.h"
#include "Core/KeyCodes.h"
namespace Engine{
	CameraController::CameraController(float _aspect){
		aspect = _aspect;
		cam.orthographic(-aspect * zoom, aspect * zoom, zoom, -zoom);
	}
	void CameraController::update(float deltaTime){
		if(Input::keyDown(EngineKeycode_W)){pos.y += moveSpeed * deltaTime;}
		if(Input::keyDown(EngineKeycode_A)){pos.x -= moveSpeed * deltaTime;}
		if(Input::keyDown(EngineKeycode_S)){pos.y -= moveSpeed * deltaTime;}
		if(Input::keyDown(EngineKeycode_D)){pos.x += moveSpeed * deltaTime;}
		cam.setPos(glm::vec3(pos, 0.0f));
	}
	void CameraController::event(Event* e){
		EventDispatcher d(e);
		d.dispatch<MouseScrollEvent>(BindFn(CameraController::mouseScroll));
		d.dispatch<WindowResizeEvent>(BindFn(CameraController::windowResize));
	}
	bool CameraController::mouseScroll(MouseScrollEvent* e){
		zoom -= e->y * 0.25f;
		zoom = std::max(zoom, 0.25f);
		moveSpeed = zoom;
		cam.orthographic(-aspect * zoom, aspect * zoom, zoom, -zoom);
		return false;
	}
	bool CameraController::windowResize(WindowResizeEvent* e){
		aspect = (float)e->width/(float)e->height;
		cam.orthographic(-aspect * zoom, aspect * zoom, zoom, -zoom);
		return false;
	}
	void CameraController::setAspect(float a){
		aspect = a;
		cam.orthographic(-aspect * zoom, aspect * zoom, zoom, -zoom);
	}
}