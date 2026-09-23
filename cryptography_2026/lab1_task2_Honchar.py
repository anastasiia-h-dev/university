from collections import Counter
import re
from itertools import islice
import math



f_with_spaces = open("text_w_spaces.txt", "r")
f_without_spaces = open("text_wo_spaces.txt", "r")
content_with = f_with_spaces.read()
content_without = f_without_spaces.read()


count_with = Counter(content_with)
count_without = Counter(content_without)

decorator = "\n==========================================================================\n"

def SeparateSymbolFrequency():
# для одиночних символів

    print(decorator)
    print("._________________________________________________.")
    print("| 1. ЧАСТОТА ОКРЕМИХ СИМВОЛІВ (текст з пробілами) |")
    print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")

    for char, count in count_with.items():
        frequency_ws = count / len(content_with)
        print(f"'{char}' = {count} ->  {frequency_ws:.4f}")
    

    print(decorator)
    print("._________________________________________________.")
    print("| 1.ЧАСТОТА ОКРЕМИХ СИМВОЛІВ (текст без пробілів) |")
    print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
    for char, count in count_without.items():
            frequency_wo = count / len(content_without)
            print(f"'{char}' = {count} ->  {frequency_wo:.4f}")

