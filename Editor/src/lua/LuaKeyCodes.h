#pragma once
#include <lua/lua.hpp>
#include <cctype>
#include <cstring>
namespace Engine{
	class LuaKeycode{
		public:
		static void addkeycode(lua_State* l, const char* name, int code){
			lua_pushnumber(l, code);
			lua_setfield(l, -2, name);
		}
		static void make(lua_State* l){
			lua_newtable(l);
			int tablepos = lua_gettop(l);
			lua_pushvalue(l, tablepos);
			lua_setglobal(l, "keycodes");

			addkeycode(l, "space",              32);
			addkeycode(l, "apostrophe",         39);  /* ' */
			addkeycode(l, "comma",              44);  /* , */
			addkeycode(l, "minus",              45);  /* - */
			addkeycode(l, "period",             46);  /* . */
			addkeycode(l, "slash",              47);  /* / */
			addkeycode(l, "0",                  48);
			addkeycode(l, "1",                  49);
			addkeycode(l, "2",                  50);
			addkeycode(l, "3",                  51);
			addkeycode(l, "4",                  52);
			addkeycode(l, "5",                  53);
			addkeycode(l, "6",                  54);
			addkeycode(l, "7",                  55);
			addkeycode(l, "8",                  56);
			addkeycode(l, "9",                  57);
			addkeycode(l, "semicolon",          59);  /* ; */
			addkeycode(l, "equal",              61);  /* = */
			addkeycode(l, "a",                  65);
			addkeycode(l, "b",                  66);
			addkeycode(l, "c",                  67);
			addkeycode(l, "d",                  68);
			addkeycode(l, "e",                  69);
			addkeycode(l, "f",                  70);
			addkeycode(l, "g",                  71);
			addkeycode(l, "h",                  72);
			addkeycode(l, "i",                  73);
			addkeycode(l, "j",                  74);
			addkeycode(l, "k",                  75);
			addkeycode(l, "l",                  76);
			addkeycode(l, "m",                  77);
			addkeycode(l, "n",                  78);
			addkeycode(l, "o",                  79);
			addkeycode(l, "p",                  80);
			addkeycode(l, "q",                  81);
			addkeycode(l, "r",                  82);
			addkeycode(l, "s",                  83);
			addkeycode(l, "t",                  84);
			addkeycode(l, "u",                  85);
			addkeycode(l, "v",                  86);
			addkeycode(l, "w",                  87);
			addkeycode(l, "x",                  88);
			addkeycode(l, "y",                  89);
			addkeycode(l, "z",                  90);
			addkeycode(l, "left_bracket",       91);  /* [ */
			addkeycode(l, "backslash",          92);  /* \ */
			addkeycode(l, "right_bracket",      93);  /* ] */
			addkeycode(l, "grave_accent",       96);  /* ` */
			addkeycode(l, "world_1",            161); /* non-us #1 */
			addkeycode(l, "world_2",            162); /* non-us #2 */
			addkeycode(l, "escape",             256);
			addkeycode(l, "enter",              257);
			addkeycode(l, "tab",                258);
			addkeycode(l, "backspace",          259);
			addkeycode(l, "insert",             260);
			addkeycode(l, "delete",             261);
			addkeycode(l, "right",              262);
			addkeycode(l, "left",               263);
			addkeycode(l, "down",               264);
			addkeycode(l, "up",                 265);
			addkeycode(l, "page_up",            266);
			addkeycode(l, "page_down",          267);
			addkeycode(l, "home",               268);
			addkeycode(l, "end",                269);
			addkeycode(l, "caps_lock",          280);
			addkeycode(l, "scroll_lock",        281);
			addkeycode(l, "num_lock",           282);
			addkeycode(l, "print_screen",       283);
			addkeycode(l, "pause",              284);
			addkeycode(l, "f1",                 290);
			addkeycode(l, "f2",                 291);
			addkeycode(l, "f3",                 292);
			addkeycode(l, "f4",                 293);
			addkeycode(l, "f5",                 294);
			addkeycode(l, "f6",                 295);
			addkeycode(l, "f7",                 296);
			addkeycode(l, "f8",                 297);
			addkeycode(l, "f9",                 298);
			addkeycode(l, "f10",                299);
			addkeycode(l, "f11",                300);
			addkeycode(l, "f12",                301);
			addkeycode(l, "f13",                302);
			addkeycode(l, "f14",                303);
			addkeycode(l, "f15",                304);
			addkeycode(l, "f16",                305);
			addkeycode(l, "f17",                306);
			addkeycode(l, "f18",                307);
			addkeycode(l, "f19",                308);
			addkeycode(l, "f20",                309);
			addkeycode(l, "f21",                310);
			addkeycode(l, "f22",                311);
			addkeycode(l, "f23",                312);
			addkeycode(l, "f24",                313);
			addkeycode(l, "f25",                314);
			addkeycode(l, "kp_0",               320);
			addkeycode(l, "kp_1",               321);
			addkeycode(l, "kp_2",               322);
			addkeycode(l, "kp_3",               323);
			addkeycode(l, "kp_4",               324);
			addkeycode(l, "kp_5",               325);
			addkeycode(l, "kp_6",               326);
			addkeycode(l, "kp_7",               327);
			addkeycode(l, "kp_8",               328);
			addkeycode(l, "kp_9",               329);
			addkeycode(l, "kp_decimal",         330);
			addkeycode(l, "kp_divide",          331);
			addkeycode(l, "kp_multiply",        332);
			addkeycode(l, "kp_subtract",        333);
			addkeycode(l, "kp_add",             334);
			addkeycode(l, "kp_enter",           335);
			addkeycode(l, "kp_equal",           336);
			addkeycode(l, "left_shift",         340);
			addkeycode(l, "left_control",       341);
			addkeycode(l, "left_alt",           342);
			addkeycode(l, "left_super",         343);
			addkeycode(l, "right_shift",        344);
			addkeycode(l, "right_control",      345);
			addkeycode(l, "right_alt",          346);
			addkeycode(l, "right_super",        347);
			addkeycode(l, "menu",               348);
		}
	};
}