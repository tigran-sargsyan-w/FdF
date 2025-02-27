/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_masks.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:43:27 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/27 18:53:25 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_MASKS_H
# define EVENT_MASKS_H

typedef enum e_event_mask
{
	NO_EVENT_MASK = 0L,                      // Нет событий
	KEY_PRESS_MASK = (1L << 0),              // Нажатие клавиши
	KEY_RELEASE_MASK = (1L << 1),            // Отпускание клавиши
	BUTTON_PRESS_MASK = (1L << 2),           // Нажатие кнопки мыши
	BUTTON_RELEASE_MASK = (1L << 3),         // Отпускание кнопки мыши
	ENTER_WINDOW_MASK = (1L << 4),           // Курсор вошёл в окно
	LEAVE_WINDOW_MASK = (1L << 5),           // Курсор покинул окно
	POINTER_MOTION_MASK = (1L << 6),         // Движение мыши
	POINTER_MOTION_HINT_MASK = (1L << 7),    // Движение мыши (с подсказками)
	BUTTON1_MOTION_MASK = (1L << 8),         // Движение с зажатой кнопкой 1
	BUTTON2_MOTION_MASK = (1L << 9),         // Движение с зажатой кнопкой 2
	BUTTON3_MOTION_MASK = (1L << 10),        // Движение с зажатой кнопкой 3
	BUTTON4_MOTION_MASK = (1L << 11),        // Движение с зажатой кнопкой 4
	BUTTON5_MOTION_MASK = (1L << 12),        // Движение с зажатой кнопкой 5
	BUTTON_MOTION_MASK = (1L << 13),         // Движение с зажатой кнопкой
	KEYMAP_STATE_MASK = (1L << 14),          // Изменение состояния клавиатуры
	EXPOSURE_MASK = (1L << 15),              // Требуется перерисовка окна
	VISIBILITY_CHANGE_MASK = (1L << 16),     // Изменение видимости окна
	STRUCTURE_NOTIFY_MASK = (1L << 17),      // Окно изменило структуру
	RESIZE_REDIRECT_MASK = (1L << 18),       // Запрос на изменение размера окна
	SUBSTRUCTURE_NOTIFY_MASK = (1L << 19),   // Изменение структуры вл. окон
	SUBSTRUCTURE_REDIRECT_MASK = (1L << 20), // изменение структуры вл. окон
	FOCUS_CHANGE_MASK = (1L << 21),          // Окно получило/потеряло фокус
	PROPERTY_CHANGE_MASK = (1L << 22),       // Изменение свойств окна
	COLORMAP_CHANGE_MASK = (1L << 23),       // Изменение цветовой палитры
	OWNER_GRAB_BUTTON_MASK = (1L << 24)      // События для захвата мыши
}	t_event_mask;

#endif
