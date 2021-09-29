from cs50 import get_string

def main():
    
    text = get_string("Text: ")

    grade = calculateIndex(text)
    
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


def calculateIndex(txt):
    
    #counting letters
    letters = 0
    for i in range(len(txt)):
        if txt[i].isalpha():
            letters += 1
    
    #counting words
    words_list = txt.split()
    words = len(words_list)
    
    #counting sentences
    txt = txt.replace("!", ".")
    txt = txt.replace("?", ".")
    sentences_list = txt.split('.')
    sentences = len(sentences_list) - 1
    
    index = round(0.0588 * letters * 100 / words - 0.296 * sentences * 100 / words - 15.8)

    return index
    
if __name__ == "__main__":
    main()
        