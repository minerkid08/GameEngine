---@meta

function create()
end

---@param deltaTime number
function update(deltaTime)
end

function destroy()
end

---@param label string
function info(label)
end

---@param label string
function warn(label)
end

---@param label string
function error(label)
end

---@class Vec2
---@field x number
---@field y number
Vec2 = {};

---@return Vec2
function Vec2.new()
end

---@return Vec2
---@param a Vec2
---@param b Vec2 | number
function Vec2.add(a, b)
end

---@return Vec2
---@param a Vec2
---@param b Vec2 | number
function Vec2.sub(a, b)
end

---@return Vec2
---@param a Vec2
---@param b Vec2 | number
function Vec2.mul(a, b)
end

---@return Vec2
---@param a Vec2
---@param b Vec2 | number
function Vec2.div(a, b)
end

---@return number
---@param a Vec2
function Vec2.len(a)
end

---@return number
---@param a Vec2
---@param b Vec2
function Vec2.dist(a, b)
end

---@return Vec2
---@param a Vec2
function Vec2.neg(a)
end

---@class Vec3
---@field x number
---@field y number
---@field z number

---@class Color
---@field r number
---@field g number
---@field b number
---@field a number

---@class Entity
Entity = {}
entity = Entity
---@param name string
---@return Entity
function Entity:add(name)
end

---@param name string
---@return Entity
function Entity:getWithName(name)
end

---@param comp string
---@return Component
function Entity:addComp(comp)
end

---@param comp string
---@return any
function Entity:getComp(comp)
end

---@param comp string
function Entity:removeComp(comp)
end

---@param comp string
---@return boolean
function Entity:hasComp(comp)
end

---@class Component

---@class Transform: Component
Transform = {}
transform = Transform
---@param pos Vec3
function Transform:setPos(pos)
end

---@return Vec3
function Transform:getPos()
end

---@param rot number
function Transform:setRot(rot)
end

---@return number
function Transform:getRot()
end

---@param scale Vec2
function Transform:setScale(scale)
end

---@return Vec2
function Transform:getScale()
end

---@class SpriteRenderer : Component
SpriteRenderer = {}

---@return Color
function SpriteRenderer:getTint()
end

---@param color Color
function SpriteRenderer:setTint(color)
end

---@return number
function SpriteRenderer:getTile()
end

---@param tile number
function SpriteRenderer:setTile(tile)
end

---@param id integer
---@param val Vec2
function SpriteRenderer:setUV(id, val)
end

---@param id integer
---@return Vec2
function SpriteRenderer:setUV(id)
end

---@class Input
Input = {}

---@param keyCode integer
---@return boolean
function Input.keyDown(keyCode)
end

---@param code integer
---@return boolean
function Input.mouseDown(code)
end

---@return integer
function Input.mouseX()
end

---@return integer
function Input.mouseY()
end

---@class Keycodes
---@field a integer
---@field b integer
---@field c integer
---@field d integer
---@field e integer
---@field f integer
---@field g integer
---@field h integer
---@field i integer
---@field j integer
---@field k integer
---@field l integer
---@field m integer
---@field n integer
---@field o integer
---@field p integer
---@field q integer
---@field r integer
---@field s integer
---@field t integer
---@field u integer
---@field v integer
---@field w integer
---@field x integer
---@field y integer
---@field z integer
Keycodes = {}