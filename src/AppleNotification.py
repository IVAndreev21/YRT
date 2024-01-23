import subprocess
import mysql.connector
from datetime import datetime
import sys


username = sys.argv[1]
config = {
    "user": "sqladmin",
    "password": "Project-YRT",
    "host": "project-yrt.mysql.database.azure.com",
    "port": 3306,
    "database": "yrt",
    "ssl_ca": "C:/DigiCertGlobalRootCA.crt.pem",
    "ssl_disabled": False
}

def send_notification(title, message):
    applescript = f'''
        display notification "{message}" with title "{title}"
    '''
    subprocess.run(['osascript', '-e', applescript])

try:
    # Try to establish a connection
    cnx = mysql.connector.connect(**config)

    # Check if the connection is successful
    if cnx.is_connected():
        print("Connection successful!")

        # Execute a query to retrieve the desired variable from the 'calendar' table
        cursor = cnx.cursor()
        query = f"SELECT * FROM calendar WHERE username = '{username}'"
        cursor.execute(query)

        results = cursor.fetchall()
        if results:
            for result in results:
                eventTitle = result[2]
                eventDescription = result[3]
                date_str = result[4].strftime("%Y-%m-%d")
                current_date = datetime.now().strftime("%Y-%m-%d")
                if date_str == current_date:
                    # Display notification for matching dates
                    send_notification(eventTitle, eventDescription)

        else:
            print("No records found for the given username")

    else:
        print("Connection failed.")

except mysql.connector.Error as e:
    print("Error connecting to MySQL database:", e)

finally:
    # Close the connection
    cnx.close()

