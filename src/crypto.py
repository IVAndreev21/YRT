from PyQt6 import QtCore, QtGui, QtWidgets
import cryptocompare
import mysql.connector
from datetime import datetime
import sys
config = {
    "user": "sqladmin",
    "password": "Project-YRT",
    "host": "project-yrt.mysql.database.azure.com",
    "port": 3306,
    "database": "yrt",
    "ssl_ca": "C:/DigiCertGlobalRootCA.crt.pem",
    "ssl_disabled": False
}

username = sys.argv[1]


class Ui_Crypto(object):

    def __init__(self):
        try:
            # Establish a connection
            self.cnx = mysql.connector.connect(**config)
            if self.cnx.is_connected():
                print("Connection successful!")
            else:
                print("Connection failed.")
        except mysql.connector.Error as e:
            print("Error connecting to MySQL database:", e)

    def setupUi(self, Crypto):
        Crypto.setObjectName("Crypto")
        Crypto.resize(1280, 720)
        self.line = QtWidgets.QFrame(parent=Crypto)
        self.line.setGeometry(QtCore.QRect(150, -10, 16, 751))
        self.line.setFrameShape(QtWidgets.QFrame.Shape.VLine)
        self.line.setFrameShadow(QtWidgets.QFrame.Shadow.Sunken)
        self.line.setObjectName("line")
        self.stackedWidget = QtWidgets.QStackedWidget(parent=Crypto)
        self.stackedWidget.setGeometry(QtCore.QRect(150, -20, 1161, 751))
        self.stackedWidget.setObjectName("stackedWidget")
        self.Dashboard = QtWidgets.QWidget()
        self.Dashboard.setObjectName("Dashboard")
        self.widget_2 = QtWidgets.QWidget(parent=self.Dashboard)
        self.widget_2.setGeometry(QtCore.QRect(10, 10, 1121, 731))
        self.widget_2.setStyleSheet("background-color: rgb(39, 40, 40);\n"
"border-radius:10px;\n"
"color: white;")
        self.widget_2.setObjectName("widget_2")
        self.widget = QtWidgets.QWidget(parent=self.widget_2)
        self.widget.setGeometry(QtCore.QRect(10, 40, 341, 291))
        self.widget.setStyleSheet("background-color: rgb(57, 58, 58);\n"
"border-radius:30px;")
        self.widget.setObjectName("widget")
        self.SOL_img_LA = QtWidgets.QLabel(parent=self.widget)
        self.SOL_img_LA.setGeometry(QtCore.QRect(10, 70, 61, 61))
        self.SOL_img_LA.setText("")
        self.SOL_img_LA.setPixmap(QtGui.QPixmap("../resources/solana.svg"))
        self.SOL_img_LA.setScaledContents(True)
        self.SOL_img_LA.setObjectName("SOL_img_LA")
        self.bitcoin_img_LA = QtWidgets.QLabel(parent=self.widget)
        self.bitcoin_img_LA.setGeometry(QtCore.QRect(10, 10, 61, 51))
        self.bitcoin_img_LA.setText("")
        self.bitcoin_img_LA.setScaledContents(True)
        self.bitcoin_img_LA.setObjectName("bitcoin_img_LA")
        self.bitcoin_img_LA.setPixmap(QtGui.QPixmap("../resources/bitcoin.png"))
        self.BNB_img_LA = QtWidgets.QLabel(parent=self.widget)
        self.BNB_img_LA.setGeometry(QtCore.QRect(10, 210, 61, 61))
        self.BNB_img_LA.setText("")
        self.BNB_img_LA.setPixmap(QtGui.QPixmap("../resources/binance.png"))
        self.BNB_img_LA.setScaledContents(True)
        self.BNB_img_LA.setObjectName("BNB_img_LA")
        self.ETH_img_LA = QtWidgets.QLabel(parent=self.widget)
        self.ETH_img_LA.setGeometry(QtCore.QRect(10, 140, 61, 61))
        self.ETH_img_LA.setText("")
        self.ETH_img_LA.setPixmap(QtGui.QPixmap("../resources/etherium.png"))
        self.ETH_img_LA.setScaledContents(True)
        self.ETH_img_LA.setObjectName("ETH_img_LA")
        self.Bitcon_LA = QtWidgets.QLabel(parent=self.widget)
        self.Bitcon_LA.setGeometry(QtCore.QRect(80, 20, 58, 16))
        self.Bitcon_LA.setStyleSheet("color: white;")
        self.Bitcon_LA.setObjectName("Bitcon_LA")
        self.BTC_LA = QtWidgets.QLabel(parent=self.widget)
        self.BTC_LA.setGeometry(QtCore.QRect(80, 40, 58, 16))
        self.BTC_LA.setStyleSheet("color: white;")
        self.BTC_LA.setObjectName("BTC_LA")
        self.line_2 = QtWidgets.QFrame(parent=self.widget)
        self.line_2.setGeometry(QtCore.QRect(10, 70, 118, 3))
        self.line_2.setFrameShape(QtWidgets.QFrame.Shape.HLine)
        self.line_2.setFrameShadow(QtWidgets.QFrame.Shadow.Sunken)
        self.line_2.setObjectName("line_2")
        self.solana_LA = QtWidgets.QLabel(parent=self.widget)
        self.solana_LA.setGeometry(QtCore.QRect(80, 80, 58, 16))
        self.solana_LA.setStyleSheet("color: white;")
        self.solana_LA.setObjectName("solana_LA")
        self.SOL_LA = QtWidgets.QLabel(parent=self.widget)
        self.SOL_LA.setGeometry(QtCore.QRect(80, 100, 58, 16))
        self.SOL_LA.setStyleSheet("color: white;")
        self.SOL_LA.setObjectName("SOL_LA")
        self.Etherium_LA = QtWidgets.QLabel(parent=self.widget)
        self.Etherium_LA.setGeometry(QtCore.QRect(70, 140, 58, 16))
        self.Etherium_LA.setStyleSheet("color: white;")
        self.Etherium_LA.setObjectName("Etherium_LA")
        self.ETH_LA = QtWidgets.QLabel(parent=self.widget)
        self.ETH_LA.setGeometry(QtCore.QRect(70, 170, 58, 16))
        self.ETH_LA.setStyleSheet("color: white;")
        self.ETH_LA.setObjectName("ETH_LA")
        self.Binance_LA = QtWidgets.QLabel(parent=self.widget)
        self.Binance_LA.setGeometry(QtCore.QRect(80, 220, 58, 16))
        self.Binance_LA.setStyleSheet("color: white;")
        self.Binance_LA.setObjectName("Binance_LA")
        self.BNB_LA = QtWidgets.QLabel(parent=self.widget)
        self.BNB_LA.setGeometry(QtCore.QRect(80, 250, 58, 16))
        self.BNB_LA.setStyleSheet("color: white;")
        self.BNB_LA.setObjectName("BNB_LA")
        self.BTC_price_LA = QtWidgets.QLabel(parent=self.widget)
        self.BTC_price_LA.setGeometry(QtCore.QRect(160, 20, 121, 16))
        self.BTC_price_LA.setText("")
        self.BTC_price_LA.setObjectName("BTC_price_LA")
        self.now_LA = QtWidgets.QLabel(parent=self.widget)
        self.now_LA.setGeometry(QtCore.QRect(170, 40, 71, 16))
        self.now_LA.setStyleSheet("color: white;")
        self.now_LA.setObjectName("now_LA")
        self.SOL_price_LA = QtWidgets.QLabel(parent=self.widget)
        self.SOL_price_LA.setGeometry(QtCore.QRect(160, 80, 101, 16))
        self.SOL_price_LA.setText("")
        self.SOL_price_LA.setObjectName("SOL_price_LA")
        self.now_LA_3 = QtWidgets.QLabel(parent=self.widget)
        self.now_LA_3.setGeometry(QtCore.QRect(170, 110, 71, 16))
        self.now_LA_3.setStyleSheet("color: white;")
        self.now_LA_3.setObjectName("now_LA_3")
        self.now_LA_2 = QtWidgets.QLabel(parent=self.widget)
        self.now_LA_2.setGeometry(QtCore.QRect(170, 170, 71, 16))
        self.now_LA_2.setStyleSheet("color: white;")
        self.now_LA_2.setObjectName("now_LA_2")
        self.now_LA_4 = QtWidgets.QLabel(parent=self.widget)
        self.now_LA_4.setGeometry(QtCore.QRect(170, 250, 71, 16))
        self.now_LA_4.setStyleSheet("color: white;")
        self.now_LA_4.setObjectName("now_LA_4")
        self.ETH_price_LA = QtWidgets.QLabel(parent=self.widget)
        self.ETH_price_LA.setGeometry(QtCore.QRect(160, 140, 91, 20))
        self.ETH_price_LA.setText("")
        self.ETH_price_LA.setObjectName("ETH_price_LA")
        self.BNB_price_LA = QtWidgets.QLabel(parent=self.widget)
        self.BNB_price_LA.setGeometry(QtCore.QRect(160, 220, 101, 20))
        self.BNB_price_LA.setText("")
        self.BNB_price_LA.setObjectName("BNB_price_LA")
        self.label = QtWidgets.QLabel(parent=self.widget)
        self.label.setGeometry(QtCore.QRect(130, 0, 61, 20))
        self.label.setStyleSheet("color: white;")
        self.label.setObjectName("label")
        self.portfolio_LA = QtWidgets.QLabel(parent=self.widget_2)
        self.portfolio_LA.setGeometry(QtCore.QRect(20, 380, 101, 16))
        self.portfolio_LA.setStyleSheet("color: white;")
        self.portfolio_LA.setObjectName("portfolio_LA")
        self.widget_3 = QtWidgets.QWidget(parent=self.widget_2)
        self.widget_3.setGeometry(QtCore.QRect(10, 410, 481, 281))
        self.widget_3.setStyleSheet("background-color: rgb(57, 58, 58);\n"
"border-radius:30px;")
        self.widget_3.setObjectName("widget_3")
        self.tableView_2 = QtWidgets.QTableView(parent=self.widget_3)
        self.tableView_2.setGeometry(QtCore.QRect(20, 10, 441, 261))
        self.tableView_2.setStyleSheet("color: white;")
        self.tableView_2.setObjectName("tableView_2")
        self.widget_4 = QtWidgets.QWidget(parent=self.widget_2)
        self.widget_4.setGeometry(QtCore.QRect(520, 340, 401, 381))
        self.widget_4.setStyleSheet("background-color: rgb(57, 58, 58);\n"
"border-radius:30px;")
        self.widget_4.setObjectName("widget_4")
        self.tabWidget = QtWidgets.QTabWidget(parent=self.widget_4)
        self.tabWidget.setGeometry(QtCore.QRect(20, 20, 361, 351))
        self.tabWidget.setStyleSheet("color:black;")
        self.tabWidget.setObjectName("tabWidget")
        self.tab = QtWidgets.QWidget()
        self.tab.setObjectName("tab")
        self.widget_6 = QtWidgets.QWidget(parent=self.tab)
        self.widget_6.setGeometry(QtCore.QRect(0, 10, 341, 61))
        self.widget_6.setStyleSheet("background-color: rgb(39, 40, 40);\n"
"border-radius:30px;\n"
"color:white;")
        self.widget_6.setObjectName("widget_6")
        self.currencySelect_CB = QtWidgets.QComboBox(parent=self.widget_6)
        self.currencySelect_CB.setGeometry(QtCore.QRect(20, 10, 301, 51))
        self.currencySelect_CB.setObjectName("currencySelect_CB")
        self.currencySelect_CB.addItem("")
        self.currencySelect_CB.addItem("")
        self.currencySelect_CB.addItem("")
        self.currencySelect_CB.addItem("")
        self.currencySelect_CB.addItem("")
        self.exchange_LA = QtWidgets.QLabel(parent=self.widget_6)
        self.exchange_LA.setGeometry(QtCore.QRect(30, 0, 71, 16))
        self.exchange_LA.setStyleSheet("")
        self.exchange_LA.setObjectName("exchange_LA")
        self.widget_7 = QtWidgets.QWidget(parent=self.tab)
        self.widget_7.setGeometry(QtCore.QRect(0, 90, 341, 61))
        self.widget_7.setStyleSheet("background-color: rgb(39, 40, 40);\n"
"border-radius:30px;\n"
"color:white;")
        self.widget_7.setObjectName("widget_7")
        self.selling_LA = QtWidgets.QLabel(parent=self.widget_7)
        self.selling_LA.setGeometry(QtCore.QRect(20, 0, 71, 16))
        self.selling_LA.setStyleSheet("")
        self.selling_LA.setObjectName("selling_LA")
        self.quantity_swap_SB = QtWidgets.QDoubleSpinBox(parent=self.widget_7)
        self.quantity_swap_SB.setGeometry(QtCore.QRect(250, 20, 91, 31))
        self.quantity_swap_SB.setDecimals(8)
        self.quantity_swap_SB.setObjectName("quantity_swap_SB")
        self.sellingCurrency_LA = QtWidgets.QLabel(parent=self.widget_7)
        self.sellingCurrency_LA.setGeometry(QtCore.QRect(20, 20, 81, 31))
        self.sellingCurrency_LA.setText("")
        self.sellingCurrency_LA.setObjectName("sellingCurrency_LA")
        self.widget_8 = QtWidgets.QWidget(parent=self.tab)
        self.widget_8.setGeometry(QtCore.QRect(0, 170, 341, 61))
        self.widget_8.setStyleSheet("background-color: rgb(39, 40, 40);\n"
"border-radius:30px;\n"
"color:white;")
        self.widget_8.setObjectName("widget_8")
        self.buying_LA = QtWidgets.QLabel(parent=self.widget_8)
        self.buying_LA.setGeometry(QtCore.QRect(20, 0, 71, 16))
        self.buying_LA.setStyleSheet("")
        self.buying_LA.setObjectName("buying_LA")
        self.buyingCurrency_swap_CB = QtWidgets.QComboBox(parent=self.widget_8)
        self.buyingCurrency_swap_CB.setGeometry(QtCore.QRect(10, 20, 321, 31))
        self.buyingCurrency_swap_CB.setObjectName("buyingCurrency_swap_CB")
        self.buyingCurrency_swap_CB.addItem("")
        self.buyingCurrency_swap_CB.addItem("")
        self.buyingCurrency_swap_CB.addItem("")
        self.buyingCurrency_swap_CB.addItem("")
        self.buyingCurrency_swap_CB.addItem("")
        self.exchangeFee_LA = QtWidgets.QLabel(parent=self.tab)
        self.exchangeFee_LA.setGeometry(QtCore.QRect(10, 240, 91, 16))
        self.exchangeFee_LA.setStyleSheet("color:white;")
        self.exchangeFee_LA.setObjectName("exchangeFee_LA")
        self.exchange_PB = QtWidgets.QPushButton(parent=self.tab)
        self.exchange_PB.setGeometry(QtCore.QRect(80, 270, 191, 61))
        self.exchange_PB.setStyleSheet("background-color: rgb(255, 106, 35);\n"
"color:white;")
        self.exchange_PB.setText("")
        self.exchange_PB.setObjectName("exchange_PB")
        self.tabWidget.addTab(self.tab, "")
        self.tab_2 = QtWidgets.QWidget()
        self.tab_2.setObjectName("tab_2")
        self.widget_12 = QtWidgets.QWidget(parent=self.tab_2)
        self.widget_12.setGeometry(QtCore.QRect(10, 20, 341, 61))
        self.widget_12.setStyleSheet("background-color: rgb(39, 40, 40);\n"
"border-radius:30px;\n"
"color:white;")
        self.widget_12.setObjectName("widget_12")
        self.buying_LA_2 = QtWidgets.QLabel(parent=self.widget_12)
        self.buying_LA_2.setGeometry(QtCore.QRect(20, 0, 71, 16))
        self.buying_LA_2.setStyleSheet("")
        self.buying_LA_2.setObjectName("buying_LA_2")
        self.buyingCurrency_buy_CB = QtWidgets.QComboBox(parent=self.widget_12)
        self.buyingCurrency_buy_CB.setGeometry(QtCore.QRect(10, 20, 321, 31))
        self.buyingCurrency_buy_CB.setObjectName("buyingCurrency_buy_CB")
        self.buyingCurrency_buy_CB.addItem("")
        self.buyingCurrency_buy_CB.addItem("")
        self.buyingCurrency_buy_CB.addItem("")
        self.buyingCurrency_buy_CB.addItem("")
        self.buyingCurrency_buy_CB.addItem("")
        self.widget_11 = QtWidgets.QWidget(parent=self.tab_2)
        self.widget_11.setGeometry(QtCore.QRect(10, 110, 341, 61))
        self.widget_11.setStyleSheet("background-color: rgb(39, 40, 40);\n"
"border-radius:30px;\n"
"color:white;")
        self.widget_11.setObjectName("widget_11")
        self.selling_LA_2 = QtWidgets.QLabel(parent=self.widget_11)
        self.selling_LA_2.setGeometry(QtCore.QRect(20, 0, 71, 16))
        self.selling_LA_2.setStyleSheet("")
        self.selling_LA_2.setObjectName("selling_LA_2")
        self.quantity_buy_SB = QtWidgets.QDoubleSpinBox(parent=self.widget_11)
        self.quantity_buy_SB.setGeometry(QtCore.QRect(250, 20, 81, 31))
        self.quantity_buy_SB.setDecimals(8)
        self.quantity_buy_SB.setObjectName("quantity_buy_SB")
        self.sellingCurrency_LA_2 = QtWidgets.QLabel(parent=self.widget_11)
        self.sellingCurrency_LA_2.setGeometry(QtCore.QRect(20, 20, 81, 31))
        self.sellingCurrency_LA_2.setText("")
        self.sellingCurrency_LA_2.setObjectName("sellingCurrency_LA_2")
        self.priceBuy_LA = QtWidgets.QLabel(parent=self.tab_2)
        self.priceBuy_LA.setGeometry(QtCore.QRect(20, 200, 161, 41))
        self.priceBuy_LA.setStyleSheet("color:white;")
        self.priceBuy_LA.setObjectName("priceBuy_LA")
        self.buy_PB = QtWidgets.QPushButton(parent=self.tab_2)
        self.buy_PB.setGeometry(QtCore.QRect(80, 250, 191, 61))
        self.buy_PB.setStyleSheet("background-color: rgb(255, 106, 35);\n"
"color:white;")
        self.buy_PB.setText("")
        self.buy_PB.setObjectName("buy_PB")
        self.tabWidget.addTab(self.tab_2, "")
        self.Sell = QtWidgets.QWidget()
        self.Sell.setObjectName("Sell")
        self.widget_13 = QtWidgets.QWidget(parent=self.Sell)
        self.widget_13.setGeometry(QtCore.QRect(10, 110, 341, 61))
        self.widget_13.setStyleSheet("background-color: rgb(39, 40, 40);\n"
"border-radius:30px;\n"
"color:white;")
        self.widget_13.setObjectName("widget_13")
        self.selling_LA_3 = QtWidgets.QLabel(parent=self.widget_13)
        self.selling_LA_3.setGeometry(QtCore.QRect(20, 0, 71, 16))
        self.selling_LA_3.setStyleSheet("")
        self.selling_LA_3.setObjectName("selling_LA_3")
        self.quantity_sell_SB = QtWidgets.QDoubleSpinBox(parent=self.widget_13)
        self.quantity_sell_SB.setGeometry(QtCore.QRect(250, 20, 81, 31))
        self.quantity_sell_SB.setDecimals(8)
        self.quantity_sell_SB.setObjectName("quantity_sell_SB")
        self.sellingCurrency_LA_3 = QtWidgets.QLabel(parent=self.widget_13)
        self.sellingCurrency_LA_3.setGeometry(QtCore.QRect(20, 20, 81, 31))
        self.sellingCurrency_LA_3.setText("")
        self.sellingCurrency_LA_3.setObjectName("sellingCurrency_LA_3")
        self.widget_14 = QtWidgets.QWidget(parent=self.Sell)
        self.widget_14.setGeometry(QtCore.QRect(10, 20, 341, 61))
        self.widget_14.setStyleSheet("background-color: rgb(39, 40, 40);\n"
"border-radius:30px;\n"
"color:white;")
        self.widget_14.setObjectName("widget_14")
        self.buying_LA_3 = QtWidgets.QLabel(parent=self.widget_14)
        self.buying_LA_3.setGeometry(QtCore.QRect(20, 0, 71, 16))
        self.buying_LA_3.setStyleSheet("")
        self.buying_LA_3.setObjectName("buying_LA_3")
        self.sellingCurrency_CB = QtWidgets.QComboBox(parent=self.widget_14)
        self.sellingCurrency_CB.setGeometry(QtCore.QRect(10, 20, 321, 31))
        self.sellingCurrency_CB.setObjectName("sellingCurrency_CB")
        self.sellingCurrency_CB.addItem("")
        self.sellingCurrency_CB.addItem("")
        self.sellingCurrency_CB.addItem("")
        self.sellingCurrency_CB.addItem("")
        self.sellingCurrency_CB.addItem("")
        self.priceSell_LA = QtWidgets.QLabel(parent=self.Sell)
        self.priceSell_LA.setGeometry(QtCore.QRect(20, 200, 211, 41))
        self.priceSell_LA.setStyleSheet("color:white;")
        self.priceSell_LA.setObjectName("priceSell_LA")
        self.sell_PB = QtWidgets.QPushButton(parent=self.Sell)
        self.sell_PB.setGeometry(QtCore.QRect(80, 250, 191, 61))
        self.sell_PB.setStyleSheet("background-color: rgb(255, 106, 35);\n"
"color:white;")
        self.sell_PB.setText("")
        self.sell_PB.setObjectName("sell_PB")
        self.tabWidget.addTab(self.Sell, "")
        self.widget_4.raise_()
        self.widget.raise_()
        self.portfolio_LA.raise_()
        self.widget_3.raise_()
        self.stackedWidget.addWidget(self.Dashboard)
        self.Portfolio = QtWidgets.QWidget()
        self.Portfolio.setObjectName("Portfolio")
        self.stackedWidget.addWidget(self.Portfolio)
        self.Market = QtWidgets.QWidget()
        self.Market.setObjectName("Market")
        self.widget_5 = QtWidgets.QWidget(parent=self.Market)
        self.widget_5.setGeometry(QtCore.QRect(0, 0, 1071, 691))
        self.widget_5.setStyleSheet("background-color: rgb(39, 40, 40);\n"
"border-radius:10px;")
        self.widget_5.setObjectName("widget_5")
        self.widget_9 = QtWidgets.QWidget(parent=self.widget_5)
        self.widget_9.setGeometry(QtCore.QRect(50, 20, 881, 661))
        self.widget_9.setStyleSheet("background-color: rgb(81, 82, 82);\n"
"border-radius:30px;")
        self.widget_9.setObjectName("widget_9")
        self.label_2 = QtWidgets.QLabel(parent=self.widget_9)
        self.label_2.setGeometry(QtCore.QRect(20, 50, 71, 61))
        self.label_2.setText("")
        self.label_2.setPixmap(QtGui.QPixmap("../resources/bitcoin.png"))
        self.label_2.setScaledContents(True)
        self.label_2.setObjectName("label_2")
        self.label_3 = QtWidgets.QLabel(parent=self.widget_9)
        self.label_3.setGeometry(QtCore.QRect(100, 70, 58, 16))
        self.label_3.setObjectName("label_3")
        self.label_4 = QtWidgets.QLabel(parent=self.widget_9)
        self.label_4.setGeometry(QtCore.QRect(50, 20, 58, 16))
        self.label_4.setObjectName("label_4")
        self.tableView = QtWidgets.QTableView(parent=self.widget_9)
        self.tableView.setGeometry(QtCore.QRect(200, 10, 651, 601))
        self.tableView.setObjectName("tableView")
        self.label_5 = QtWidgets.QLabel(parent=self.widget_9)
        self.label_5.setGeometry(QtCore.QRect(20, 150, 71, 61))
        self.label_5.setText("")
        self.label_5.setPixmap(QtGui.QPixmap("../resources/etherium.png"))
        self.label_5.setScaledContents(True)
        self.label_5.setObjectName("label_5")
        self.label_6 = QtWidgets.QLabel(parent=self.widget_9)
        self.label_6.setGeometry(QtCore.QRect(20, 250, 71, 61))
        self.label_6.setText("")
        self.label_6.setPixmap(QtGui.QPixmap("../resources/solana.svg"))
        self.label_6.setScaledContents(True)
        self.label_6.setObjectName("label_6")
        self.label_8 = QtWidgets.QLabel(parent=self.widget_9)
        self.label_8.setGeometry(QtCore.QRect(20, 350, 71, 61))
        self.label_8.setText("")
        self.label_8.setPixmap(QtGui.QPixmap("../resources/binance.png"))
        self.label_8.setScaledContents(True)
        self.label_8.setObjectName("label_8")
        self.label_9 = QtWidgets.QLabel(parent=self.widget_9)
        self.label_9.setGeometry(QtCore.QRect(20, 550, 71, 61))
        self.label_9.setText("")
        self.label_9.setPixmap(QtGui.QPixmap("../resources/dodgecoin.png"))
        self.label_9.setScaledContents(True)
        self.label_9.setObjectName("label_9")
        self.label_10 = QtWidgets.QLabel(parent=self.widget_9)
        self.label_10.setGeometry(QtCore.QRect(100, 170, 61, 16))
        self.label_10.setObjectName("label_10")
        self.label_11 = QtWidgets.QLabel(parent=self.widget_9)
        self.label_11.setGeometry(QtCore.QRect(100, 270, 58, 16))
        self.label_11.setObjectName("label_11")
        self.label_12 = QtWidgets.QLabel(parent=self.widget_9)
        self.label_12.setGeometry(QtCore.QRect(100, 370, 58, 16))
        self.label_12.setObjectName("label_12")
        self.label_13 = QtWidgets.QLabel(parent=self.widget_9)
        self.label_13.setGeometry(QtCore.QRect(100, 470, 58, 16))
        self.label_13.setObjectName("label_13")
        self.label_14 = QtWidgets.QLabel(parent=self.widget_9)
        self.label_14.setGeometry(QtCore.QRect(100, 570, 71, 16))
        self.label_14.setObjectName("label_14")
        self.stackedWidget.addWidget(self.Market)
        self.Transactions = QtWidgets.QWidget()
        self.Transactions.setObjectName("Transactions")
        self.stackedWidget.addWidget(self.Transactions)
        self.watchlist = QtWidgets.QWidget()
        self.watchlist.setObjectName("watchlist")
        self.stackedWidget.addWidget(self.watchlist)
        self.widget_10 = QtWidgets.QWidget(parent=Crypto)
        self.widget_10.setGeometry(QtCore.QRect(0, 0, 151, 721))
        self.widget_10.setStyleSheet("background-color: rgb(39, 40, 40);\n"
"border-radius:10px;")
        self.widget_10.setObjectName("widget_10")
        self.back_PB = QtWidgets.QPushButton(parent=self.widget_10)
        self.back_PB.setGeometry(QtCore.QRect(20, 660, 100, 32))
        self.back_PB.setStyleSheet("background-color: rgb(84, 85, 85);\n"
"color: white;")
        self.back_PB.setObjectName("back_PB")
        self.widget_15 = QtWidgets.QWidget(parent=self.widget_10)
        self.widget_15.setGeometry(QtCore.QRect(140, 70, 1151, 661))
        self.widget_15.setStyleSheet("background-color: rgb(39, 40, 40);\n"
"border-radius:10px;")
        self.widget_15.setObjectName("widget_15")
        self.widget_15.raise_()
        self.back_PB.raise_()
        self.widget_10.raise_()
        self.line.raise_()
        self.stackedWidget.raise_()

        self.retranslateUi(Crypto)
        self.tabWidget.setCurrentIndex(1)
        QtCore.QMetaObject.connectSlotsByName(Crypto)

    def retranslateUi(self, Crypto):
        _translate = QtCore.QCoreApplication.translate
        Crypto.setWindowTitle(_translate("Crypto", "Form"))
        self.Bitcon_LA.setText(_translate("Crypto", "Bitcoin"))
        self.BTC_LA.setText(_translate("Crypto", "BTC"))
        self.solana_LA.setText(_translate("Crypto", "Solana"))
        self.SOL_LA.setText(_translate("Crypto", "SOL"))
        self.Etherium_LA.setText(_translate("Crypto", "Etherium"))
        self.ETH_LA.setText(_translate("Crypto", "ETH"))
        self.Binance_LA.setText(_translate("Crypto", "Binance"))
        self.BNB_LA.setText(_translate("Crypto", "BNB"))
        self.now_LA.setText(_translate("Crypto", "Now"))
        self.now_LA_3.setText(_translate("Crypto", "Now"))
        self.now_LA_2.setText(_translate("Crypto", "Now"))
        self.now_LA_4.setText(_translate("Crypto", "Now"))
        self.label.setText(_translate("Crypto", "Watchlist"))
        self.portfolio_LA.setText(_translate("Crypto", "Your portfolio"))
        self.currencySelect_CB.setItemText(0, _translate("Crypto", "BTC"))
        self.currencySelect_CB.setItemText(1, _translate("Crypto", "ETH"))
        self.currencySelect_CB.setItemText(2, _translate("Crypto", "SOL"))
        self.currencySelect_CB.setItemText(3, _translate("Crypto", "BNB"))
        self.currencySelect_CB.setItemText(4, _translate("Crypto", "DODGECOIN"))
        self.exchange_LA.setText(_translate("Crypto", "Exchange"))
        self.selling_LA.setText(_translate("Crypto", "Selling"))
        self.buying_LA.setText(_translate("Crypto", "Buying"))
        self.buyingCurrency_swap_CB.setItemText(0, _translate("Crypto", "BTC"))
        self.buyingCurrency_swap_CB.setItemText(1, _translate("Crypto", "ETH"))
        self.buyingCurrency_swap_CB.setItemText(2, _translate("Crypto", "SOL"))
        self.buyingCurrency_swap_CB.setItemText(3, _translate("Crypto", "BNB"))
        self.buyingCurrency_swap_CB.setItemText(4, _translate("Crypto", "DODGECOIN"))
        self.exchangeFee_LA.setText(_translate("Crypto", "Exchange fee"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab), _translate("Crypto", "Swap"))
        self.buying_LA_2.setText(_translate("Crypto", "Buying"))
        self.buyingCurrency_buy_CB.setItemText(0, _translate("Crypto", "BTC"))
        self.buyingCurrency_buy_CB.setItemText(1, _translate("Crypto", "ETH"))
        self.buyingCurrency_buy_CB.setItemText(2, _translate("Crypto", "SOL"))
        self.buyingCurrency_buy_CB.setItemText(3, _translate("Crypto", "BNB"))
        self.buyingCurrency_buy_CB.setItemText(4, _translate("Crypto", "DODGECOIN"))
        self.selling_LA_2.setText(_translate("Crypto", "Quantity"))
        self.priceBuy_LA.setText(_translate("Crypto", "TextLabel"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_2), _translate("Crypto", "Buy"))
        self.selling_LA_3.setText(_translate("Crypto", "Quantity"))
        self.buying_LA_3.setText(_translate("Crypto", "Selling"))
        self.sellingCurrency_CB.setItemText(0, _translate("Crypto", "BTC"))
        self.sellingCurrency_CB.setItemText(1, _translate("Crypto", "ETH"))
        self.sellingCurrency_CB.setItemText(2, _translate("Crypto", "SOL"))
        self.sellingCurrency_CB.setItemText(3, _translate("Crypto", "BNB"))
        self.sellingCurrency_CB.setItemText(4, _translate("Crypto", "DODGECOIN"))
        self.priceSell_LA.setText(_translate("Crypto", "TextLabel"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.Sell), _translate("Crypto", "Sell"))
        self.label_3.setText(_translate("Crypto", "Bitcoin"))
        self.label_4.setText(_translate("Crypto", "Name"))
        self.label_10.setText(_translate("Crypto", "Ethereum"))
        self.label_11.setText(_translate("Crypto", "Solana"))
        self.label_12.setText(_translate("Crypto", "BNB"))
        self.label_13.setText(_translate("Crypto", "TetherUS"))
        self.label_14.setText(_translate("Crypto", "Dodgecoin"))
        self.back_PB.setText(_translate("Crypto", "Back"))
        self.updatePrices()

        # Create a timer to update prices every 2000 milliseconds (2 seconds)
        self.timer = QtCore.QTimer(Crypto)
        self.timer.timeout.connect(self.updatePrices)
        self.timer.timeout.connect(self.updateBuyPrice)
        self.timer.timeout.connect(self.updateSellGain)
        self.timer.timeout.connect(self.updateButtonText)
        self.timer.start(2000)  # Set the interval in milliseconds

        QtCore.QMetaObject.connectSlotsByName(Crypto)

        self.buy_PB.clicked.connect(lambda: self.buyCrypto())
        self.sell_PB.clicked.connect(lambda: self.sellCrypto())

    def updatePrices(self):
        # Cryptocurrencies to display
        cryptocurrenciesDashboard = ["BTC", "ETH", "SOL", "BNB"]

        # Get prices for cryptocurrencies
        price_data = cryptocompare.get_price(cryptocurrenciesDashboard, currency="USD")

        # Update label text with cryptocurrency prices
        for crypto in cryptocurrenciesDashboard:
            price_label = getattr(self, f"{crypto}_price_LA")  # Get the label by its name
            crypto_price = price_data[crypto]['USD']
            price_label.setText(f"{crypto_price} USD")

    def updateButtonText(self):
        selling_crypto_name = str(self.currencySelect_CB.currentText())
        buying_crypto_name = str(self.buyingCurrency_swap_CB.currentText())
        quantity_to_swap = float(self.quantity_swap_SB.value())

        # Set the button text to reflect the swap
        self.exchange_PB.setText(f"Get {quantity_to_swap} {buying_crypto_name}")

    

    def buyCrypto(self):
        try:
            if self.cnx.is_connected():
                print("Connection successful!")

                cursor = self.cnx.cursor()

                # Fetch user's balance
                select_query = "SELECT `Balance` FROM users WHERE username = %s"
                cursor.execute(select_query, (username,))
                balance_result = cursor.fetchone()

                if balance_result:
                    balance = float(balance_result[0])

                    # Get the total cost from the buy_PB button text
                    total_cost_str = self.buy_PB.text().split()[0]
                    total_cost = float(total_cost_str)

                    # Check if the user has enough balance to make the purchase
                    if balance >= total_cost:
                        new_balance = balance - total_cost

                        # Update the user's balance
                        update_query = "UPDATE users SET `Balance` = %s WHERE username = %s"
                        cursor.execute(update_query, (new_balance, username))

                        self.cnx.commit()

                        # Check if the user already has a record for the cryptocurrency
                        crypto_name = str(self.buyingCurrency_buy_CB.currentText())
                        select_crypto_query = "SELECT `Crypto Amount` FROM crypto WHERE Username = %s AND `Crypto Name` = %s"
                        cursor.execute(select_crypto_query, (f'{username}', crypto_name))
                        crypto_result = cursor.fetchone()

                        if crypto_result:
                            # If the user already has a record, update the quantity
                            current_crypto_amount = float(crypto_result[0])
                            new_crypto_amount = current_crypto_amount + float(self.quantity_buy_SB.value())

                            update_crypto_query = "UPDATE crypto SET `Crypto Amount` = %s WHERE Username = %s AND `Crypto Name` = %s"
                            cursor.execute(update_crypto_query, (new_crypto_amount, f'{username}', crypto_name))
                        else:
                            # If the user doesn't have a record, insert a new record
                            crypto_amount = float(self.quantity_buy_SB.value())
                            insert_query = """
                                        INSERT INTO crypto (Username, `Crypto Name`, `Crypto Amount`, `Purchase Date`)
                                        VALUES (%s, %s, %s, %s)
                                    """
                            purchase_date = datetime.now()
                            cursor.execute(insert_query, (f'{username}', crypto_name, crypto_amount, purchase_date))

                        self.cnx.commit()

                        print("Purchase successful!")
                        print(f"New balance: {new_balance} USD")
                    else:
                        print("Insufficient balance for the purchase.")
                else:
                    print("User not found or no balance information.")
            else:
                print("Connection failed.")
        except mysql.connector.Error as e:
            print("Error connecting to MySQL database:", e)



    def updateBuyPrice(self):
        cryptoCurrency = self.buyingCurrency_buy_CB.currentText()
        quantity = self.quantity_buy_SB.value()
        cryptoData = cryptocompare.get_price(cryptoCurrency, currency="USD")
        cryptoPrice = cryptoData[cryptoCurrency]['USD']
        price = cryptoPrice * quantity
        rounded_price = round(price, 2)  # Round to the second decimal place
        self.buy_PB.setText(str(rounded_price) + " USD")

    def updateSellGain(self):
        cryptoCurrency = self.sellingCurrency_CB.currentText()
        quantity = self.quantity_sell_SB.value()
        cryptoData = cryptocompare.get_price(cryptoCurrency, currency="USD")
        cryptoPrice = cryptoData[cryptoCurrency]['USD']
        sellAmount = cryptoPrice * quantity
        rounded_sell_amount = round(sellAmount, 2)  # Round to the second decimal place
        self.sell_PB.setText(str(rounded_sell_amount) + " USD")


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Crypto = QtWidgets.QWidget()
    ui = Ui_Crypto()
    ui.setupUi(Crypto)
    Crypto.show()
    sys.exit(app.exec())