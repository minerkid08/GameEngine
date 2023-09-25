#include "SceneHierarchy.h"

namespace Engine{
	void SceneHierarchy::setContext(const shdPtr<Scene>& _scene){
		scene = _scene;
		selected = {};
	}
	void SceneHierarchy::uiRender(){
		ImGui::Begin("Scene Hierarchy");
		if(ImGui::Button("add entity")){
			selected = scene->createEnt();
		}
		scene->getReg().each([this](entt::entity ent){
			drawEntity({scene.get(), ent});
		});
		if(ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()){
			selected = {};
		}
		ImGui::End();
		ImGui::Begin("Properties");
		if(selected){
			ImGuiTreeNodeFlags flags = 
			ImGuiTreeNodeFlags_OpenOnArrow | 
			ImGuiTreeNodeFlags_OpenOnDoubleClick | 
			ImGuiTreeNodeFlags_DefaultOpen | 
			ImGuiTreeNodeFlags_Framed | 
			ImGuiTreeNodeFlags_SpanAvailWidth |
			ImGuiTreeNodeFlags_AllowItemOverlap |
			ImGuiTreeNodeFlags_FramePadding;
			if(selected.hasComp<Components::Tag>()){
				std::string& tag = selected.getComp<Components::Tag>().tag;
				char buf[256];
				memset(buf, 0, sizeof(buf));
				strcpy(buf, tag.c_str());
				if(ImGui::InputText(" ", buf, sizeof(buf))){
					tag = std::string(buf);
				}
			}
			ImVec2 contentArea = ImGui::GetContentRegionAvail();
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4,4));
			float lineHeight = ImGui::GetFont()->FontSize * 2.0f + ImGui::GetStyle().FramePadding.y * 2.0f;
			ImGui::PopStyleVar();

			ImGui::SameLine(contentArea.x - lineHeight * 0.5f);
			if(ImGui::Button("+", ImVec2(lineHeight, lineHeight))){
				ImGui::OpenPopup("AddComp");
			}
			if(ImGui::BeginPopup("AddComp")){
				if(!selected.hasComp<Components::Camera>()){
					if(ImGui::MenuItem("Camera")){
						selected.addComp<Components::Camera>();
						ImGui::CloseCurrentPopup();
					}
				}
				if(!selected.hasComp<Components::SpriteRenderer>()){
					if(ImGui::MenuItem("SpriteRenderer")){
						selected.addComp<Components::SpriteRenderer>();
						ImGui::CloseCurrentPopup();
					}
				}
				if(!selected.hasComp<Components::NativeScript>()){
					if(ImGui::MenuItem("Script")){
						selected.addComp<Components::NativeScript>();
						ImGui::CloseCurrentPopup();
					}
				}
				ImGui::EndPopup();
			}
			drawComp<Components::Transform>("Transform", flags, [this](Components::Transform& transform){
				ImGui::DragFloat3("pos", glm::value_ptr(transform.pos), 0.1f);
				float rotation = glm::degrees(transform.rot);
				ImGui::DragFloat("rot", &rotation, 5.0f);
				transform.rot = glm::radians(rotation);
				ImGui::DragFloat2("scale", glm::value_ptr(transform.scale), 0.1f);
			}, false);
			drawComp<Components::Camera>("Camera", flags, [this](Components::Camera& camera){
				bool changed = false;
				ImGui::Checkbox("mainCamera", &camera.mainCamera);
				changed |= ImGui::Checkbox("fixedAspect", &camera.fixedAspect);
				changed |= ImGui::DragFloat("near", &camera.camera.getNear(), 0.1);
				changed |= ImGui::DragFloat("far", &camera.camera.getFar(), 0.1);
				changed |= ImGui::DragFloat("zoom", &camera.camera.getZoom(), 0.1, 0);
				if(camera.fixedAspect){
					changed |= ImGui::DragFloat("aspect", &camera.camera.getAspect(), 0.1, 0);
				}
				if(changed){
					camera.camera.orthographic();
				}
			});
			drawComp<Components::SpriteRenderer>("Sprite Renderer", flags, [this](Components::SpriteRenderer& renderer){
				static int mode = 0;
				ImGui::Combo("mode", &mode, "color\0texture\0\0");
				if(mode == 0){
					renderer.mode = Components::SpriteRenderer::Type::Color;
					ImGui::ColorEdit4("color", glm::value_ptr(renderer.color));
				}else{
					renderer.mode = Components::SpriteRenderer::Type::Tex;
					char buf[256];
					memset(buf, 0, sizeof(buf));
					strcpy(buf, renderer.path.c_str());
					if(ImGui::InputText("tex path", buf, sizeof(buf))){
						renderer.path = std::string(buf);
					}
					if(ImGui::Button("find texture")){
						renderer.texture();
					}
					ImGui::ColorEdit4("tint", glm::value_ptr(renderer.color));
					ImGui::DragFloat("tile", &renderer.tile, 0.1, 0);
				}
			});
			drawComp<Components::NativeScript>("Script", flags, [this](Components::NativeScript& script){
				ImGui::Checkbox("enabled", &script.enabled);
			});
		}
		ImGui::End();
	}
	void SceneHierarchy::drawEntity(const Entity& ent){
		Components::Tag& tag = ent.getComp<Components::Tag>();
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | (ent == selected ? ImGuiTreeNodeFlags_Selected : 0);
		bool opened = ImGui::TreeNodeEx((void*)(int)ent, flags, tag.tag.c_str());
		if(ImGui::IsItemClicked()){
			selected = ent;
		}
		bool dlt = false;
		if(ImGui::BeginPopupContextItem()){
			if(ImGui::MenuItem("Delete")){
				dlt = true;
			}
			ImGui::EndPopup();
		}
		if(opened){
			ImGui::TreePop();
		}
		if(dlt){
			if(selected.operator==(ent)){
				selected = {};
			}
			scene->removeEnt(ent);
		}
	}
	template<typename T> void SceneHierarchy::drawComp(const char* name, ImGuiTreeNodeFlags flags, std::function<void(T&)> func, bool canDelete){
		if(selected.hasComp<T>()){
			ImVec2 contentArea = ImGui::GetContentRegionAvail();
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4,4));
			float lineHeight = ImGui::GetFont()->FontSize * 2.0f + ImGui::GetStyle().FramePadding.y * 2.0f;
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), flags, name);
			ImGui::PopStyleVar();

			ImGui::SameLine(contentArea.x - lineHeight * 0.5f);
			if(ImGui::Button(":", ImVec2(lineHeight, lineHeight))){
				ImGui::OpenPopup("CompSettings");
			}
			
			if(ImGui::BeginPopup("CompSettings")){
				if(ImGui::MenuItem("Reset")){
					selected.getComp<T>().reset();
				}
				if(canDelete){
					if(ImGui::MenuItem("Remove")){
						selected.removeComp<T>();
						ImGui::EndPopup();
						ImGui::TreePop();
						return;
					}
				}
				ImGui::EndPopup();
			}
			
			if(open){
				func(selected.getComp<T>());
				ImGui::TreePop();
			}
		}
	}
}