from tkinter import *
import json
import requests

def reload_data(event=None):
	try:
		response = requests.get('http://localhost:3000/raw').content.decode("utf8")
		forecast_j = json.loads(response)
		desc.config(text=str(forecast_j["description"]))
		temp.config(text=str(round(forecast_j["temp"])) + "°C")
	except requests.exceptions.ConnectionError:
		pass

root = Tk()
root.geometry('200x270')
root.title("Погода")
root.bind("<Button-1>", reload_data)

top =    Frame(root, bg="#e9c04d", width=100, height=30)
middle = Frame(root, bg="#ffffff",  width=100, height=90)
bottom = Frame(root, bg="#e9c04d", width=100, height=30)

top.pack(side=TOP, fill=X)
middle.pack(expand=True, fill=BOTH)
bottom.pack(side=BOTTOM, fill=X)

city = Label(top, font=("Calibri Bold", 12), text="Симферополь", bg="#e9c04d")
desc = Label(top, font=("Calibri", 12), bg="#e9c04d")
temp = Label(middle, font=("Impact", 48), bg="#ffffff")

city.pack(pady=0)
desc.pack(pady=0)
temp.pack(expand=True)

reload_data()
root.mainloop()
