#!/usr/bin/env python3
import sys

def main():
    owner_name = sys.argv[1]
    keys = sys.argv[2:] # gets all args after owner_key

    input_lines = []

    # read lines until a new line char or ctrl+d is entered
    while True:
        try:
            line = input()
        except EOFError:
            break
        input_lines.append(line)

    inserted_keys = {} # filled with: { user: key }
    turned_keys = {} # filled with: { user: key }
    inside_house = [] # filled with user names

    for line in input_lines:
        line_split = line.split(' ')
        command = line_split[0] + " " + line_split[1]

        if command == "INSERT KEY":
            temp_user = line_split[2]
            temp_key = line_split[3]
            inserted_keys[temp_user] = temp_key
            print(f"KEY {temp_key} INSERTED BY {line_split[2]}")

        elif command == "TURN KEY":
            temp_user = line_split[2]
            temp_key = inserted_keys[temp_user]
            if temp_key in keys:
                del inserted_keys[temp_user]
                turned_keys[temp_user] = temp_key
                print(f"SUCCESS {temp_user} TURNS KEY {temp_key}")
            else:
                print(f"FAILURE {temp_user} UNABLE TO TURN KEY {temp_key}")

        elif command == "ENTER HOUSE":
            temp_user = line_split[2]
            if temp_user in turned_keys:
                del turned_keys[temp_user]
                inside_house.append(temp_user)
                print("ACCESS ALLOWED")
            else:
                print("ACCESS DENIED")

        elif command == "LEAVE HOUSE":
            temp_user = line_split[2]
            if temp_user in inside_house:
                inside_house.remove(temp_user)
                print("OK")
            else:
                print(f"{temp_user} NOT HERE")

        elif command == "WHO'S INSIDE?":
            if len(inside_house) > 0:
                print(", ".join(inside_house))
            else:
                print("NOBODY HOME")

        elif command == "CHANGE LOCKS":
            temp_user = line_split[2]
            if temp_user == owner_name:
                keys = line_split[3:]
                print("OK")
            else:
                print("ACCESS DENIED")

        else:
            print(f"ERROR: {command} not valid!")

if __name__ == "__main__":
    main()
