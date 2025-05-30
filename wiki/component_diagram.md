# Диаграмма компонентов  
**Описание:** Архитектура проекта на языке C.  

## Компоненты:  
1. **Консольный интерфейс**: Ввод/вывод данных через терминал.  
2. **Основное приложение**: Управление логикой программы.  
3. **Модуль аутентификации**: Проверка логина/пароля.  
4. **Модуль CRUD**: Операции над данными.  
5. **Модуль работы с БД**: Низкоуровневые SQL-запросы.  
6. **Вспомогательные утилиты**: Функции для валидации и форматирования.  
7. **Библиотека SQLite3**: Внешняя библиотека для работы с БД.  
8. **Файлы БД**: people.db (хранение данных), schema.sql (структура таблиц).  
9. **Тесты**: Проверка работы модулей.  
10. **Сборка (Makefile)**: Автоматизация компиляции.  
11. **Документация**: README.md, API.md.  

## Связи:  
- **Консольный интерфейс** ↔ **Основное приложение**: Передача команд.  
- **Основное приложение** ↔ **Модуль аутентификации/CRUD**: Вызов функций.  
- **Модуль CRUD** ↔ **Модуль работы с БД**: Использование SQL-запросов.  
- **Модуль работы с БД** ↔ **Библиотека SQLite3**: Выполнение запросов.  
- **Модуль работы с БД** ↔ **Файлы БД**: Чтение/запись данных.  
- **Тесты** ↔ **Модуль работы с БД/аутентификации**: Проверка функционала.  
- **Сборка** ↔ **Все исходные файлы**: Компиляция в исполняемый файл.  
