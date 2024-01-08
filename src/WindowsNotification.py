import mysql.connector
from datetime import datetime
from win10toast import ToastNotifier

config = {
    "user": "sqladmin",
    "password": "Project-YRT",
    "host": "project-yrt.mysql.database.azure.com",
    "port": 3306,
    "database": "yrt",
    "ssl_ca": "C:/DigiCertGlobalRootCA.crt.pem",
    "ssl_disabled": False
}

desired_variable = "From"  # Replace with the actual variable name you want to retrieve

try:
    # Try to establish a connection
    cnx = mysql.connector.connect(**config)

    # Check if the connection is successful
    if cnx.is_connected():
        print("Connection successful!")

        # Execute a query to retrieve the desired variable from the 'calendar' table
        cursor = cnx.cursor()
        query = f"SELECT `{desired_variable}` FROM calendar WHERE username = 'bo'"
        cursor.execute(query)

        results = cursor.fetchall()
        if results:
            print(f"{desired_variable}s:")
            for result in results:
                date_str = result[0].strftime("%Y-%d-%m")
                current_date = datetime.now().strftime("%Y-%m-%d")
                if date_str == current_date:
                    # Display notification for matching dates
                    toaster = ToastNotifier()
                    toaster.show_toast(f"Notification for {desired_variable}", f"Date: {date_str}", duration=10)

                    print(result[0])
        else:
            print("No records found for the given username")

    else:
        print("Connection failed.")

except mysql.connector.Error as e:
    print("Error connecting to MySQL database:", e)

finally:
    # Close the connection
    cnx.close()
