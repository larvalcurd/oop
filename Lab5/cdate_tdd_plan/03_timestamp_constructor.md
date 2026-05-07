# Название этапа
Реализовать конструктор из timestamp с проверкой диапазона.

## Цель
После этапа `CDate(unsigned timestamp)` корректно создаёт valid/invalid состояние.

## Предусловие
Завершён `02_default_constructor.md`.

## Список задач
1. Написать тесты для конструктора из timestamp.
2. Вычислить и зафиксировать `maxTimestamp` для 31.12.9999.
3. Реализовать проверку `timestamp <= maxTimestamp`.
4. Реализовать перевод в invalid при превышении диапазона.
5. Запустить тесты этапа.

## Тесты, которые нужно написать ДО реализации
1. `timestamp=0` -> valid.
2. `timestamp=1` -> valid.
3. `timestamp=32` -> valid.
4. `timestamp=maxTimestamp` -> valid.
5. `timestamp=maxTimestamp+1` -> invalid.

## Критерий завершённости
Конструктор из timestamp корректно различает допустимые и недопустимые значения.

## Типичные ошибки
1. Неверно посчитать `maxTimestamp`.
2. Потерять `explicit`.
3. Принять недопустимый timestamp как valid.
