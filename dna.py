import sys
import csv

def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py CSV TXT")
        sys.exit(1)

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
        dna = txt_file.read()

    stats = {}
    for STR in STRs:
        stats[STR] = repetitions(dna, STR)

    for row in database:
        match = 0
        for STR in STRs:
            if row[STR] == stats[STR]:
                match += 1
        if match == len(STRs):
            print(row["name"])
            exit(0)
    
    print("No match")

def repetitions(sequence, STR):
    length = len(STR)
    count = 0
    tmp = 0
    i = 0
    while i < len(sequence) - length + 1:
        if sequence[i:(i+length)] == STR:
            tmp += 1
            i += length
        else:
            if count < tmp:
                count = tmp
            i += 1
            tmp = 0
    return count


if __name__ == "__main__":
    main()
