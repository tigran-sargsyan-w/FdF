/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:18:01 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/27 19:04:49 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

typedef enum e_event
{
	ON_KEYDOWN = 2,            // Нажатие клавиши
	ON_KEYUP = 3,              // Отпускание клавиши
	ON_MOUSEDOWN = 4,          // Нажатие кнопки мыши
	ON_MOUSEUP = 5,            // Отпускание кнопки мыши
	ON_MOUSEMOVE = 6,          // Движение мыши
	ON_ENTER_NOTIFY = 7,       // Курсор вошёл в окно
	ON_LEAVE_NOTIFY = 8,       // Курсор покинул окно
	ON_FOCUS_IN = 9,           // Окно получило фокус
	ON_FOCUS_OUT = 10,         // Окно потеряло фокус
	ON_KEYMAP_NOTIFY = 11,     // Изменение раскладки клавиатуры
	ON_EXPOSE = 12,            // Окно требует перерисовки
	ON_GRAPHICS_EXPOSE = 13,   // Графическая область окна изменилась
	ON_NO_EXPOSE = 14,         // Перерисовка не требуется
	ON_VISIBILITY_NOTIFY = 15, // Изменение видимости окна
	ON_CREATE_NOTIFY = 16,     // Окно создано
	ON_DESTROY_NOTIFY = 17,    // Окно закрывается
	ON_UNMAP_NOTIFY = 18,      // Окно спрятано
	ON_MAP_NOTIFY = 19,        // Окно показано
	ON_MAP_REQUEST = 20,       // Запрос на отображение окна
	ON_REPARENT_NOTIFY = 21,   // Окно перемещено в другое окно
	ON_CONFIGURE_NOTIFY = 22,  // Изменение размеров окна
	ON_CONFIGURE_REQUEST = 23, // Запрос на изменение размеров окна
	ON_GRAVITY_NOTIFY = 24,    // Изменение привязки окна
	ON_RESIZE_REQUEST = 25,    // Запрос на изменение размеров окна
	ON_CIRCULATE_NOTIFY = 26,  // Порядок окон изменён
	ON_CIRCULATE_REQUEST = 27, // Запрос на изменение порядка окон
	ON_PROPERTY_NOTIFY = 28,   // Изменение свойств окна
	ON_SELECTION_CLEAR = 29,   // Очистка выделения
	ON_SELECTION_REQUEST = 30, // Запрос на копирование данных
	ON_SELECTION_NOTIFY = 31,  // Данные вставлены из буфера обмена
	ON_COLORMAP_NOTIFY = 32,   // Изменение цветовой палитры окна
	ON_CLIENT_MESSAGE = 33,    // Сообщение от клиента (например, ALT+F4)
	ON_MAPPING_NOTIFY = 34,    // Изменение привязки клавиш
	ON_GENERIC_EVENT = 35,     // Общие события системы
	ON_LAST_EVENT = 36         // Последнее возможное событие
}	t_event;

#endif
