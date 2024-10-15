--- Supermarket Management System ---

This C++ program simulates a supermarket's daily operations, allowing administrators to manage product inventory and buyers to view available products, make purchases, and generate receipts with discounts.

--- Features ---

Administrator:
-Add, edit, and delete products from the inventory.

Buyer:
-View a list of available products.
-Purchase items and receive a receipt with discounted prices.

Bill Management:
-Save generated receipts for future reference.
--- Requirements ---

To run this program, you need:

-A C++ compiler (e.g., GCC, Clang, MSVC)
-A text editor or IDE (e.g., VS Code, Code::Blocks)

--- Installation ---

Compile the Code:
-Bash
g++ -o supermarket main.cpp

Run the Executable:
-Bash
./supermarket

--- Usage ---

Run the Program and choose from the menu:

->Administrator: Login to manage product inventory.
->Buyer: View and purchase products.
->View Previous Bills: Display saved receipts.
->Exit: Quit the application.
Follow the prompts to perform actions like adding, editing, deleting products, or generating and viewing receipts.

--- Administrator Login ---

->Username: shopkeeper@gmail.com
->Password: 1234
Log in with these credentials to access the administrator options and manage the inventory.

--- Data Storage ---

The program uses text files to store product data and receipts:

->Product Inventory File: database.txt
Stores information about products, including code, name, price, and discount (one product per line, separated by spaces).

->Receipt Files: bills.txt (appended)
Saves generated receipts with details like customer name, date, purchased items with quantities and prices, and the total amount (one receipt per section).
--- Functionality Details ---

The code provides functionalities for:

Administrator Menu:

->Add products: Enter product details (code, name, price, discount) to add them to the inventory file.
->Edit products: Search for a product by code, update its details, and rewrite the inventory file.
->Delete products: Remove a product by code and update the inventory file.

Buyer Menu:
->View product list: Display all available products with their codes, names, prices, and discounts.
->Generate receipt: Enter customer name, select items with quantities, calculate discounted prices, and save the receipt details to a file.

Bill Management:
->View previous bills: Display the contents of saved receipt files.

--- Future Enhancements ---

Implement a graphical user interface (GUI) for a more user-friendly experience.
Use a database system (e.g., SQLite) for more robust data storage and management.
Introduce user roles with different access levels for better security.
This README provides a comprehensive overview of the Supermarket Management System, including its functionalities, data storage methods, and potential improvements.
