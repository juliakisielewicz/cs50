from cs50 import get_int


number = get_int(Number: )

n = number
count = 0
sum1 = 0
sum2 = 0

while n != 0:
    if count % 2 == 0:
        sum1 += n % 10
    else:
        tmp = 2 * (n % 10)
        if tmp > 9:
            sum2 += (tmp % 10) + (tmp / 10)
        else:
            sum2 += tmp
    
    n /= 10
    count += 1
    
checksum = sum1 + sum2

if checksum % 10 == 0:
    if count == 15 and (number / (10 ** 13)) == 34 or (number / (10 ** 13)) == 37):
        print("AMEX")
    elif count == 16 and (number / (10 ** 14)) in range(51, 56): # == 51 or number / (10 ** 14) == 52 or number / (10 ** 14) == 53 or number / (10 ** 14) == 54 or number / (10, 14) == 55)) 
        print("MASTERCARD")
    elif ((count == 13 and number / (10 ** 12) == 4) or (count == 16 and number / (10 ** 15) == 4)):
        print("VISA")
    else:
        print("INVALID")
    
else:
    print("INVALID")
