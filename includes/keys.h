/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:26:26 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/27 19:32:27 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

typedef enum e_special_keys
{
	KEY_ESC = 65307,
	KEY_ENTER = 65293,
	KEY_SPACE = 32,
	KEY_TAB = 65289,
	KEY_BACKSPACE = 65288,
	KEY_DELETE = 65535,
	KEY_SHIFT_L = 65505,
	KEY_SHIFT_R = 65506,
	KEY_CTRL_L = 65507,
	KEY_CTRL_R = 65508,
	KEY_ALT_L = 65513,
	KEY_ALT_R = 65514,
	KEY_SUPER_L = 65515, // "Windows", "Command" on macOS
	KEY_SUPER_R = 65516
}	t_special_keys;

typedef enum e_arrow_keys
{
	KEY_ARROW_UP = 65362,
	KEY_ARROW_DOWN = 65364,
	KEY_ARROW_LEFT = 65361,
	KEY_ARROW_RIGHT = 65363
}	t_arrow_keys;

typedef enum e_number_keys
{
	KEY_0 = 48,
	KEY_1 = 49,
	KEY_2 = 50,
	KEY_3 = 51,
	KEY_4 = 52,
	KEY_5 = 53,
	KEY_6 = 54,
	KEY_7 = 55,
	KEY_8 = 56,
	KEY_9 = 57
}	t_number_keys;

typedef enum e_letter_keys
{
	KEY_A = 97,
	KEY_B = 98,
	KEY_C = 99,
	KEY_D = 100,
	KEY_E = 101,
	KEY_F = 102,
	KEY_G = 103,
	KEY_H = 104,
	KEY_I = 105,
	KEY_J = 106,
	KEY_K = 107,
	KEY_L = 108,
	KEY_M = 109,
	KEY_N = 110,
	KEY_O = 111,
	KEY_P = 112,
	KEY_Q = 113,
	KEY_R = 114,
	KEY_S = 115,
	KEY_T = 116,
	KEY_U = 117,
	KEY_V = 118,
	KEY_W = 119,
	KEY_X = 120,
	KEY_Y = 121,
	KEY_Z = 122
}	t_letter_keys;

typedef enum e_function_keys
{
	KEY_F1 = 65470,
	KEY_F2 = 65471,
	KEY_F3 = 65472,
	KEY_F4 = 65473,
	KEY_F5 = 65474,
	KEY_F6 = 65475,
	KEY_F7 = 65476,
	KEY_F8 = 65477,
	KEY_F9 = 65478,
	KEY_F10 = 65479,
	KEY_F11 = 65480,
	KEY_F12 = 65481
}	t_function_keys;

typedef enum e_numpad_keys
{
	KEY_NUM_0 = 65438,
	KEY_NUM_1 = 65436,
	KEY_NUM_2 = 65433,
	KEY_NUM_3 = 65435,
	KEY_NUM_4 = 65430,
	KEY_NUM_5 = 65437,
	KEY_NUM_6 = 65432,
	KEY_NUM_7 = 65429,
	KEY_NUM_8 = 65431,
	KEY_NUM_9 = 65434,
	KEY_NUM_PLUS = 65451,
	KEY_NUM_MINUS = 65453,
	KEY_NUM_MULTIPLY = 65450,
	KEY_NUM_DIVIDE = 65455,
	KEY_NUM_ENTER = 65421,
	KEY_NUM_DOT = 65439
}	t_numpad_keys;

#endif
