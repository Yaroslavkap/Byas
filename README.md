# Автоматическая классификация документов.
Необходимо реализовать наивный байесовский классификатор, который будет обучен на первой части входных данных и классифицировать им вторую часть.
## Формат ввода
Вам даны данные в следующем формате: <training> <test> <class_1> <data_1> <class_2> <data_2> ... <class_training> <data_training> <query_1> <query_2> ... <query_test>
В первой строке даны два числа: количество обучающих данных и количество тестовых запросов. Обучающие данные представлены парами строк, в первой строке дано одно число 0 или 1, отвечающее за номер класса, во второй строке дан весь текст документа. Тестовые данные содержат по одному документу в строке, которые необходимо классифицировать.
Тексты могут содержать любые ascii символы.
Задача реализована как интерактивная, поэтому следующий документ для классификации будет передан, только после ответа на предыдущий. Не забывайте чистить буффер!

## Формат вывода
В ответ на каждый тестовый запрос выведите единственное число 0 или 1 — предполагаемый класс документа.
