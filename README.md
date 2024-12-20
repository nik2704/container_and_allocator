## Своя реализация простого контейнера и аллокатора


#### Простой контейнер

**Параметризация аллокатором:** Контейнер параметризуется аллокатором, который по умолчанию используется как std::allocator. Это позволяет пользователю использовать свои собственные аллокаторы, если требуется.

**Аллокация и добавление элементов:**

Когда добавляется новый элемент с помощью метода add, если емкость контейнера достигнута, он увеличивает ее в два раза.
Элементы перемещаются в новый массив с помощью конструктора перемещения.

**Итератор:**
Контейнер поддерживает итератор для обхода элементов в одном направлении.

**Обход контейнера:**
Через begin() и end() возвращаются итераторы на начало и конец контейнера, что позволяет обойти все элементы с использованием стандартных циклов, например, в цикле for.


#### Аллокатор

**Объявление аллокатора:**

CustomAllocator параметризован типом данных T и размером чанка ChunkSize (по умолчанию DEFAULT_CHUNK_SIZE = 10).

**Методы аллокации:**
***allocate(std::size_t n):*** Выделяет память для n объектов типа T.
Использует ***::operator new*** для выделения сырой памяти.
Если выделение не удалось, генерируется исключение std::bad_alloc.
Сохраняет указатель на выделенную память в ptr_ и сохраняет размер в reserved_.

***deallocate(pointer p, std::size_t):***
Освобождает память, выделенную allocate. Использует ::operator delete для освобождения памяти.

***deallocate_all():***
Освобождает всю ранее выделенную память, которая хранится в ptr_.

**Вложенная структура rebind:**
Используется для обеспечения совместимости с контейнерами стандартной библиотеки (STL), которые могут работать с разными типами данных при аллокации.

