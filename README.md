# VideoGraphDOS-TestTask

DOSBox является эмулятором x86-совместимой аппаратной архитектуры, которая используется в старых компьютерах. Он эмулирует процессор, звуковые карты, графические карты и другие устройства, которые были распространены в компьютерах, работающих под управлением MS-DOS.

CPU: DOSBox эмулирует процессор Intel x86, который был широко использован в старых компьютерах. В архитектуре x86 размеры типов данных отличаются от современных архитектур:

  `char - 1 байт`
  `short - 2 байта`
  `int - 2 байта`
  `long - 4 байта`
  `float - 4 байта`

Если не учесть особенности x86 архитектуры, то при обработке чанков графических файлов формата PNG возникнут проблемы.
____
## PNG Спецификация
### Сигнатура

Файл PNG состоит из подписи PNG, за которой следует серия фрагментов. Сигнатура состоит из 8 байтов:

137 80 78 71 13 10 26 10

Для того, чтобы определить является ли данный графический файл формата PNG, сравниваются первые считанные 8 байтов, для удобства
можно перевести байты в шестнадцатеричный формат - `x89PNGx0Dx0Ax1Ax0A` сравнить используя memcmp: 

`memcmp(chunk->signature, "\x89PNG\r\n\x1a\n", 8) != 0`

### Фрагменты (Chunks)
Каждый фрагмент состоит из четырех частей: длина, тип, данные фрагмента и CRC.
Длина представлена, тип фрагмента и CRC представлены 4 байтами.

Допустимое изображение в формате PNG должно содержать фрагмент `IHDR`, один или несколько фрагментов `IDAT` и фрагмент `IEND`.
Фрагмент `IHDR` встречается первым по мере чтения графического файла. Данный фрагмент содержит:

   `Width:              4 bytes`
   
   `Height:             4 bytes`
   
   `Bit depth:          1 byte`
   
   `Color type:         1 byte`
   
   `Compression method: 1 byte`
   
   `Filter method:      1 byte`
   
   `Interlace method:   1 byte`

Ширина и высота задают размеры изображения в пикселях. Разрядность - это 1 байтовое целое число, задающее количество битов на образец или на индекс палитры (не на пиксель). 

Тип цвета - это однобайтовое целое число, описывающее интерпретацию данных изображения. Ограничения разрядности для каждого цветового типа вводятся для упрощения реализации и запрета комбинаций, которые плохо сжимаются. Декодеры должны поддерживать все допустимые комбинации разрядности и цветового типа:

| Type | Bit Depths | 
| ----------- | ----------- |
| 0   | 1,2,4,8,16   |
| 2   | 8,16   |
| 3   | 1,2,4,8   |
| 4   | 8,16   |
| 6   | 8,16   |

## Видеорежим


Видеорежим - это способ отображения графики на экране компьютера, определяющий разрешение, количество цветов или оттенков серого, частоту обновления и другие параметры изображения. В зависимости от видеорежима, изображение может быть более четким, цветным или иметь более высокое разрешение.

Например,видеорежим 320x200x256 означает разрешение 320 пикселей по горизонтали, 200 пикселей по вертикали и возможность отображения 256 цветов. 

Для установки видеорежима в DOSBOX используются специальные команды, которые позволяют управлять регистрами видеокарты.
