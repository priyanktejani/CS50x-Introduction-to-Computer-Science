from cs50 import get_string

letter = 0
word = 0
sentence = 0

# Prompt user for text
text = get_string("Text: ")

# Count letter & sentence
for i in range(len(text)):

    # Increment letter if a character is alphabetical
    if text[i].isalpha():
        letter += 1

    # Increment sentence if the text ends with '.', '!', '?'
    elif text[i] == '.' or text[i] == '!' or text[i] == '?':
        sentence += 1

# Count word
word = len(text.split())

# Calculate (US) grade level index using Coleman-Liau formula
grade = round(0.0588 * (100 * letter / word) - 0.296 * (100 * sentence / word) - 15.8)

# Print reading level
if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")