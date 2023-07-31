# for chanhing file permissions

# chmod +x Lab1B.sh

# To run this program : type 

# type ./Lab1B.sh

#!/bin/sh

data="emp.txt"

add_record()
{
    echo "Enter the Id of the employee : ";
    read emp_id;

    echo "Enter the name of the employee : ";
    read emp_name;
    
    echo "Enter the designation of the employee : ";
    read emp_post;

    echo "$emp_id \t $emp_name \t $emp_post" >> "$data";
}

search_record()
{
    echo "Enter the employee you want to search : ";
    read emp_name;

    grep "$emp_name" "$data";
}

display_records()
{
    cat "$data";
}

delete_record()
{
    echo "Enter the name you want to delete : ";
    read emp;
    
    grep -v -i "$emp" "$data" >> "temp.txt";
    mv "temp.txt" "$data";
    echo "record deleted successfully !!";
}

update_record()
{
    echo -n "Enter the id of the you want to update : ";
    read old_id;

    grep -v -i "$old_id" "$data" >> "temp.txt";
    mv "temp.txt" "$data";

    echo -n "Enter the new id of the employee : ";
    read new_id;

    echo -n "Enter the new name of the employee : ";
    read emp_name;

    echo -n "Enter the new designation of the employee : ";
    read emp_des;

    echo "$new_id \t $emp_name \t $emp_des" >> "$data";
    echo "Record updated successfully !!"
}

# main menu
show_menu() {
    echo "Employee Database Menu:"
    echo "1. Add new record"
    echo "2. Search record"
    echo "3. Display records"
    echo "4. Delete record"
    echo "5. Update record"
    echo "6. Exit"
    echo -n "Enter your choice (1-6): "
}

#main script

while true; do
    show_menu
    read choice

    case $choice in
        1) add_record ;;
        2) search_record ;;
        3) display_records ;;
        4) delete_record ;;
        5) update_record ;;
        6) echo "Thank you for using system !!"; exit 0 ;;
        *) echo "Invalid choice, please enter again !!" ;;
    esac

done