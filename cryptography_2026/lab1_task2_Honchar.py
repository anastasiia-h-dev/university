from collections import Counter
import re
from itertools import islice
import math



f_with_spaces = open("text_w_spaces.txt", "r")
f_without_spaces = open("text_wo_spaces.txt", "r")
content_with = "abcdef abcdef"#f_with_spaces.read()
content_without = "abcdefabcdef"#f_without_spaces.read()


count_with = Counter(content_with)
count_without = Counter(content_without)
length__with = len(content_with)
length__without = len(content_without)


total_bigrams_ws_step1 = 0
total_bigrams_ws_step2 = 0
total_bigrams_wo_step1 = 0
total_bigrams_wo_step2 = 0

counted_bigrams_ws_step1 = 0
counted_bigrams_ws_step2 = 0
counted_bigrams_wo_step1 = 0
counted_bigrams_wo_step2 = 0


decorator = "\n==========================================================================\n"


def SeparateSymbolFrequency(counter_object):
# для одиночних символів


    for char, count in counter_object.items():
        frequency_ws = count / length__with
        print(f"'{char}' = {count} ->  {frequency_ws:.4f}")

    print("\nСимволи з найбільшими частотами (топ 5) :")
    print(counter_object.most_common(5))



def BigramsFrequencyStep1():
    global total_bigrams_ws_step1
    global total_bigrams_wo_step1

    global counted_bigrams_ws_step1
    global counted_bigrams_wo_step1

    print(decorator)
    print(".__________________________________________________________________________________.")
    print("| 2.ЧАСТОТА БІГРАМ (для тексту з пробіліами) : біграми - пари сивмолів, з перетином|")
    print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")

    bigrams_with_spaces = [content_with[i : i + 2] for i in range(0, len(content_with) - 1, 1)]
    counted_bigrams_ws_step1 = Counter(bigrams_with_spaces)
    total_bigrams_ws_step1 = sum(counted_bigrams_ws_step1.values())
    
    for bigram, count in counted_bigrams_ws_step1.items():
        frequency_bigrams_wo = count / total_bigrams_ws_step1
        print(f"'{bigram}' = {count} -> {frequency_bigrams_wo:.4f}")

    print("\nБіграми з найбільшими частотами (топ 5) :")
    print(counted_bigrams_ws_step1.most_common(5))



    print(decorator)
    print(".__________________________________________________________________________________.")
    print("| 2.ЧАСТОТА БІГРАМ (для тексту без пробілів) : біграми - пари сивмолів, з перетином|")
    print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")

    bigrams_without_spaces = [content_without[i : i + 2] for i in range(0, len(content_without) - 1, 1)]
    counted_bigrams_wo_step1 = Counter(bigrams_without_spaces)
    total_bigrams_wo_step1 = sum(counted_bigrams_wo_step1.values())
    
    for bigram, count in counted_bigrams_wo_step1.items():
        frequency_bigrams_wo = count / total_bigrams_wo_step1
        print(f"'{bigram}' = {count} -> {frequency_bigrams_wo:.4f}")

    print("\nБіграми з найбільшими частотами (топ 5) :")
    print(counted_bigrams_wo_step1.most_common(5))



def BigramsFrequencyStep2():
    #для біграм
    
    global total_bigrams_ws_step2
    global total_bigrams_wo_step2
    
    global counted_bigrams_ws_step2
    global counted_bigrams_wo_step2


    print(decorator)
    print(".__________________________________________________________________________________.")
    print("| 2.ЧАСТОТА БІГРАМ (для тексту з пробілами) : біграми - пари сивмолів, без перетину|")
    print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
    bigrams_with_spaces = [content_with[i : i + 2] for i in range(0, len(content_with) - 1, 2)]
    counted_bigrams_ws_step2 = Counter(bigrams_with_spaces)
    total_bigrams_ws_step2 = sum(counted_bigrams_ws_step2.values())
    
    for bigram, count in counted_bigrams_ws_step2.items():
        frequency_bigrams_ws = count / total_bigrams_ws_step2
        print(f"'{bigram}' = {count} -> {frequency_bigrams_ws:.4f}")
    print("\nБіграми з найбільшими частотами (топ 5) :")
    print(counted_bigrams_ws_step2.most_common(5))



    print(decorator)
    print(".___________________________________________________________________________________.")
    print("| 2.ЧАСТОТА БІГРАМ (для тексту без пробілів) : біграми - пари сивмолів, без перетину|")
    print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
    bigrams_without_spaces = [content_without[i : i + 2] for i in range(0, len(content_without) - 1, 2)]
    counted_bigrams_wo_step2 = Counter(bigrams_without_spaces)
    total_bigrams_wo_step2 = sum(counted_bigrams_wo_step2.values())
    
    for bigram, count in counted_bigrams_wo_step2.items():
        frequency_bigrams_wo = count / total_bigrams_wo_step2
        print(f"'{bigram}' = {count} -> {frequency_bigrams_wo:.4f}")
    print("\nБіграми з найбільшими частотами (топ 5) :")
    print(counted_bigrams_wo_step2.most_common(5))




def Entropy(counter_obj, total_count, n):
    entropy = 0.0
    for count in counter_obj.values():
        p = count / total_count
        entropy += -p * math.log2(p)
    return entropy / n  # ділимо на 1 для монограм, на 2 для біграм





#output

print(decorator)
print("._________________________________________________.")
print("| 1. ЧАСТОТА ОКРЕМИХ СИМВОЛІВ (текст з пробілами) |")
print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
SeparateSymbolFrequency(count_with)

print(decorator)
print("._________________________________________________.")
print("| 1. ЧАСТОТА ОКРЕМИХ СИМВОЛІВ (текст без пробілів) |")
print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
SeparateSymbolFrequency(count_without)



BigramsFrequencyStep1()
BigramsFrequencyStep2()


print(Entropy(counted_bigrams_ws_step1, total_bigrams_ws_step1, 2))
print(Entropy(counted_bigrams_ws_step2, total_bigrams_ws_step2, 2))
print(Entropy(counted_bigrams_wo_step1, total_bigrams_wo_step1, 2))
print(Entropy(counted_bigrams_wo_step2, total_bigrams_wo_step2, 2))
