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

try:
    # Try to establish a connection
    cnx = mysql.connector.connect(**config)

    # Check if the connection is successful
    if cnx.is_connected():
        print("Connection successful!")
    else:
        print("Connection failed.")

except mysql.connector.Error as e:
    print("Error connecting to MySQL database:", e)

finally:
    # Close the connection
    cnx.close()
