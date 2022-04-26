#include "InputManager.h"

#include "pgr.h"

std::map<InputManager::ImKey, bool> InputManager::keyMap = initKeyMap();
std::map<InputManager::ImKey, std::string> InputManager::keyToStringMap = initKeyToStringMap();
std::map<InputManager::ImMouseButton, bool> InputManager::mouseMap = initMouseMap();
std::map<InputManager::ImMouseButton, std::string> InputManager::mouseToStringMap = initMouseToStringMap();

std::map<InputManager::ImKey, bool> InputManager::initKeyMap()
{
    std::map<ImKey, bool> map;

    map.insert(std::pair<ImKey, bool>(IM_KEY_SPACE, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_APOSTROPHE, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_PLUS, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_COMMA, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_MINUS, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_PERIOD, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_SLASH, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_0, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_1, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_2, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_3, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_4, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_5, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_6, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_7, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_8, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_9, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_SEMICOLON, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_EQUAL, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_A, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_B, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_C, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_D, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_E, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_F, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_G, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_H, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_I, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_J, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_K, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_L, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_M, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_N, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_O, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_P, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_Q, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_R, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_S, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_T, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_U, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_V, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_W, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_X, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_Y, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_Z, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_LEFT_BRACKET, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_BACKSLASH, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_RIGHT_BRACKET, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_a, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_b, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_c, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_d, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_e, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_f, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_g, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_h, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_i, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_j, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_k, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_l, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_m, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_n, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_o, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_p, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_q, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_r, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_s, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_t, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_u, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_v, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_w, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_x, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_y, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_z, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_ESCAPE, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_ENTER, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_TAB, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_BACKSPACE, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_INSERT, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_DELETE, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_RIGHT, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_LEFT, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_DOWN, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_UP, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_PAGE_UP, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_PAGE_DOWN, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_HOME, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_END, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_F1, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_F2, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_F3, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_F4, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_F5, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_F6, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_F7, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_F8, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_F9, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_F10, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_F11, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_F12, false));
    map.insert(std::pair<ImKey, bool>(IM_KEY_UNDEFINED, false));

    return map;
}

std::map<InputManager::ImKey, std::string> InputManager::initKeyToStringMap() {
    std::map<ImKey, std::string> map;

    map.insert(std::pair<ImKey, std::string>(IM_KEY_SPACE, " "));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_APOSTROPHE, "'"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_PLUS, "+"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_COMMA, ","));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_MINUS, "-"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_PERIOD, "."));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_SLASH, "/"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_0, "0"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_1, "1"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_2, "2"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_3, "3"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_4, "4"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_5, "5"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_6, "6"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_7, "7"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_8, "8"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_9, "9"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_SEMICOLON, ";"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_EQUAL, "="));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_A, "A"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_B, "B"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_C, "C"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_D, "D"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_E, "E"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_F, "F"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_G, "G"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_H, "H"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_I, "I"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_J, "J"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_K, "K"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_L, "L"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_M, "M"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_N, "N"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_O, "O"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_P, "P"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_Q, "Q"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_R, "R"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_S, "S"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_T, "T"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_U, "U"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_V, "V"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_W, "W"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_X, "X"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_Y, "Y"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_Z, "Z"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_LEFT_BRACKET, "["));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_BACKSLASH, "\\"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_RIGHT_BRACKET, "]"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_a, "a"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_b, "b"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_c, "c"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_d, "d"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_e, "e"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_f, "f"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_g, "g"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_h, "h"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_i, "i"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_j, "j"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_k, "k"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_l, "l"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_m, "m"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_n, "n"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_o, "o"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_p, "p"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_q, "q"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_r, "r"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_s, "s"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_t, "t"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_u, "u"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_v, "v"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_w, "w"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_x, "x"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_y, "y"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_z, "z"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_ESCAPE, "ESC"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_ENTER, "ENTER"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_TAB, "TAB"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_BACKSPACE, "BACKSPACE"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_INSERT, "INSERT"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_DELETE, "DELETE"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_RIGHT, "RIGHT"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_LEFT, "LEFT"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_DOWN, "DOWN"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_UP, "UP"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_PAGE_UP, "PAGE_UP"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_PAGE_DOWN, "PAGE_DOWN"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_HOME, "HOME"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_END, "END"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_F1, "F1"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_F2, "F2"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_F3, "F3"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_F4, "F4"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_F5, "F5"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_F6, "F6"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_F7, "F7"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_F8, "F8"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_F9, "F9"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_F10, "F10"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_F11, "F11"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_F12, "F12"));
    map.insert(std::pair<ImKey, std::string>(IM_KEY_UNDEFINED, "UNDEFINED"));

    return map;
}

std::map<InputManager::ImMouseButton, bool> InputManager::initMouseMap()
{
    std::map<ImMouseButton, bool> map;

    map.insert(std::pair<ImMouseButton, bool>(IM_MOUSE_BUTTON_LEFT, false));
    map.insert(std::pair<ImMouseButton, bool>(IM_MOUSE_BUTTON_MIDDLE, false));
    map.insert(std::pair<ImMouseButton, bool>(IM_MOUSE_BUTTON_RIGHT, false));
    map.insert(std::pair<ImMouseButton, bool>(IM_MOUSE_UNDEFINED, false));

    return map;
}

std::map<InputManager::ImMouseButton, std::string> InputManager::initMouseToStringMap()
{
    std::map<ImMouseButton, std::string> map;

    map.insert(std::pair<ImMouseButton, std::string>(IM_MOUSE_BUTTON_LEFT, "LMB"));
    map.insert(std::pair<ImMouseButton, std::string>(IM_MOUSE_BUTTON_RIGHT, "RMB"));
    map.insert(std::pair<ImMouseButton, std::string>(IM_MOUSE_BUTTON_MIDDLE, "MMB"));
    map.insert(std::pair<ImMouseButton, std::string>(IM_MOUSE_UNDEFINED, "UNDEFINED"));

    return map;
}

InputManager::ImKey InputManager::glutKeyToImKey(int key) {
    switch (key) {
		case ' ':
			return IM_KEY_SPACE;
        case '\'':
            return IM_KEY_APOSTROPHE;
        case '+':
            return IM_KEY_PLUS;
        case ',':
            return IM_KEY_COMMA;
        case '-':
            return IM_KEY_MINUS;
        case '.':
            return IM_KEY_PERIOD;
        case '/':
            return IM_KEY_SLASH;
        case '0':
            return IM_KEY_0;
        case '1':
            return IM_KEY_1;
        case '2':
            return IM_KEY_2;
        case '3':
            return IM_KEY_3;
        case '4':
            return IM_KEY_4;
        case '5':
            return IM_KEY_5;
        case '6':
            return IM_KEY_6;
        case '7':
            return IM_KEY_7;
        case '8':
            return IM_KEY_8;
        case '9':
            return IM_KEY_9;
        case ';':
            return IM_KEY_SEMICOLON;
        case '=':
            return IM_KEY_EQUAL;
        case 'A':
            return IM_KEY_A;
        case 'B':
            return IM_KEY_B;
        case 'C':
            return IM_KEY_C;
        case 'D':
            return IM_KEY_D;
        case 'E':
            return IM_KEY_E;
        case 'F':
            return IM_KEY_F;
        case 'G':
            return IM_KEY_G;
        case 'H':
            return IM_KEY_H;
        case 'I':
            return IM_KEY_I;
        case 'J':
            return IM_KEY_J;
        case 'K':
            return IM_KEY_K;
        case 'L':
            return IM_KEY_L;
        case 'M':
            return IM_KEY_M;
        case 'N':
            return IM_KEY_N;
        case 'O':
            return IM_KEY_O;
        case 'P':
            return IM_KEY_P;
        case 'Q':
            return IM_KEY_Q;
        case 'R':
            return IM_KEY_R;
        case 'S':
            return IM_KEY_S;
        case 'T':
            return IM_KEY_T;
        case 'U':
            return IM_KEY_U;
        case 'V':
            return IM_KEY_V;
        case 'W':
            return IM_KEY_W;
        case 'X':
            return IM_KEY_X;
        case 'Y':
            return IM_KEY_Y;
        case 'Z':
            return IM_KEY_Z;
        case '[':
            return IM_KEY_LEFT_BRACKET;
        case '\\':
            return IM_KEY_BACKSLASH;
        case ']':
            return IM_KEY_RIGHT_BRACKET;
        case 'a':
            return IM_KEY_a;
        case 'b':
            return IM_KEY_b;
        case 'c':
            return IM_KEY_c;
        case 'd':
            return IM_KEY_d;
        case 'e':
            return IM_KEY_e;
        case 'f':
            return IM_KEY_f;
        case 'g':
            return IM_KEY_g;
        case 'h':
            return IM_KEY_h;
        case 'i':
            return IM_KEY_i;
        case 'j':
            return IM_KEY_j;
        case 'k':
            return IM_KEY_k;
        case 'l':
            return IM_KEY_l;
        case 'm':
            return IM_KEY_m;
        case 'n':
            return IM_KEY_n;
        case 'o':
            return IM_KEY_o;
        case 'p':
            return IM_KEY_p;
        case 'q':
            return IM_KEY_q;
        case 'r':
            return IM_KEY_r;
        case 's':
            return IM_KEY_s;
        case 't':
            return IM_KEY_t;
        case 'u':
            return IM_KEY_u;
        case 'v':
            return IM_KEY_v;
        case 'w':
            return IM_KEY_w;
        case 'x':
            return IM_KEY_x;
        case 'y':
            return IM_KEY_y;
        case 'z':
            return IM_KEY_z;
        case 27:
            return IM_KEY_ESCAPE;
        case 13:
            return IM_KEY_ENTER;
        case 9:
            return IM_KEY_TAB;
        case 8:
            return IM_KEY_BACKSPACE;
        default:
            return IM_KEY_UNDEFINED;
    }
}

InputManager::ImKey InputManager::glutSpecialKeyToImKey(int key)
{
    switch (key) {
	    case GLUT_KEY_INSERT:
	        return IM_KEY_INSERT;
        case GLUT_KEY_DELETE:
            return IM_KEY_DELETE;
		case GLUT_KEY_RIGHT:
            return IM_KEY_RIGHT;
        case GLUT_KEY_LEFT:
            return IM_KEY_LEFT;
        case GLUT_KEY_DOWN:
            return IM_KEY_DOWN;
        case GLUT_KEY_UP:
            return IM_KEY_UP;
        case GLUT_KEY_PAGE_UP:
            return IM_KEY_PAGE_UP;
        case GLUT_KEY_PAGE_DOWN:
            return IM_KEY_PAGE_DOWN;
        case GLUT_KEY_HOME:
            return IM_KEY_HOME;
        case GLUT_KEY_END:
            return IM_KEY_END;
        case GLUT_KEY_F1:
            return IM_KEY_F1;
        case GLUT_KEY_F2:
            return IM_KEY_F2;
        case GLUT_KEY_F3:
            return IM_KEY_F3;
        case GLUT_KEY_F4:
            return IM_KEY_F4;
        case GLUT_KEY_F5:
            return IM_KEY_F5;
        case GLUT_KEY_F6:
            return IM_KEY_F6;
        case GLUT_KEY_F7:
            return IM_KEY_F7;
        case GLUT_KEY_F8:
            return IM_KEY_F8;
        case GLUT_KEY_F9:
            return IM_KEY_F9;
		case GLUT_KEY_F10:
			return IM_KEY_F10;
        case GLUT_KEY_F11:
            return IM_KEY_F11;
        case GLUT_KEY_F12:
            return IM_KEY_F12;
        default:
            return IM_KEY_UNDEFINED;
    }
}

InputManager::ImMouseButton InputManager::glutMouseButtonToImMouseButton(int key) {
    switch (key) {
	    case GLUT_LEFT_BUTTON:
		    return IM_MOUSE_BUTTON_LEFT;
	    case GLUT_RIGHT_BUTTON:
            return IM_MOUSE_BUTTON_RIGHT;
	    case GLUT_MIDDLE_BUTTON:
            return IM_MOUSE_BUTTON_MIDDLE;
	    default:
	        return IM_MOUSE_UNDEFINED;
    }
}


void InputManager::debugPrint() {
    for (auto& entry : keyMap) {
        if (entry.second) {
            printf("Key '%s': %s\n", keyToStringMap[entry.first].c_str(), "true");
        }
    }
    for (auto& entry : mouseMap) {
        if (entry.second) {
            printf("Key '%s': %s\n", mouseToStringMap[entry.first].c_str(), "true");
        }
    }
    printf("\n");
}
