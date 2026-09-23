from collections import Counter
import re
from itertools import islice
import math



f_with_spaces = open("text_w_spaces.txt", "r")
f_without_spaces = open("text_wo_spaces.txt", "r")
content_with = "abcdefabcdef"#f_with_spaces.read()
content_without = "abcdefabcdef"#f_without_spaces.read()


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



def BigramsFrequency():
    #для біграм
    print(decorator)
    print("._________________________________________________________________________.")
    print("| 2.ЧАСТОТА БІГРАМ (для тексту з пробілами) : біграми - слова, з перетином|")
    print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")

    bigram_words = re.findall("\w+", content_with)
    counted_bigram_words = Counter(zip(bigram_words, islice(bigram_words, 1, None)))
    total_bigrams_1 = sum(counted_bigram_words.values())
    for pair, count in counted_bigram_words.items():
        bigram_words_freq = count / total_bigrams_1
        print(f"{pair} = {count} -> {bigram_words_freq:.4f}")

    

    print(decorator)
    print(".____________________________________________.")
    print("| 2.ЧАСТОТА БІГРАМ (для тексту без пробілів) : біграми - пари сивмолів, без перетину|")
    print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")
    bigrams_without_spaces = [content_without[i : i + 2] for i in range(0, len(content_without) - 1, 2)]
    counted_bigrams_without_spaces = Counter(bigrams_without_spaces)
    total_bigrams_2 = sum(counted_bigrams_without_spaces.values())
    
    for bigram, count in counted_bigrams_without_spaces.items():
        frequency_bigrams_wo = count / total_bigrams_2
        print(f"'{bigram}' = {count} -> {frequency_bigrams_wo:.4f}")

    print(decorator)
    print(".____________________________________________.")
    print("| 2.ЧАСТОТА БІГРАМ (для тексту без пробілів) : біграми - пари сивмолів, з перетином|")
    print("'‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾'")

    bigrams_without_spaces = [content_without[i : i + 2] for i in range(0, len(content_without) - 1, 1)]
    counted_bigrams_without_spaces = Counter(bigrams_without_spaces)
    total_bigrams_2 = sum(counted_bigrams_without_spaces.values())
    
    for bigram, count in counted_bigrams_without_spaces.items():
        frequency_bigrams_wo = count / total_bigrams_2
        print(f"'{bigram}' = {count} -> {frequency_bigrams_wo:.4f}")

#SeparateSymbolFrequency()
BigramsFrequency()