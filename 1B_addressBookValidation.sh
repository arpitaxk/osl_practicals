#!/bin/sh

# File to store the address book
ADDRESS_BOOK="address_book.txt"

# Function to create an address book
create_address_book() {
    if [ -f $ADDRESS_BOOK ]; then
        echo "Address book already exists."
    else
        touch $ADDRESS_BOOK
        echo "Address book created."
    fi
}

# Function to view the address book
view_address_book() {
    if [ ! -f $ADDRESS_BOOK ] || [ ! -s $ADDRESS_BOOK ]; then
        echo "Address book is empty."
    else
        cat $ADDRESS_BOOK
    fi
}

# Function to validate name (only alphabetic characters and spaces allowed)
validate_name() {
    local name="$1"
    # Check that the name only contains alphabetic characters and spaces
    echo "$name" | grep -qE "^[a-zA-Z[:space:]]+$"
    return $?
}

# Function to validate phone number (must be exactly 10 digits)
validate_phone() {
    local phone="$1"
    # Check if the phone number contains exactly 10 digits
    echo "$phone" | grep -qE "^[0-9]{10}$"
    return $?
}

# Function to validate email (simple regex for email format)
validate_email() {
    local email="$1"
    # Check if the email follows a basic valid pattern
    echo "$email" | grep -qE "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$"
    return $?
}

# Function to insert a new record
insert_record() {
    echo "Enter Name: "
    read name
    # Validate the name
    while ! validate_name "$name"; do
        echo "Please enter a valid name: "
        read name
    done
    
    echo "Enter Phone Number: "
    read phone
    # Validate the phone number
    while ! validate_phone "$phone"; do
        echo "Please enter a valid 10-digit phone number: "
        read phone
    done

    echo "Enter Email: "
    read email
    # Validate the email
    while ! validate_email "$email"; do
        echo "Please enter a valid email address: "
        read email
    done
    
    # Save the new record to the address book
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

    if [ -s temp.txt ]; then
        mv temp.txt $ADDRESS_BOOK
        echo "Record deleted successfully."
    else
        # If the file is empty after deletion, remove the temp file and clear the address book
        rm -f $ADDRESS_BOOK
        echo "Last record deleted, address book is now empty."
    fi
}

# Function to modify a record
modify_record() {
    echo "Enter the name of the record to modify: "
    read name
    grep -q -i "Name: $name" $ADDRESS_BOOK
    # -q does not print anything and just gives the output status
    if [ $? -eq 0 ]; then
        echo "Enter new Phone Number: "
        read new_phone
        # Validate the new phone number
        while ! validate_phone "$new_phone"; do
            echo "Please enter a valid 10-digit phone number: "
            read new_phone
        done

        echo "Enter new Email: "
        read new_email
        # Validate the new email
        while ! validate_email "$new_email"; do
            echo "Please enter a valid email address: "
            read new_email
        done

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
