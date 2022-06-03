from sys import argv, exit
from cs50 import SQL
import csv

# Ensure proper usage
if len(argv) != 2:
    print("argv missing")
    exit(1)

# Set up a database connection
db = SQL("sqlite:///students.db")

# Open the csv file
with open(argv[1], "r") as csv_file:
    reader = csv.DictReader(csv_file)

    for row in reader:

        # Split student name
        name = row["name"].split(" ")

        # Store None if students don't have middle name or not present in csv file
        if len(name) != 3:
            name[1:0] = [None]

        # Insert each student into students table
        db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                   name[0], name[1], name[2], row["house"], row["birth"])