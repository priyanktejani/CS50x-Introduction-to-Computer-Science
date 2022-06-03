from cs50 import get_int

# Prompt user for height until it is an Integer and comprised between 1 and 8
while True:
    h = get_int("Height: ")

    if h > 0 and h < 9:
        break

# Print half-pyramid
for i in range(1, h + 1):
    print((h - i) * ' ' + i * '#')