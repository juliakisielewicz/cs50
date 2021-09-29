import sys
import csv


def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py CSV TXT")
        sys.exit()

    database = []
    STRs = set()

    with open(sys.argv[1]) as csv_file:
        reader = csv.DictReader(csv_file)

        for row in reader:
            for key in row:
                if key != "name":
                    STRs.add(key)
                    row[key] = int(row[key])
            database.append(row)

    with open(sys.argv[2]) as txt_file:
        dna = txt_file.read().replace("\n", "")

    stats = {}
    for item in STRs:
            stats[item] = repetitions(dna, item)

    for row in database:
        match = 0
        for seq in STRs:
            if row[seq] == stats[seq]:
                match += 1
        if match == len(STRs):
            print(row["name"])
    
    if match != len(STRs):    
        print("No match")

def repetitions(sequence, STR):
    length = len(STR)
    count = 0
    maximum = []
    c = 0
    while c < len(sequence) - length + 1:
        if sequence[c:(c+length)] == STR:
            count += 1
            c += length
        else:
            c += 1
            maximum.append(count)
            count = 0
    return max(maximum)


if __name__ == "__main__":
    main()
