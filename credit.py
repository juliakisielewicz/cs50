from cs50 import get_string
from math import floor

number = get_string("Number: ")

count = len(number)
sum = 0

for i in range(count - 1, -1, -1):
    if (count - 1 - i) % 2 == 0:
        sum += int(number[i])
        
    else:
        if int(number[i]) * 2 > 9:
            sum += (int(number[i]) * 2) % 10 + floor(int(number[i]) * 2 / 10)
        else:
            sum += int(number[i]) * 2
            

if sum % 10 == 0:
    if count == 15 and int(number[0]) == 3 and int(number[1]) in [4, 7]:
        print("AMEX")
    elif count == 16 and int(number[0]) == 5 and int(number[1]) in range(1, 6):
        print("MASTERCARD")
    elif (count == 13 or count == 16) and int(number[0]) == 4:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
    
    
    
    