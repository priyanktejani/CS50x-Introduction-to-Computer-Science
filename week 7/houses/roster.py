from sys import argv, exit
from cs50 import SQL

# Ensure proper usage
if len(argv) != 2:
    print("argv missing")
    exit(1)

# Set up a database connection
db = SQL("sqlite:///students.db")

# Store house name in variable
house = argv[1]

# Execute SQL database querie
data = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", house)

for row in data:
    # Prints a list of students for for a given house
    # Put NULL (empty string) if student middle name is None
    first, middle, last, birth = row['first'], row['middle'], row['last'], row['birth']
    print(f"{first} {middle + ' ' if middle else ''}{last}, born {birth}")