from cs50 import get_int

while True:

    # Prompts user for a credit card number
    ccnum = get_int("Number: ")
    if ccnum > 0:
        break

# Determine the first digit & first two digits of the credit card
one_digit = int(str(ccnum)[0])
two_digit = int(str(ccnum)[:2])

# Initialize credit card length & digit sum to 0
ccnumlen = 0
digits_sum = 0

# Iterate odd and even digits by Luhan's algorithm
while ccnum > 0:

    # Determine even digit
    if ccnumlen % 2 == 0:
        digits_sum += ccnum % 10
    else:
        # multiply odd digit by 2
        odd_digit = 2 * (ccnum % 10)

        # If the odd digit falls into two units, separate it and add it up
        digits_sum += (odd_digit // 10) + (odd_digit % 10)

    ccnumlen += 1
    ccnum //= 10

# Check if the credit card is valid and its type
isvalid = digits_sum % 10 == 0
if isvalid and (two_digit == 34 or two_digit == 37) and ccnumlen == 15:
    print("AMEX")
elif isvalid and (two_digit >= 51 and two_digit <= 55) and ccnumlen == 16:
    print("MASTERCARD")
elif isvalid and one_digit == 4 and (ccnumlen == 13 or ccnumlen == 16):
    print("VISA")
else:
    print("INVALID")