# Calculator Project (GUI + Backend)

Проект калькулятора с графическим интерфейсом на Qt6 и backend-логикой на C++.

## Требования

Для запуска проекта нужна библиотека Qt6 и cpputest фрейворк для тестирования.

## Документация

- **[DIFFERENCES.md](DIFFERENCES.md)** - Подробное сравнение с оригинальной реализацией Windows Calculator (на русском языке)
- **[DIFFERENCES_EN.md](DIFFERENCES_EN.md)** - Detailed comparison with original Windows Calculator implementation (English version)

## Структура проекта

- `CalculatorBackEnd/` - Логика калькулятора и юнит-тесты
  - `src/production/` - Основной код логики калькулятора
  - `src/tests/` - Юнит-тесты (CppUTest)
- `StandardCalcProj/` - GUI приложение на Qt6