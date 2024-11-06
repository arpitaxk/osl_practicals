#!/bin/bash
#chmod +x address_book.sh
#./address_book.sh
# File to store the address book
ADDRESS_BOOK="address_book.txt"

# Function to create an address book
create_address_book() {
    if [[ -f $ADDRESS_BOOK ]]; then
        echo "Address book already exists."
    else
        touch $ADDRESS_BOOK
        echo "Address book created."
    fi
}

# Function to view the address book
view_address_book() {
    if [[ ! -f $ADDRESS_BOOK || ! -s $ADDRESS_BOOK ]]; then
        echo "Address book is empty."
    else
        cat $ADDRESS_BOOK
    fi
}

# Function to insert a new record
insert_record() {
    echo "Enter Name: "
    read name
    echo "Enter Phone Number: "
    read phone
    echo "Enter Email: "
    read email
    echo "Name: $name, Phone: $phone, Email: $email" >> $ADDRESS_BOOK
    echo "Record inserted successfully."
}

# Function to delete a record
delete_record() {
    echo "Enter the name of the record to delete: "
    read name
    # -v eliminates the particular details and gives everything except the match
    grep -v "Name: $name" $ADDRESS_BOOK > temp.txt && mv temp.txt $ADDRESS_BOOK
    echo "Record deleted (if exists)."
}

# Function to modify a record
modify_record() {
    echo "Enter the name of the record to modify: "
    read name
    #-q: quiet and -i: case insensitive
    grep -q -i "Name: $name" $ADDRESS_BOOK
    # -q does not print anything and just gives the output status, 0 means search is successful
    if [[ $? -eq 0 ]]; then
        echo "Enter new Phone Number: "
        read new_phone
        echo "Enter new Email: "
        read new_email
        # Remove the old record using grep -v and save it to a temp file
        grep -i -v "Name: $name" $ADDRESS_BOOK > temp.txt

        # Add the new modified record at the end of the file
        echo "Name: $name, Phone: $new_phone, Email: $new_email" >> temp.txt

        # Replace the original address book with the modified temp file
        mv temp.txt $ADDRESS_BOOK

        echo "Record modified."
    else
        echo "Record not found."
    fi
}

# Function to exit the script
exit_program() {
    echo "Exiting program."
    exit 0
}

# Main menu loop
while true; do
    echo "===================================="
    echo "1. Create Address Book"
    echo "2. View Address Book"
    echo "3. Insert Record"
    echo "4. Delete Record"
    echo "5. Modify Record"
    echo "6. Exit"
    echo "===================================="
    echo "Choose an option: "
    read choice

    case $choice in
        1) create_address_book ;;
        2) view_address_book ;;
        3) insert_record ;;
        4) delete_record ;;
        5) modify_record ;;
        6) exit_program ;;
        *) echo "Invalid option, please try again." ;;
    esac
done
