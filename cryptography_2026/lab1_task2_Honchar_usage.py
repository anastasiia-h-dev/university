from lab1_task2_Honchar import *

from collections import Counter
import re
from itertools import islice
import math

decorator = "\n==========================================================================\n"

with open("text_w_spaces.txt", "r", encoding="utf-8") as f:
    content_with = f.read()

with open("text_wo_spaces.txt", "r", encoding="utf-8") as f:
    content_without = f.read()

#content_with = "abc abc abc abc"#f_with_spaces.read()
#content_without = "abc abc abc abc"#f_without_spaces.read()


print(decorator)
print(".___________________________________________________.")
print("| 1.1. ЧАСТОТА ОКРЕМИХ СИМВОЛІВ (текст з пробілами) |")
print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
SeparateSymbolFrequency(content_with)

print(decorator)
print(".___________________________________________________.")
print("| 1.2. ЧАСТОТА ОКРЕМИХ СИМВОЛІВ (текст без пробілів)|")
print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
SeparateSymbolFrequency(content_without)





print(decorator)
print(".________________________________________________________.")
print("| 2.1.1. ЧАСТОТА БІГРАМ (текст з пробілами, з перетином) |")
print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
BigramsFrequency(content_with, 1)

print(decorator)
print(".________________________________________________________.")
print("| 2.1.2. ЧАСТОТА БІГРАМ (текст з пробілами, без перетину)|")
print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
BigramsFrequency(content_with, 2)



print(decorator)
print("._______________________________________________________________.")
print("| 2.2.1. ЧАСТОТА БІГРАМ (текст без пробілів, з перетином).      |")
print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
BigramsFrequency(content_without, 1)

print(decorator)
print("._________________________________________________________.")
print("| 2.2.2. ЧАСТОТА БІГРАМ (текст без пробілів, без перетину)|")
print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
BigramsFrequency(content_without, 2)




#поки що не придумала як зробити виклик цієї функції симпатичнішим
#поки що передача аргументів якась неефективна та незручна
#треба вручну визначити об'єкт Count для тексту/стрічки
#треба вручнувизначити довжину тексту/стрічки з якими працюємо
#для біграми трохи інакше
count_with = Counter(content_with)
count_without = Counter(content_without)
length__with = len(content_with)
length__without = len(content_without)
print(decorator)
print("._________________________________________________.")
print("| 3.1. ЕНТРОПІЯ H1 (текст з пробілами)              |")
print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
print(f"(з пробілами, step=1) : {Entropy(count_with, length__with, 1)}")

print(decorator)
print("._________________________________________________.")
print("| 3.2. ЕНТРОПІЯ H1 (текст без пробілів)             |")
print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
print(Entropy(count_without, length__with, 1))




#тут теж поки що не дуже зручно
#треба самостійно витягати потрібні аргументи з функції BigramsFrequency
bigrams_step1 = BigramsFrequency(content_with, 1)
bigrams_step2 = BigramsFrequency(content_with, 2)
print(decorator)
print(".____________________________________________________________.")
print("| 4.1.1. ЕНТРОПІЯ H2 (текст з пробілами, біграми з перетином)|")
print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
print(f"(з пробілами, step=1) : {Entropy(bigrams_step1[0], bigrams_step1[1], 2)}")


print(decorator)
print(".______________________________________________________________.")
print("| 4.1.2. ЕНТРОПІЯ H2 (текст з пробілами, біграми без перетину) |")
print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
print(f"(без пробілів, step=2) : {Entropy(bigrams_step1[0], bigrams_step1[1], 2)}")


print(decorator)
print(".______________________________________________________________.")
print("| 4.2.1. ЕНТРОПІЯ H2 (текст без пробілів, біграми з перетином) |")
print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
print(f"(без пробілів, step=1) : {Entropy(bigrams_step2[0], bigrams_step2[1], 2)}")


print(decorator)
print("._______________________________________________________________.")
print("| 4.2.2. ЕНТРОПІЯ H2  (текст без пробілів, біграми без перетину)|")
print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
print(f"(з пробілами, step=2) : {Entropy(bigrams_step2[0], bigrams_step2[1], 2)}")
