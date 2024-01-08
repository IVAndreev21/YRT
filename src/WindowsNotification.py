import mysql.connector

config = {
    "user": "sqladmin",
    "password": "Project-YRT",
    "host": "project-yrt.mysql.database.azure.com",
    "port": 3306,
    "database": "yrt",
    "ssl_ca": "C:/DigiCertGlobalRootCA.crt.pem",
    "ssl_disabled": False
}

desired_variable = "From"

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
                if date_str == current_date:
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
