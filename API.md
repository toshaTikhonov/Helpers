# BankFramework API Documentation

- [Использование Helpers в C программах](#use-helpers-in-a-c-program)
  - [Заголовочные файлы](#header-file)
  - [опции сбрки](#build-options)
- [Реализация дополнительного функционала для работы библиотеки](#dependens-src)

## Использование Helpers в C программах <a name="use-helpers-in-a-c-program"></a>

### Заголовочные файлы <a name="header-file"></a>
```

### Опции сборки <a name="build-options"></a>

Вы также должны использовать `pkg-config`, чтобы получить опции линковки BankFramework:

```shell
$ # compile flags
$ pkg-config --cflags libHelpers
-I/usr/include
$ # linker flags
$ pkg-config --libs libHelpers
-L/usr/lib -lHelpers
```

Если вы не используете  pkg-config для сборки, вы должны установить следующие  опции для линковки `-lHelpers`.

## Реализация дополнительного функционала для работы библиотеки <a name="dependens-src"></a>

