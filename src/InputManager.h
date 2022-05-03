#pragma once
#include <map>
#include <string>

class InputManager {
public:
	enum ImKey {
		IM_KEY_SPACE = 32,
		IM_KEY_APOSTROPHE = 39,
		IM_KEY_PLUS = 43,
		IM_KEY_COMMA = 44,
		IM_KEY_MINUS = 45,
		IM_KEY_PERIOD = 46,
		IM_KEY_SLASH = 47,
		IM_KEY_0 = 48,
		IM_KEY_1 = 49,
		IM_KEY_2 = 50,
		IM_KEY_3 = 51,
		IM_KEY_4 = 52,
		IM_KEY_5 = 53,
		IM_KEY_6 = 54,
		IM_KEY_7 = 55,
		IM_KEY_8 = 56,
		IM_KEY_9 = 57,
		IM_KEY_SEMICOLON = 58,
		IM_KEY_EQUAL = 61,
		IM_KEY_A = 65,
		IM_KEY_B = 66,
		IM_KEY_C = 67,
		IM_KEY_D = 68,
		IM_KEY_E = 69,
		IM_KEY_F = 70,
		IM_KEY_G = 71,
		IM_KEY_H = 72,
		IM_KEY_I = 73,
		IM_KEY_J = 74,
		IM_KEY_K = 75,
		IM_KEY_L = 76,
		IM_KEY_M = 77,
		IM_KEY_N = 78,
		IM_KEY_O = 79,
		IM_KEY_P = 80,
		IM_KEY_Q = 81,
		IM_KEY_R = 82,
		IM_KEY_S = 83,
		IM_KEY_T = 84,
		IM_KEY_U = 85,
		IM_KEY_V = 86,
		IM_KEY_W = 87,
		IM_KEY_X = 88,
		IM_KEY_Y = 89,
		IM_KEY_Z = 90,
		IM_KEY_LEFT_BRACKET = 91,
		IM_KEY_BACKSLASH = 92,
		IM_KEY_RIGHT_BRACKET = 93,
		IM_KEY_a = 97,
		IM_KEY_b = 98,
		IM_KEY_c = 99,
		IM_KEY_d = 100,
		IM_KEY_e = 101,
		IM_KEY_f = 102,
		IM_KEY_g = 103,
		IM_KEY_h = 104,
		IM_KEY_i = 105,
		IM_KEY_j = 106,
		IM_KEY_k = 107,
		IM_KEY_l = 108,
		IM_KEY_m = 109,
		IM_KEY_n = 110,
		IM_KEY_o = 111,
		IM_KEY_p = 112,
		IM_KEY_q = 113,
		IM_KEY_r = 114,
		IM_KEY_s = 115,
		IM_KEY_t = 116,
		IM_KEY_u = 117,
		IM_KEY_v = 118,
		IM_KEY_w = 119,
		IM_KEY_x = 120,
		IM_KEY_y = 121,
		IM_KEY_z = 122,
		IM_KEY_ESCAPE,
		IM_KEY_ENTER,
		IM_KEY_TAB,
		IM_KEY_BACKSPACE,
		IM_KEY_INSERT,
		IM_KEY_DELETE,
		IM_KEY_RIGHT,
		IM_KEY_LEFT,
		IM_KEY_DOWN,
		IM_KEY_UP,
		IM_KEY_PAGE_UP,
		IM_KEY_PAGE_DOWN,
		IM_KEY_HOME,
		IM_KEY_END,
		IM_KEY_F1,
		IM_KEY_F2,
		IM_KEY_F3,
		IM_KEY_F4,
		IM_KEY_F5,
		IM_KEY_F6,
		IM_KEY_F7,
		IM_KEY_F8,
		IM_KEY_F9,
		IM_KEY_F10,
		IM_KEY_F11,
		IM_KEY_F12,
		IM_KEY_SHIFT_L,
        IM_KEY_SHIFT_R,
        IM_KEY_CTRL_L,
        IM_KEY_CTRL_R,
        IM_KEY_ALT_L,
        IM_KEY_ALT_R,
		IM_KEY_UNDEFINED = 999,
	};

	enum ImMouseButton {
		IM_MOUSE_BUTTON_LEFT,
		IM_MOUSE_BUTTON_MIDDLE,
		IM_MOUSE_BUTTON_RIGHT,
		IM_MOUSE_UNDEFINED = 999
	};

	static std::map<ImKey, bool> keyMap;
	static std::map<ImMouseButton, bool> mouseMap;

	// String conversion map
    static std::map<ImKey, std::string> keyToStringMap;
    static std::map<ImMouseButton, std::string> mouseToStringMap;

	static ImKey glutKeyToImKey(int key);
    static ImKey glutSpecialKeyToImKey(int key);
    static ImMouseButton glutMouseButtonToImMouseButton(int key);
    static int imKeyToAtbKey(ImKey key);
    static void debugPrint();

	static bool isShiftDown();
    static bool isCtrlDown();
    static bool isAltDown();

private:
	static std::map<ImKey, bool> initKeyMap();
    static std::map<ImKey, std::string> initKeyToStringMap();
	static std::map<ImMouseButton, bool> initMouseMap();
    static std::map<ImMouseButton, std::string> initMouseToStringMap();
};
