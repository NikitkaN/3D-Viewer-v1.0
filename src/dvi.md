## Установка

Внимание, если вы запускаете с винды, то может потребоваться отдельное приложение для запуска вьюера!
Для установки вьюера нужно, находясь в папке src, написать в терминале:

> make install

Установка может занять около минуты, потом в папке build (нужно выйти из src) будет файл ogltest1.

## Запуск

Перейдя в папку build, нужно запустить ogltest1:

> ./ogltest1

## Работа вьюера

Программа представляет функционал для просмотра 3D моделей в каркасном виде (3D Viewer). Сами модели загружаются из файлов формата .obj и имеется возможность просматривать их на экране с возможностью вращения, масштабирования и перемещения.

## Создание архива

Нужно снова зайти в src и написать команду:

> make dist

## Удаление

Для удаления проекта нужно в src прописать команду:

> make uninstall
