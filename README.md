# Tolkachov_TestTask

Суть игры в том, чтобы собрать все огоньки (души) на уровне и открыть портал на следующий уровень. Как только игрок соберет 20 огоньков, в дверях в углу карты появится портал, и если пройти через него, уровень завершится. Процесс создания:

1. За основу взята пустая карта Empty world. Создана сцена с освещением, ландшафтом, текстурами и растительностью.
2. Создан персонаж, skeletal mesh которого взят из ассета Windwalker Echo.
3. Логика управления персонажем написана с помощью Enhanced input на C++.
4. Создан animation blueprint ABP_EchoCharacter, где осуществляется логика анимации персонажа: Idle, Run, Jump.
5. Вся логика взаимодействия персонажа с окружением написана на C++ в файлах EchoCharacter.h и EchoCharacter.cpp.
6. Создано несколько отдельных C++ классов для логики души, виджетов, атрибутов персонажа, портала и т. д.
7. Эффекты души и портала созданы с помощью Niagara system.
8. Логика появления портала написана на blueprints в классе BP_EchoCharacter
9. Добавлены звуковые эффекты для бега и прыжка персонажа, а также для его взаимодействия с душами.
10. Создано меню начала и завершения игры с помощью blueprints.
