import mysql.connector
from datetime import datetime, timedelta
import time

config = {
    "user": "sqladmin",
    "password": "Project-YRT",
    "host": "project-yrt.mysql.database.azure.com",
    "port": 3306,
    "database": "yrt",
    "ssl_ca": "/Users/boyankiovtorov/Documents/DigiCertGlobalRootCA.crt.pem",
    "ssl_disabled": False
}

desired_variable = "Last Active"  # Replace with the actual variable name you want to retrieve

while True:
    try:
        # Try to establish a connection
        cnx = mysql.connector.connect(**config)

        # Check if the connection is successful
        if cnx.is_connected():
            print("Connection successful!")

            # Execute a query to retrieve usernames, last active dates, heirs, and balances from the 'users' table
            cursor = cnx.cursor()
            query = f"SELECT `username`, `{desired_variable}`, `Heir`, `Balance` FROM users"
            cursor.execute(query)

            # Fetch all users at once
            results = cursor.fetchall()
            current_date = datetime.now()

            for row in results:
                username = row[0]
                last_active_date_str = str(row[1])
                heir = row[2]
                balance = row[3]

                # Check if the last active date is not empty
                if last_active_date_str:
                    last_active_date = datetime.strptime(last_active_date_str, "%Y-%m-%d")

                    # Check if there is a 1-year gap
                    if last_active_date + timedelta(days=365) < current_date:
                        print(f"User {username} hasn't been online in the last year!")
                        print(f"User {username}'s Heir: {heir}")

                        # Transfer balance to the heir's balance if heir is not None and balance is not None
                        

            # Commit the changes to the database
            cnx.commit()


        else:
            print("Connection failed.")

    except mysql.connector.Error as e:
        print("Error connecting to MySQL database:", e)

    finally:
        # Close the cursor
        cursor.close()
        # Close the connection
        cnx.close()

    # Sleep for 10 seconds before the next iteration
    time.sleep(10)
