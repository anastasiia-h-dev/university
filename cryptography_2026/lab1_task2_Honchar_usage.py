from collections import Counter
import re
from itertools import islice
import math



#f_with_spaces = open("text_w_spaces.txt", "r")
#f_without_spaces = open("text_wo_spaces.txt", "r")
content_with = "abc abc abc abc"#f_with_spaces.read()
content_without = "abc abc abc abc"#f_without_spaces.read()


count_with = Counter(content_with)
count_without = Counter(content_without)
length__with = len(content_with)
length__without = len(content_without)


decorator = "\n==========================================================================\n"


def SeparateSymbolFrequency(counter_object, total_length):
# для одиночних символів


    for char, count in counter_object.items():
        frequency_ws = count / total_length
        print(f"'{char}' = {count} ->  {frequency_ws:.4f}")

    print("\nСимволи з найбільшими частотами (топ 5) :")
    print(counter_object.most_common(5))



def BigramsFrequencyStep1(content, step):
    bigrams = [content[i : i + 2] for i in range(0, len(content) - 1, step)]
    counted_bigrams = Counter(bigrams)
    total_bigrams = sum(counted_bigrams.values())
    
    for bigram, count in counted_bigrams.items():
        frequency_bigrams = count / total_bigrams
        print(f"'{bigram}' = {count} -> {frequency_bigrams:.4f}")

    print("\nБіграми з найбільшими частотами (топ 5) :")
    print(counted_bigrams.most_common(5))

    result = [counted_bigrams, total_bigrams]
    return result



def Entropy(counter_obj, total_count, n):
    entropy = 0.0
    for count in counter_obj.values():
        p = count / total_count
        entropy += -p * math.log2(p)
    return entropy / n  # ділимо на 1 для монограм, на 2 для біграм





#output

# print(decorator)
# print("._________________________________________________.")
# print("| 1. ЧАСТОТА ОКРЕМИХ СИМВОЛІВ (текст з пробілами) |")
# print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
# SeparateSymbolFrequency(count_with, length__with)

# print(decorator)
# print("._________________________________________________.")
# print("| 1. ЧАСТОТА ОКРЕМИХ СИМВОЛІВ (текст без пробілів)|")
# print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
# SeparateSymbolFrequency(count_without, length__without)



bigrams_step1 = BigramsFrequencyStep1(content_with, 1)

#BigramsFrequencyStep2()

# print(decorator)
# print("._________________________________________________.")
# print("| 4. ЕНТРОПІЯ H1                                  |")
# print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
# print(Entropy(count_with, length__with, 1))
# print(Entropy(count_without, length__without, 1))


print(decorator)
print("._________________________________________________.")
print("| 4. ЕНТРОПІЯ H2                                  |")
print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
print(f"(з пробілами, step=1) : {Entropy(bigrams_step1[0], bigrams_step1[1], 2)}")
# print(f"(з пробілами, step=2) : {Entropy(counted_bigrams_ws_step2, total_bigrams_ws_step2, 2)}")
# print(f"(без пробілів, step=1) : {Entropy(counted_bigrams_wo_step1, total_bigrams_wo_step1, 2)}")
# print(f"(без пробілів, step=2) : {Entropy(counted_bigrams_wo_step2, total_bigrams_wo_step2, 2)}")
