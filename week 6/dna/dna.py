from sys import argv, exit
import csv


def main():

    # Ensure proper usage
    if len(argv) != 3:
        print("argv missing")
        exit(1)

    # Open CSV file
    with open(argv[1], "r") as csv_file:
        reader = csv.reader(csv_file)

        # Store header in variable
        header = next(reader)[1:]

        # Open TXT file
        with open(argv[2], "r") as txt_file:
            s = txt_file.read()

            # Populate seq throuth loop
            STRs_count = [max_repeat_str_count(s, STR) for STR in header]

        # Compare STRs & Print person name based on their DNA
        compare(reader, STRs_count)


def max_repeat_str_count(s, STR):

    # Initialize zero's in arry
    count = [0] * len(s)

    for i in range(len(s)):

        # Check for STR match
        if s[i: i + len(STR)] == STR:

            # Increase the counter by checking the previous count in arry
            count[i] = 1 + count[i - len(STR)]

    return max(count)


def compare(reader, STRs_count):

    for row in reader:
        # Store database values in variable
        values = [int(val) for val in row[1:]]

        # Compare database values with STRs count
        if values == STRs_count:
            print(row[0])
            return

    print("No match")


if __name__ == "__main__":
    main()